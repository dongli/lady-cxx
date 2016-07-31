#ifndef __LADY_MeshConfig
#define __LADY_MeshConfig

#include "domain_config.hpp"

namespace lady {

class MeshConfig {
protected:
  const DomainConfig *_domainConfig;
public:
  MeshConfig(const DomainConfig &domainConfig) {
    _domainConfig = &domainConfig;
  }
  virtual ~MeshConfig() {}

  const DomainConfig& domainConfig() const {
    return *_domainConfig;
  }
};

}

#endif
