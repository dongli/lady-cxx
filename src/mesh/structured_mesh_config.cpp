#include "structured_mesh_config.hpp"

namespace lady {

template class StructuredMeshConfig<2>;
template class StructuredMeshConfig<3>;

template <int NUM_DIM>
StructuredMeshConfig<NUM_DIM>::StructuredMeshConfig(const DomainConfig<NUM_DIM> &domainConfig)
: MeshConfig<NUM_DIM>(domainConfig) {
}

template <int NUM_DIM>
StructuredMeshConfig<NUM_DIM>::~StructuredMeshConfig() {
}

}
