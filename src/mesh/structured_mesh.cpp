#include "structured_mesh.hpp"

namespace lady {

template class StructuredMesh<2>;
template class StructuredMesh<3>;

template <int NUM_DIM>
StructuredMesh<NUM_DIM>::StructuredMesh() {
}

template <int NUM_DIM>
StructuredMesh<NUM_DIM>::~StructuredMesh() {

}

template <int NUM_DIM>
void StructuredMesh<NUM_DIM>::init(const MeshConfig<NUM_DIM> &_meshConfig) {
  auto &domainConfig = _meshConfig.domainConfig();
  auto meshConfig = static_cast<const StructuredMeshConfig<NUM_DIM>&>(_meshConfig);
  this->_gridCoords.set_size(NUM_DIM, prod(meshConfig.numGridAlongEachAxis));
  this->_gridSizes.set_size(NUM_DIM, prod(meshConfig.numGridAlongEachAxis));
  // FIXME: Parallel-note: Specify the space decomposition.
  vec grids[NUM_DIM];
  vec intervals[NUM_DIM];
  for (int di = 0; di < NUM_DIM; di++) {
    grids[di].set_size(meshConfig.numGridAlongEachAxis[di]);
    intervals[di].set_size(meshConfig.numGridAlongEachAxis[di]);
    for (int ai = 0; ai < meshConfig.numGridAlongEachAxis[di]; ai++) {
      // Currently, the grids are even distributed.
      intervals[di][ai] = (domainConfig.axisEndCoords[di] - domainConfig.axisStartCoords[di]) / meshConfig.numGridAlongEachAxis[di];
      grids[di][ai] = domainConfig.axisStartCoords[di] + intervals[di][ai] * (ai + 0.5);
    }
  }
  int ai[NUM_DIM], tmp;
  double offset;
  for (int gi = 0; gi < this->_gridCoords.n_cols; gi++) {
    offset = 0;
    for (int di = NUM_DIM-1; di >= 0; di--) {
      if (di != NUM_DIM-1) {
        tmp = 1;
        for (int i = 0; i <= di; i++) {
          tmp *= meshConfig.numGridAlongEachAxis[i];
        }
        offset += ai[di+1] * tmp;
      }
      tmp = 1;
      for (int i = 0; i < di; i++) {
        tmp *= meshConfig.numGridAlongEachAxis[i];
      }
      ai[di] = floor(static_cast<double>(gi-offset) / tmp);
      this->_gridCoords(di, gi) = grids[di][ai[di]];
      this->_gridSizes(di, gi) = intervals[di][ai[di]];
    }
  }
}

}
