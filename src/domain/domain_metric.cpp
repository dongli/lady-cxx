#include "domain_metric.hpp"
#include "cartesian_domain.hpp"

namespace lady {

template class DomainMetric<CartesianDomain<2>>;
template class DomainMetric<CartesianDomain<3>>;

template <class DomainType>
const DomainType* DomainMetric<DomainType>::_domain = NULL;

template <class DomainType>
void DomainMetric<DomainType>::init(const DomainType *domain) {
  _domain = domain;
}

}
