#include "cartesian_mesh.hpp"

namespace lady {

template class CartesianMesh<2>;
template class CartesianMesh<3>;

template <int NUM_DIM>
CartesianMesh<NUM_DIM>::CartesianMesh() {
}

template <int NUM_DIM>
CartesianMesh<NUM_DIM>::~CartesianMesh() {
}

template <int NUM_DIM>
int CartesianMesh<NUM_DIM>::numGridAlongX() const {
  return this->meshConfig.numGridAlongEachAxis[0];
}

template <int NUM_DIM>
int CartesianMesh<NUM_DIM>::numGridAlongY() const {
  return this->meshConfig.numGridAlongEachAxis[1];
}

template <int NUM_DIM>
int CartesianMesh<NUM_DIM>::numGridAlongZ() const {
  return this->meshConfig.numGridAlongEachAxis[2];
}

}
