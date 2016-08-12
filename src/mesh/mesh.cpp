#include "mesh.hpp"

namespace lady {

template class Mesh<2>;
template class Mesh<3>;

template <int NUM_DIM>
Mesh<NUM_DIM>::Mesh() {

}

template <int NUM_DIM>
Mesh<NUM_DIM>::~Mesh() {

}

}
