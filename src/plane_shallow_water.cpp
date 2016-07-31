#include "dycore.hpp"
#include "structured_field_config.hpp"

int main(int argc, char const *argv[]) {
  lady::DomainConfig domainConfig;
  lady::StructuredMeshConfig meshConfig(domainConfig);
  lady::Dycore dycore;

  domainConfig.axisStartCoords = { 0.0, 0.0 };
  domainConfig.axisEndCoords = { 1.0, 1.0 };
  domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
  meshConfig.numGridAlongEachAxis[0] = 5;
  meshConfig.numGridAlongEachAxis[1] = 5;
  dycore.init(meshConfig);

  lady::StructuredFieldConfig fieldConfig(meshConfig);
  lady::StructuredField p, T;

  fieldConfig.stagger = lady::StructuredFieldElementStagger::CENTER;
  p.init(fieldConfig);
  T.init(fieldConfig);

  p().fill(1);
  T().fill(1);
  dycore.inputData(0, p, T);

  dycore.run();

  return 0;
}
