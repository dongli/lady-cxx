#ifndef __LADY_StructuredMesh
#define __LADY_StructuredMesh

#include "mesh.hpp"
#include "structured_mesh_config.hpp"

namespace lady {

/**
 *  This class is not for direct use. Use CartesianMesh instead.
 */

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
class StructuredMesh : public Mesh<NUM_DIM, MeshConfigTemplate> {
public:
  typedef MeshConfigTemplate<NUM_DIM> MeshConfigType;

  StructuredMesh();
  virtual ~StructuredMesh();

  virtual void init(const MeshConfigType &meshConfig);
};

}

#endif
