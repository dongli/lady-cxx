#ifndef __LADY_MeshConfig
#define __LADY_MeshConfig

#include "domain_config.hpp"

namespace lady {

template <int NUM_DIM>
class MeshConfig {
protected:
  const DomainConfig<NUM_DIM> *_domainConfig;
public:
  MeshConfig() {}
  MeshConfig(const DomainConfig<NUM_DIM> &domainConfig) {
    _domainConfig = &domainConfig;
  }
  virtual ~MeshConfig() {}

  const DomainConfig<NUM_DIM>& domainConfig() const {
    return *_domainConfig;
  }

  MeshConfig<NUM_DIM>& operator=(const MeshConfig<NUM_DIM> &other);
};

}

#endif
