#ifndef __LADY_CartesianMesh
#define __LADY_CartesianMesh

#include "structured_mesh.hpp"
#include "cartesian_mesh_config.hpp"
#include "cartesian_domain.hpp"

namespace lady {

template <int NUM_DIM>
class CartesianMesh : public StructuredMesh<NUM_DIM> {
public:
  typedef CartesianDomain<NUM_DIM> DomainType;
  template <int _NUM_DIM>
  using MeshConfigTemplate = CartesianMeshConfig<_NUM_DIM>;
  typedef CartesianMeshConfig<NUM_DIM> MeshConfigType;

  CartesianMesh();
  virtual ~CartesianMesh();
};

}

#endif
