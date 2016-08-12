#include "lady/cartesian.hpp"

int main(int argc, char const *argv[]) {
  lady::logger::init();

  lady::DomainConfig<2> domainConfig;
  lady::CartesianMeshConfig<2> meshConfig(domainConfig);
  lady::Dycore<2, lady::CartesianField> dycore;

  domainConfig.axisStartCoords = { 0.0, 0.0 };
  domainConfig.axisEndCoords = { 1.0, 1.0 };
  domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
  meshConfig.numGridAlongEachAxis[0] = 5;
  meshConfig.numGridAlongEachAxis[1] = 5;
  dycore.init(meshConfig);

  lady::CartesianFieldConfig<2> fieldConfig(meshConfig);
  lady::CartesianField<2> p, T;

  fieldConfig.stagger = lady::StructuredFieldElementStagger::CENTER;
  p.init(fieldConfig);
  T.init(fieldConfig);

  p().fill(1);
  T().fill(1);
  dycore.inputData(p, T);

  dycore.run();

  return 0;
}
