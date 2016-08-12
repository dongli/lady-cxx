#ifndef __LADY_CartesianMeshConfig
#define __LADY_CartesianMeshConfig

#include "structured_mesh_config.hpp"

namespace lady {

template <int NUM_DIM>
class CartesianMeshConfig : public StructuredMeshConfig<NUM_DIM> {
public:
  CartesianMeshConfig(const DomainConfig<NUM_DIM> &domainConfig);
  virtual ~CartesianMeshConfig();
};

}

#endif
