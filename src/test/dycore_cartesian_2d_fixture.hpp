#ifndef __LADY_DycoreCartesian2dFixture
#define __LADY_DycoreCartesian2dFixture

#define private public
#define protected public
#include "lady/cartesian.hpp"

class DycoreCartesian2dFixture {
public:
  lady::Dycore<2, lady::CartesianField> dycore;
  lady::CartesianField<2> p, T;

  DycoreCartesian2dFixture() {
    lady::DomainConfig<2> domainConfig;
    lady::CartesianMeshConfig<2> meshConfig(domainConfig);
    domainConfig.axisStartCoords = { 0.0, 0.0 };
    domainConfig.axisEndCoords = { 1.0, 1.0 };
    domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
    meshConfig.numGridAlongEachAxis[0] = 5;
    meshConfig.numGridAlongEachAxis[1] = 5;
    dycore.init(lady::BAROCLINIC, meshConfig);

    lady::CartesianFieldConfig<2> fieldConfig(meshConfig);
    fieldConfig.stagger = lady::CENTER;
    p.init(fieldConfig);
    T.init(fieldConfig);
  }
};

#endif
