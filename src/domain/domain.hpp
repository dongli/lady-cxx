#ifndef _LADY_Domain
#define _LADY_Domain

#include "common.hpp"
#include "domain_config.hpp"

namespace lady {

class Domain {
protected:
  const DomainConfig *_domainConfig;
public:
  Domain() {}
  virtual ~Domain() {}

  void init(const DomainConfig &domainConfig);
};

}

#endif
