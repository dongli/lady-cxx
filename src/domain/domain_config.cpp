#include "domain_config.hpp"

namespace lady {

template class DomainConfig<2>;
template class DomainConfig<3>;

template <int NUM_DIM>
DomainConfig<NUM_DIM>::DomainConfig() {
  axisBoundaryTypes.set_size(NUM_DIM);
}

template <int NUM_DIM>
DomainConfig<NUM_DIM>& DomainConfig<NUM_DIM>::operator=(const DomainConfig<NUM_DIM> &other) {
  if (this == &other) return *this;
  this->axisBoundaryTypes = other.axisBoundaryTypes;
  this->axisStartCoords = other.axisStartCoords;
  this->axisEndCoords = other.axisEndCoords;
  return *this;
}

}
