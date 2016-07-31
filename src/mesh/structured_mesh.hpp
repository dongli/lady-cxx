#ifndef __LADY_StructuredMesh
#define __LADY_StructuredMesh

#include "mesh.hpp"
#include "structured_mesh_config.hpp"

namespace lady {

class StructuredMesh : public Mesh {
public:
  StructuredMesh();
  virtual ~StructuredMesh();

  void init(const StructuredMeshConfig &config);
};

}

#endif
