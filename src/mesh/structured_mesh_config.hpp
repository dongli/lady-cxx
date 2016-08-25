#ifndef __LADY_StructuredMeshConfig
#define __LADY_StructuredMeshConfig

#include "mesh_config.hpp"

namespace lady {

template <int NUM_DIM>
class StructuredMeshConfig : public MeshConfig<NUM_DIM> {
public:
  uvec::fixed<NUM_DIM> numGridAlongEachAxis;

  StructuredMeshConfig() {}
  StructuredMeshConfig(const DomainConfig<NUM_DIM> &domainConfig);
  virtual ~StructuredMeshConfig();

  StructuredMeshConfig<NUM_DIM>& operator=(const StructuredMeshConfig<NUM_DIM> &other);
};

}

#endif
