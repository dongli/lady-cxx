#ifndef __LADY_CartesianDomain2dFixture
#define __LADY_CartesianDomain2dFixture

#define private public
#define protected public
#include "lady/cartesian.hpp"

class CartesianDomain2dFixture {
public:
  lady::CartesianDomain<2> domain;

  CartesianDomain2dFixture() {
    lady::DomainConfig<2> domainConfig;
    domainConfig.axisStartCoords = { 0.0, 0.0 };
    domainConfig.axisEndCoords = { 100.0, 100.0 };
    domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
    domain.init(domainConfig);
  }
};

#endif
