#include "lady/cartesian.hpp"

int main(int argc, char const *argv[]) {
  lady::logger::init();

  lady::DomainConfig<2> domainConfig;
  lady::TimeConfig timeConfig;
  lady::CartesianMeshConfig<2> meshConfig(domainConfig);
  lady::Dycore<2, lady::CartesianField> dycore;

  timeConfig.startTime = "2016-08-21 00:00:00";
  timeConfig.endTime = "2016-08-21 00:00:10";
  timeConfig.timeStepSize = 0.5;
  lady::TimeManager::init(timeConfig);

  domainConfig.axisStartCoords = { 0.0, 0.0 };
  domainConfig.axisEndCoords = { 100.0, 100.0 };
  domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
  meshConfig.numGridAlongEachAxis[0] = 20;
  meshConfig.numGridAlongEachAxis[1] = 20;
  dycore.init(lady::BAROTROPIC, meshConfig);

  lady::CartesianFieldConfig<2> fieldConfig(meshConfig);
  lady::CartesianField<2> h, u, v;

  fieldConfig.stagger = lady::StructuredFieldElementStagger::CENTER;
  h.init(fieldConfig);
  u.init(fieldConfig);
  v.init(fieldConfig);

  u().fill(0);
  v().fill(0);
  arma::vec::fixed<2> x0 = { 50.0, 50.0 };
  for (size_t i = 0; i < dycore.mesh().numGrid(); i++) {
    auto x = dycore.mesh().gridCoord(i);
    h(i) = 1.0 + exp(- 0.4 * norm(x - x0)) * 0.01;
    // h(i) = 1.0 + exp(- 0.4 * fabs(x[0] - x0[0])) * 0.01;
  }

  dycore.inputBarotropicData(h, u, v);
  dycore.output();

  while (!lady::TimeManager::isFinished()) {
    dycore.run();
    lady::TimeManager::advance();
    lady::TimeManager::printTime();
    dycore.output();
  }

  return 0;
}
