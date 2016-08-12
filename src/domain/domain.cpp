#include "domain.hpp"
#include "domain_metric.hpp"

namespace lady {

template class Domain<2>;
template class Domain<3>;

template <int NUM_DIM>
void Domain<NUM_DIM>::init(const DomainConfig<NUM_DIM> &domainConfig) {
  _domainConfig = domainConfig;
  _domainConfig.axisSpans = _domainConfig.axisEndCoords - _domainConfig.axisStartCoords;
}

}
