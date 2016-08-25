#include "dycore.hpp"
#include "shape_function.hpp"
#include "cartesian_domain.hpp"
#include "cartesian_mesh.hpp"
#include "cartesian_field.hpp"
#include "time_manager.hpp"
#include "io.hpp"

namespace lady {

template class Dycore<2, CartesianField>;
template class Dycore<3, CartesianField>;

template <int NUM_DIM, template <int ...> class FieldTemplate>
Dycore<NUM_DIM, FieldTemplate>::Dycore() {
  neighborSearch = NULL;
  meshSearch = NULL;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
Dycore<NUM_DIM, FieldTemplate>::~Dycore() {
  if (neighborSearch != NULL) delete neighborSearch;
  if (meshSearch != NULL) delete meshSearch;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::init(const DycoreMode mode, const typename MeshType::MeshConfigType &meshConfig) {
  this->mode = mode;
  Rr = 1;

  ShapeFunction<NUM_DIM>::init();
  QuadPoints<NUM_DIM>::init();
  domain.init(meshConfig.domainConfig());
  mesh.init(meshConfig);
  meshSearch = new SearchType(mesh.gridCoords(), true);
  IO<NUM_DIM, FieldTemplate>::init("lady.%1%.nc");

  for (int ti = 0; ti < 2; ti++) {
    parcels[ti].resize(mesh.numGrid());
    quadPoints[ti].resize(parcels[ti].size());
    for (int pi = 0; pi < mesh.numGrid(); pi++) {
      parcels[ti][pi].init(pi, mesh.gridCoord(pi), mesh.gridSize(pi));
      quadPoints[ti][pi].init(&parcels[ti][pi]);
    }
  }
  parcelCentroids.set_size(NUM_DIM, mesh.numGrid());
  neighborSearch = new SearchType(false, true);
  oldTi = 0;
  newTi = 1;
  // Find neighbors of parcels.
  findNeighbors(oldTi);
  // Update quadrature points.
  updateQuadPoints(oldTi);
  // Calculate forces acted on parcels.
  calcForces(oldTi);
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::inputBarotropicData(const FieldType &h, const FieldType &u, const FieldType &v) {
  sp_mat A(mesh.numGrid(), mesh.numGrid());
  vec b1(mesh.numGrid()), b2(mesh.numGrid()), b3(mesh.numGrid());
  vec x1(mesh.numGrid()), x2(mesh.numGrid()), x3(mesh.numGrid());
  vec::fixed<NUM_DIM> y;
  double f;
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    b1(pi) = h(pi);
    b2(pi) = h(pi) * u(pi);
    b3(pi) = h(pi) * v(pi);
    for (int ni = 0; ni < parcels[0][pi].numNeighbor; ni++) {
      const Parcel<NUM_DIM> &neighbor = *parcels[0][pi].neighbors[ni];
      parcels[0][pi].getBodyCoord(domain, neighbor.x, y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (std::abs(f) < 1.0e-16) continue;
      A(pi, neighbor.id) = f / parcels[0][pi].detH;
    }
    A(pi, pi) = ShapeFunction<NUM_DIM>::C / parcels[0][pi].detH;
  }
  spsolve(x1, A, b1);
  spsolve(x2, A, b2);
  spsolve(x3, A, b3);
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    parcels[0][pi].m = x1[pi];
    parcels[0][pi].v[0] = x2[pi] / x1[pi];
    parcels[0][pi].v[1] = x3[pi] / x1[pi];
    parcels[0][pi].dH.zeros();
  }
  this->h = h;
  this->V[0] = u;
  this->V[1] = v;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::inputBaroclinicData(const FieldType &p, const FieldType &T) {
  sp_mat A(mesh.numGrid(), mesh.numGrid());
  vec b1(mesh.numGrid()), b2(mesh.numGrid());
  vec x1(mesh.numGrid()), x2(mesh.numGrid());
  vec::fixed<NUM_DIM> y;
  double f;
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    b1(pi) = p(pi) * CV / RD;
    b2(pi) = p(pi) / T(pi) / RD;
    for (int ni = 0; ni < parcels[0][pi].numNeighbor; ni++) {
      const Parcel<NUM_DIM> &neighbor = *parcels[0][pi].neighbors[ni];
      parcels[0][pi].getBodyCoord(domain, neighbor.x, y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (std::abs(f) < 1.0e-16) continue;
      A(pi, neighbor.id) = f / parcels[0][pi].detH;
    }
    A(pi, pi) = ShapeFunction<NUM_DIM>::C / parcels[0][pi].detH;
  }
  spsolve(x1, A, b1);
  spsolve(x2, A, b2);
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    parcels[0][pi].m = x2[pi];
    parcels[0][pi].u = x1[pi] / x2[pi];
    // TODO: Set initial velocity.
    parcels[0][pi].v.zeros();
    parcels[0][pi].dH.zeros();
  }
  // Copy input data into internal fields.
  this->p = p;
  this->T = T;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::run() {
  double dt = TimeManager::timeStepSize.seconds();
  // Integrate in time direction.
  for (int pi = 0; pi < parcels[newTi].size(); pi++) {  // TODO: What about if parcels are inserted or removed dynamically?
    parcels[newTi][pi].v  = parcels[oldTi][pi].v  + 0.5 * dt * (parcels[oldTi][pi].Fp + parcels[oldTi][pi].Fr);
    parcels[newTi][pi].dH = parcels[oldTi][pi].dH + 0.5 * dt * (parcels[oldTi][pi].Mp + parcels[oldTi][pi].Mr);
    parcels[newTi][pi].x  = parcels[oldTi][pi].x  + dt * parcels[newTi][pi].v;
    parcels[newTi][pi].H  = parcels[oldTi][pi].H  + dt * parcels[newTi][pi].dH;
    parcels[oldTi][pi].v  = parcels[newTi][pi].v;
    parcels[oldTi][pi].dH = parcels[newTi][pi].dH;
  }
  if (mode == BAROCLINIC) {
    calcHeats(oldTi);
    for (int pi = 0; pi < parcels[newTi].size(); pi++) {
      parcels[newTi][pi].u = parcels[oldTi][pi].u;
      for (int iter = 0; iter < 2; iter++) {
        calcHeats(newTi);
        parcels[newTi][pi].u = parcels[oldTi][pi].u + 0.5 * dt * (parcels[oldTi][pi].Qr + parcels[oldTi][pi].Qr);
      }
    }
  }
  // Find neighbors of parcels.
  findNeighbors(newTi);
  // Update quadrature points.
  updateQuadPoints(newTi);
  // Calculate forces acted on parcels.
  calcForces(newTi);
  // Update velocity to new time level.
  for (int pi = 0; pi < parcels[newTi].size(); pi++) {
    parcels[newTi][pi].v  += 0.5 * dt * (parcels[newTi][pi].Fp + parcels[newTi][pi].Fr);
    parcels[newTi][pi].dH += 0.5 * dt * (parcels[newTi][pi].Mp + parcels[newTi][pi].Mr);
  }
  // Switch time indices.
  int ti = oldTi; oldTi = newTi; newTi = ti;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::output(int ti) const {
  if (mode == BAROTROPIC) {
    IO<NUM_DIM, FieldTemplate>::outputBarotropicData(domain, mesh, h, V[0], V[1]);
  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::findNeighbors(int ti) {
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    for (int di = 0; di < NUM_DIM; di++) {
      parcelCentroids.at(di, pi) = parcels[ti][pi].x[di];
    }
  }
  neighborSearch->Train(parcelCentroids);
  Range r(0, 0);
  vector<vector<size_t>> neighbors;
  vector<vector<double>> distances;
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    // Enlarge the search range for quadrature points.
    r.Hi() = parcels[ti][pi].shapeSize(0) * 2;
    neighborSearch->Search(parcels[ti][pi].x, r, neighbors, distances);
    if (parcels[ti][pi].neighbors.capacity() < neighbors[0].size()) {
      parcels[ti][pi].neighbors.resize(neighbors[0].size());
    }
    parcels[ti][pi].numNeighbor = neighbors[0].size() - 1; // Exclude self.
    int mi = 0;
    for (int ni = 0; ni < neighbors[0].size(); ni++) {
      if (neighbors[0][ni] == pi) continue;
      parcels[ti][pi].neighbors[mi++] = &parcels[ti][neighbors[0][ni]];
    }
  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::updateQuadPoints(int ti) {
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    quadPoints[ti][pi].update(domain);
  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::calcForces(int ti) {
  double f, rho, T, w, a1;
  vec::fixed<NUM_DIM> y, v, vi, a2;
  mat::fixed<NUM_DIM, NUM_DIM> a3;
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    parcels[ti][pi].Fp.zeros(); parcels[ti][pi].Mp.zeros();
    parcels[ti][pi].Fr.zeros(); parcels[ti][pi].Mr.zeros();
    for (int ni = 0; ni < parcels[ti][pi].numNeighbor; ni++) {
      const Parcel<NUM_DIM> &neighbor = *parcels[ti][pi].neighbors[ni];
      for (int qi = 0; qi < QuadPoints<NUM_DIM>::num; qi++) {
        parcels[ti][pi].getBodyCoord(domain, quadPoints[ti][neighbor.id].x[qi], y);
        ShapeFunction<NUM_DIM>::eval(y, f);
        if (std::abs(f) < 1.0e-16) continue;
        rho = quadPoints[ti][neighbor.id].rho[qi];
        T = quadPoints[ti][neighbor.id].T[qi];
        v = quadPoints[ti][neighbor.id].v[qi];
        parcels[ti][pi].getLocalVelocity(y, vi);
        w = QuadPoints<NUM_DIM>::w[qi];
        // First part of pressure force
        switch (mode) {
          case BAROTROPIC:
            a1 = neighbor.m * w * G;
            break;
          case BAROCLINIC:
            a1 = neighbor.m * w * (parcels[ti][pi].u - CV * T) / rho;
            break;
        }
        parcels[ti][pi].getShapeFunctionDerivatives(y, f, a2, a3);
        parcels[ti][pi].Fp -= a1 * a2;
        parcels[ti][pi].Mp -= a1 * a3;
        // Friction force
        a1 = neighbor.m * w * Rr * f / parcels[ti][pi].detH / rho;
        a2 = vi - v;
        parcels[ti][pi].Fr -= a1 * a2;
        parcels[ti][pi].Mr -= a1 * a2 * y.t();
      }
    }
    // Second part of pressure force
    for (int qi = 0; qi < QuadPoints<NUM_DIM>::num; qi++) {
      rho = quadPoints[ti][pi].rho[qi];
      T = quadPoints[ti][pi].T[qi];
      parcels[ti][pi].getShapeFunctionDerivatives(QuadPoints<NUM_DIM>::y[qi], QuadPoints<NUM_DIM>::f[qi], a2);
      w = QuadPoints<NUM_DIM>::w[qi];
      switch (mode) {
        case BAROTROPIC:
          a1 = parcels[ti][pi].m * w * G;
          break;
        case BAROCLINIC:
          a1 = parcels[ti][pi].m * w * (parcels[ti][pi].u - CV * T) / rho;
          break;
      }
      parcels[ti][pi].Fp -= a1 * a2;
      parcels[ti][pi].Mp -= a1 * a2 * QuadPoints<NUM_DIM>::y[qi].t();
    }
    parcels[ti][pi].Mp /= ShapeFunction<NUM_DIM>::J;
    parcels[ti][pi].Fr /= 2 * parcels[ti][pi].m;
    parcels[ti][pi].Mr /= 2 * parcels[ti][pi].m * ShapeFunction<NUM_DIM>::J;
  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::calcHeats(int ti) {
  double f, rho, T, w, a1, a2;
  vec::fixed<NUM_DIM> y, v, vi;
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    parcels[ti][pi].Qr = 0;
    for (int ni = 0; ni < parcels[ti][pi].numNeighbor; ni++) {
      const Parcel<NUM_DIM> &neighbor1 = *parcels[ti][pi].neighbors[ni];
      for (int qi = 0; qi < QuadPoints<NUM_DIM>::num; qi++) {
        parcels[ti][pi].getBodyCoord(domain, quadPoints[ti][neighbor1.id].x[qi], y);
        ShapeFunction<NUM_DIM>::eval(y, f);
        if (std::abs(f) < 1.0e-16) continue;
        rho = quadPoints[ti][neighbor1.id].rho[qi];
        v = quadPoints[ti][neighbor1.id].v[qi];
        w = QuadPoints<NUM_DIM>::w[qi];
        a1 = neighbor1.m * f / parcels[ti][pi].detH * w / rho / rho;
        // Friction generated heat
        a2 = 0;
        for (int nj = 0; nj < parcels[ti][pi].numNeighbor; nj++) {
          const Parcel<NUM_DIM> &neighbor2 = *parcels[ti][pi].neighbors[nj];
          neighbor2.getBodyCoord(domain, quadPoints[ti][neighbor1.id].x[qi], y);
          ShapeFunction<NUM_DIM>::eval(y, f);
          if (std::abs(f) < 1.0e-16) continue;
          neighbor2.getLocalVelocity(y, vi);
          a2 += neighbor2.m * f / neighbor2.detH * dot(vi, vi) - rho * dot(v, v);
        }
        parcels[ti][pi].Qr += a1 * a2;
      }
      parcels[ti][pi].Qr *= Rr * 0.5;
    }
  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::regridBarotropicData(int ti) {
  // Find the neighboring grids of each parcel.
  h().fill(0); V[0]().fill(0); V[1]().fill(0);
  Range r(0, 0);
  vector<vector<size_t>> neighbors;
  vector<vector<double>> distances;
  vec::fixed<NUM_DIM> y, v;
  double f, tmp;
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    r.Hi() = parcels[ti][pi].shapeSize(0);
    meshSearch->Search(parcels[ti][pi].x, r, neighbors, distances);
    for (int ni = 0; ni < neighbors[0].size(); ni++) {
      int gi = neighbors[0][ni];
      parcels[ti][pi].getBodyCoord(domain, mesh.gridCoord(gi), y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (std::abs(f) < 1.0e-16) continue;
      parcels[ti][pi].getLocalVelocity(y, v);
      tmp = f / parcels[ti][pi].detH * parcels[ti][pi].m;
      h(gi) += tmp;
      V[0](gi) += tmp * v[0];
      V[1](gi) += tmp * v[1];
    }
  }
  for (int gi = 0; gi < mesh.numGrid(); gi++) {
    V[0](gi) /= h(gi);
    V[1](gi) /= h(gi);
  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::regridBaroclinicData(int ti) {
  // Find the neighboring grids of each parcel.
  p().fill(0); T().fill(0);
  Range r(0, 0);
  vector<vector<size_t>> neighbors;
  vector<vector<double>> distances;
  vec::fixed<NUM_DIM> y;
  double f, tmp;
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    r.Hi() = parcels[ti][pi].shapeSize(0);
    meshSearch->Search(parcels[ti][pi].x, r, neighbors, distances);
    for (int ni = 0; ni < neighbors[0].size(); ni++) {
      int gi = neighbors[0][ni];
      parcels[ti][pi].getBodyCoord(domain, mesh.gridCoord(gi), y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (std::abs(f) < 1.0e-16) continue;
      tmp = f / parcels[ti][pi].detH * parcels[ti][pi].m;
      p(gi) += tmp;
      T(gi) += tmp * parcels[ti][pi].u;
    }
  }
  for (int gi = 0; gi < mesh.numGrid(); gi++) {
    T(gi) = T(gi) / p(gi) / CV;
    p(gi) = p(gi) * T(gi) * RD;
  }
}

}
