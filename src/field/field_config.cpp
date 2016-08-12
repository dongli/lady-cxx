#include "field_config.hpp"
#include "cartesian_mesh_config.hpp"

namespace lady {

template class FieldConfig<2, CartesianMeshConfig>;
template class FieldConfig<3, CartesianMeshConfig>;

}
