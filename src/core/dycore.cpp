#include "dycore.hpp"
#include "shape_function.hpp"

namespace lady {

Dycore::Dycore() {
  neighborSearch = NULL;
}

Dycore::~Dycore() {
  if (neighborSearch != NULL) delete neighborSearch;
}

void Dycore::init(const MeshConfigType &meshConfig) {
  ShapeFunction::init();
  QuadPoints::init();
  domain.init(meshConfig.domainConfig());
  mesh.init(meshConfig);
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

void Dycore::inputData(int ti, const FieldType &p, const FieldType &T) {
  sp_mat A(mesh.numGrid(), mesh.numGrid());
  vec b1(mesh.numGrid()), b2(mesh.numGrid());
  vec x1(mesh.numGrid()), x2(mesh.numGrid());
  Vec y;
  double f;
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    b1(pi) = p(pi) * CV / RD;
    b2(pi) = p(pi) / T(pi) / RD;
    for (int ni = 0; ni < parcels[ti][pi].numNeighbor; ni++) {
      const Parcel *neighbor = parcels[ti][pi].neighbors[ni];
      neighbor->getBodyCoord(parcels[ti][pi].x, y);
      ShapeFunction::eval(y, f);
      if (abs(f) < 1.0e-16) continue;
      A(pi, neighbor->id) = f / neighbor->detH;
    }
    A(pi, pi) = 1 / parcels[ti][pi].detH;
  }
  spsolve(x1, A, b1);
  spsolve(x2, A, b2);
  for (int pi = 0; pi < mesh.numGrid(); pi++) {
    parcels[ti][pi].m = x2[pi];
    parcels[ti][pi].u = x1[pi] / x2[pi];
  }
}

void Dycore::run() {
}

void Dycore::findNeighbors(int ti) {
  for (int pi = 0; pi < parcels[ti].size(); pi++) {
    for (int di = 0; di < NUM_DIM; di++) {
      parcelCentroids.at(di, pi) = parcels[ti][pi].x[di];
    }
  }
  neighborSearch->Train(parcelCentroids);
  RangeType r(0, 0);
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
    for (size_t ni = 0; ni < neighbors[0].size(); ni++) {
      if (neighbors[0][ni] == pi) continue;
      parcels[ti][pi].neighbors[mi++] = &parcels[ti][neighbors[0][ni]];
    }
  }
}

}
