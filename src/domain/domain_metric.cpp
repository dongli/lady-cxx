#include "domain_metric.hpp"

namespace lady {

const DomainType* DomainMetric::_domain = NULL;

void DomainMetric::init(const Domain *domain) {
  _domain = static_cast<const DomainType*>(domain);
}

}
