#include "cartesian_domain.hpp"
#include "domain_metric.hpp"

namespace lady {

template class CartesianDomain<2>;
template class CartesianDomain<3>;

template <int NUM_DIM>
CartesianDomain<NUM_DIM>::CartesianDomain() {
  DomainMetric<CartesianDomain<NUM_DIM>>::init(this);
}

template <int NUM_DIM>
vec::fixed<NUM_DIM> CartesianDomain<NUM_DIM>::subCoord(const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &y) const {
  vec::fixed<NUM_DIM> res = x - y;
  for (int di = 0; di < NUM_DIM; di++) {
    if (this->_domainConfig.axisBoundaryTypes[di] == PERIODIC) {
      double tmp1 = std::abs(res[di]);
      double tmp2 = this->_domainConfig.axisSpans[di] - tmp1;
      if (tmp1 > tmp2) res[di] = res[di] > 0 ? -tmp2 : tmp2;
    }
    if (std::abs(res[di]) > this->_domainConfig.axisSpans[di]) {
      LOG_ERROR << "Coordinate is out of range!" << THROW_EXCEPTION;
    }
  }
  return res;
}

template <int NUM_DIM>
vec::fixed<NUM_DIM> CartesianDomain<NUM_DIM>::addCoord(const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &y) const {
  vec::fixed<NUM_DIM> res = x + y;
  for (int di = 0; di < NUM_DIM; di++) {
    if (res[di] < this->_domainConfig.axisStartCoords[di]) {
      if (this->_domainConfig.axisBoundaryTypes[di] == PERIODIC) {
        res[di] += this->_domainConfig.axisSpans[di];
      }
    } else if (res[di] > this->_domainConfig.axisEndCoords[di]) {
      if (this->_domainConfig.axisBoundaryTypes[di] == PERIODIC) {
        res[di] -= this->_domainConfig.axisSpans[di];
      }
    }
    if (res[di] < this->_domainConfig.axisStartCoords[di] || res[di] > this->_domainConfig.axisEndCoords[di]) {
      LOG_ERROR << "Coordiante is out of range!" << THROW_EXCEPTION;
    }
  }
  return res;
}

template <int NUM_DIM>
double CartesianDomain<NUM_DIM>::distance(const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &y) const {
  return norm(subCoord(x, y));
}

}
