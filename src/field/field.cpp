#include "field.hpp"
#include "cartesian_mesh.hpp"

namespace lady {

template class Field<2, CartesianMesh>;
template class Field<3, CartesianMesh>;

template <int NUM_DIM, template <int ...> class MeshTemplate>
Field<NUM_DIM, MeshTemplate>::Field() {
}

template <int NUM_DIM, template <int ...> class MeshTemplate>
Field<NUM_DIM, MeshTemplate>::~Field() {
}

}
