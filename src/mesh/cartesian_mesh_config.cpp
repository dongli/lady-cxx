#include "cartesian_mesh_config.hpp"

namespace lady {

template class CartesianMeshConfig<2>;
template class CartesianMeshConfig<3>;

template <int NUM_DIM>
CartesianMeshConfig<NUM_DIM>::CartesianMeshConfig(const DomainConfig<NUM_DIM> &domainConfig)
: StructuredMeshConfig<NUM_DIM>(domainConfig) {
}

template <int NUM_DIM>
CartesianMeshConfig<NUM_DIM>::~CartesianMeshConfig() {
}

}
