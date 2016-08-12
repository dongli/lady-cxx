#ifndef __LADY_StructuredMesh
#define __LADY_StructuredMesh

#include "mesh.hpp"
#include "structured_mesh_config.hpp"

namespace lady {

/**
 *  This class is not for direct use. Use CartesianMesh instead.
 */

template <int NUM_DIM>
class StructuredMesh : public Mesh<NUM_DIM> {
public:
  StructuredMesh();
  virtual ~StructuredMesh();

  virtual void init(const MeshConfig<NUM_DIM> &meshConfig);
};

}

#endif
