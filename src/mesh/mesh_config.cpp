#include "mesh_config.hpp"

namespace lady {

template class MeshConfig<2>;
template class MeshConfig<3>;

template <int NUM_DIM>
MeshConfig<NUM_DIM>& MeshConfig<NUM_DIM>::operator=(const MeshConfig<NUM_DIM> &other) {
  if (this == &other) return *this;
  this->_domainConfig = other._domainConfig;
}

}
