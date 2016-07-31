#ifndef __LADY_StructuredMeshConfig
#define __LADY_StructuredMeshConfig

#include "mesh_config.hpp"

namespace lady {

class StructuredMeshConfig : public MeshConfig {
public:
  Uvec numGridAlongEachAxis;

  StructuredMeshConfig(const DomainConfig &domainConfig) : MeshConfig(domainConfig) {}
  virtual ~StructuredMeshConfig() {}
};

}

#endif
