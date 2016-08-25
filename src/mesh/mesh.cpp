#include "mesh.hpp"
#include "cartesian_mesh_config.hpp"

namespace lady {

template class Mesh<2, CartesianMeshConfig>;
template class Mesh<3, CartesianMeshConfig>;

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
Mesh<NUM_DIM, MeshConfigTemplate>::Mesh() {
}

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
Mesh<NUM_DIM, MeshConfigTemplate>::~Mesh() {
}

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
void Mesh<NUM_DIM, MeshConfigTemplate>::init(const MeshConfigType &meshConfig) {
  this->meshConfig = meshConfig;
}

}
