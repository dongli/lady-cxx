#include "domain.hpp"
#include "domain_metric.hpp"

namespace lady {

void Domain::init(const DomainConfig &domainConfig) {
  _domainConfig = &domainConfig;
  DomainMetric::init(this);
}

}
