#include "lady/cartesian.hpp"

int main(int argc, char const *argv[]) {
  lady::logger::init();

  lady::DomainConfig<2> domainConfig;
  lady::TimeConfig timeConfig;
  lady::CartesianMeshConfig<2> meshConfig(domainConfig);
  lady::Dycore<2, lady::CartesianField> dycore;

  timeConfig.startTime = "2016-08-21 00:00:00";
  timeConfig.endTime = "2016-08-21 00:01:00";
  timeConfig.timeStepSize = 1;
  lady::TimeManager::init(timeConfig);

  domainConfig.axisStartCoords = { 0.0, 0.0 };
  domainConfig.axisEndCoords = { 1.0, 1.0 };
  domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
  meshConfig.numGridAlongEachAxis[0] = 5;
  meshConfig.numGridAlongEachAxis[1] = 5;
  dycore.init(lady::BAROTROPIC, meshConfig);

  lady::CartesianFieldConfig<2> fieldConfig(meshConfig);
  lady::CartesianField<2> h, u, v;

  fieldConfig.stagger = lady::StructuredFieldElementStagger::CENTER;
  h.init(fieldConfig);
  u.init(fieldConfig);
  v.init(fieldConfig);

  h().fill(1);
  u().fill(0);
  v().fill(0);
  dycore.inputBarotropicData(h, u, v);
  dycore.output(0);

  // dycore.run();

  return 0;
}
