#ifndef _LADY_Domain
#define _LADY_Domain

#include "common.hpp"
#include "domain_config.hpp"

namespace lady {

template <int NUM_DIM>
class Domain {
protected:
  DomainConfig<NUM_DIM> _domainConfig;
public:
  Domain() {}
  virtual ~Domain() {}

  void init(const DomainConfig<NUM_DIM> &domainConfig);
};

}

#endif
