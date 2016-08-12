#include "structured_field.hpp"
#include "structured_mesh_config.hpp"
#include "cartesian_mesh.hpp"

namespace lady {

template class StructuredField<2, CartesianMesh>;
template class StructuredField<3, CartesianMesh>;

template <int NUM_DIM, template <int ...> class MeshTemplate>
StructuredField<NUM_DIM, MeshTemplate>::StructuredField() {
}

template <int NUM_DIM, template <int ...> class MeshTemplate>
StructuredField<NUM_DIM, MeshTemplate>::~StructuredField() {
}

template <int NUM_DIM, template <int ...> class MeshTemplate>
void StructuredField<NUM_DIM, MeshTemplate>::init(const FieldConfig<NUM_DIM, MeshType::template MeshConfigTemplate> &fieldConfig) {
  auto meshConfig = static_cast<const typename MeshType::MeshConfigType&>(fieldConfig.meshConfig());
  if (NUM_DIM == 2) {
    this->_data.set_size(meshConfig.numGridAlongEachAxis[0],
                         meshConfig.numGridAlongEachAxis[1]);
  } else if (NUM_DIM == 3) {
    this->_data.set_size(meshConfig.numGridAlongEachAxis[0],
                         meshConfig.numGridAlongEachAxis[1],
                         meshConfig.numGridAlongEachAxis[2]);
  }
}

template <int NUM_DIM, template <int ...> class MeshTemplate>
StructuredField<NUM_DIM, MeshTemplate>& StructuredField<NUM_DIM, MeshTemplate>::operator=(const StructuredField<NUM_DIM, MeshTemplate> &other) {
  if (this == &other) return *this;
  this->_data.copy_size(other._data);
  this->_data = other._data;
}

}
