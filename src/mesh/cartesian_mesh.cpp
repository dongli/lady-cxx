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

}
