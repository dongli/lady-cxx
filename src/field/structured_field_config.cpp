#include "structured_field_config.hpp"
#include "cartesian_mesh_config.hpp"

namespace lady {

template class StructuredFieldConfig<2, CartesianMeshConfig>;
template class StructuredFieldConfig<3, CartesianMeshConfig>;

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
StructuredFieldConfig<NUM_DIM, MeshConfigTemplate>::StructuredFieldConfig(const MeshConfigTemplate<NUM_DIM> &meshConfig)
: FieldConfig<NUM_DIM, MeshConfigTemplate>(meshConfig) {
}

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
StructuredFieldConfig<NUM_DIM, MeshConfigTemplate>::~StructuredFieldConfig() {
}

}
