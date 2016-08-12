#include "dycore.hpp"
#include "shape_function.hpp"
#include "cartesian_domain.hpp"
#include "cartesian_mesh.hpp"
#include "cartesian_field.hpp"

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
void Dycore<NUM_DIM, FieldTemplate>::init(const typename MeshType::MeshConfigType &meshConfig) {
  ShapeFunction<NUM_DIM>::init();
  QuadPoints<NUM_DIM>::init();
  domain.init(meshConfig.domainConfig());
  mesh.init(meshConfig);
  meshSearch = new SearchType(mesh.gridCoords(), true);
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
  findNeighbors(0);
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::inputData(int ti, const FieldType &p, const FieldType &T) {
  sp_mat A(mesh.numGrid(), mesh.numGrid());
  vec b1(mesh.numGrid()), b2(mesh.numGrid());
  vec x1(mesh.numGrid()), x2(mesh.numGrid());
  vec::fixed<NUM_DIM> y;
  double f;
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    b1(pi) = p(pi) * CV / RD;
    b2(pi) = p(pi) / T(pi) / RD;
    for (int ni = 0; ni < parcels[ti][pi].numNeighbor; ni++) {
      const Parcel<NUM_DIM> &neighbor = *parcels[ti][pi].neighbors[ni];
      parcels[ti][pi].getBodyCoord(domain, neighbor.x, y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (std::abs(f) < 1.0e-16) continue;
      A(pi, neighbor.id) = f / parcels[ti][pi].detH;
    }
    A(pi, pi) = ShapeFunction<NUM_DIM>::C / parcels[ti][pi].detH;
  }
  spsolve(x1, A, b1);
  spsolve(x2, A, b2);
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    parcels[ti][pi].m = x2[pi];
    parcels[ti][pi].u = x1[pi] / x2[pi];
  }
  // Copy input data into internal fields.
  this->p = p;
  this->T = T;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void Dycore<NUM_DIM, FieldTemplate>::run() {
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
    r.Hi() = parcels[ti][pi].shapeSize(0);
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
void Dycore<NUM_DIM, FieldTemplate>::regrid(int ti) {
  // Find the neighboring grids of each parcel.
  p().fill(0);
  T().fill(0);
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
