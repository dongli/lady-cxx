#include "io.hpp"
#include "cartesian_field.hpp"

namespace lady {

template class IO<2, CartesianField>;
template class IO<3, CartesianField>;

template <int NUM_DIM, template <int ...> class FieldTemplate>
string IO<NUM_DIM, FieldTemplate>::filePrefix;
template <int NUM_DIM, template <int ...> class FieldTemplate>
format IO<NUM_DIM, FieldTemplate>::fileNamePattern;
template <int NUM_DIM, template <int ...> class FieldTemplate>
time_duration IO<NUM_DIM, FieldTemplate>::outputInterval;

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::init(const string &_filePrefix, const time_duration &_outputInterval) {
  filePrefix = _filePrefix;
  outputInterval = _outputInterval;
  try {
    TimeManager::setAlert("output", outputInterval);
  } catch (const std::exception &e) {

  }
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::outputParcels(const vector<Parcel<NUM_DIM>> &parcels) {
  // format fileNamePattern(filePrefix + ".parcels.%1%.nc");
  // fileNamePattern % TimeManager::currTimeToString();
  format fileNamePattern(filePrefix + ".parcels.%1$05d.nc");
  fileNamePattern % TimeManager::timeStep;
  NcFile file(fileNamePattern.str(), NcFile::replace);

  NcDim timeDim = file.addDim("time");
  NcDim spaceDim = file.addDim("space", NUM_DIM);
  NcDim parcelDim = file.addDim("parcel", parcels.size());

  NcVar timeVar = file.addVar("time", ncFloat, timeDim);
  timeVar.putAtt("long_name", "time");
  format timeUnits("seconds since %1%");
  timeUnits % TimeManager::startTimeToString();
  timeVar.putAtt("units", timeUnits.str());

  NcVar idVar = file.addVar("id", ncInt, { timeDim, parcelDim });
  NcVar mVar = file.addVar("m", ncFloat, { timeDim, parcelDim });
  NcVar xVar = file.addVar("x", ncFloat, { timeDim, parcelDim, spaceDim });
  NcVar HVar = file.addVar("H", ncFloat, { timeDim, parcelDim, spaceDim, spaceDim });
  NcVar FpVar = file.addVar("Fp", ncFloat, { timeDim, parcelDim, spaceDim });

  int *dataInt = new int[parcels.size()];
  float *dataFloat = new float[NUM_DIM*NUM_DIM*parcels.size()];
  int i;
  vector<size_t> start, count;

  start = { 0 };
  count = { 1 };

  dataFloat[0] = TimeManager::elapsedSeconds();
  timeVar.putVar(start, count, dataFloat);

  start = { 0, 0 };
  count = { 1, parcels.size() };

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    dataInt[i++] = parcels[pi].id;
  }
  idVar.putVar(start, count, dataInt);

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    dataFloat[i++] = parcels[pi].m;
  }
  mVar.putVar(dataFloat);

  start = { 0, 0, 0 };
  count = { 1, parcels.size(), NUM_DIM };

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    for (int di = 0; di < NUM_DIM; di++) {
      dataFloat[i++] = parcels[pi].x[di];
    }
  }
  xVar.putVar(dataFloat);

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    for (int di = 0; di < NUM_DIM; di++) {
      dataFloat[i++] = parcels[pi].Fp[di];
    }
  }
  FpVar.putVar(dataFloat);

  start = { 0, 0, 0, 0 };
  count = { 1, parcels.size(), NUM_DIM, NUM_DIM };

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    for (int di2 = 0; di2 < NUM_DIM; di2++) {
      for (int di1 = 0; di1 < NUM_DIM; di1++) {
        dataFloat[i++] = parcels[pi].H(di1, di2);
      }
    }
  }
  HVar.putVar(dataFloat);

  delete [] dataInt;
  delete [] dataFloat;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::outputQuadPoints(const vector<QuadPoints<NUM_DIM>> &quadPoints) {
  // format fileNamePattern(filePrefix + ".quad_points.%1%.nc");
  // fileNamePattern % TimeManager::currTimeToString();
  format fileNamePattern(filePrefix + ".quad_points.%1$05d.nc");
  fileNamePattern % TimeManager::timeStep;
  NcFile file(fileNamePattern.str(), NcFile::replace);

  NcDim timeDim = file.addDim("time");
  NcDim parcelDim = file.addDim("parcel", quadPoints.size());
  NcDim quadPointDim = file.addDim("quad_point", QuadPoints<NUM_DIM>::num);
  NcDim spaceDim = file.addDim("space", NUM_DIM);

  NcVar timeVar = file.addVar("time", ncFloat, timeDim);
  timeVar.putAtt("long_name", "time");
  format timeUnits("seconds since %1%");
  timeUnits % TimeManager::startTimeToString();
  timeVar.putAtt("units", timeUnits.str());

  NcVar xVar = file.addVar("x", ncFloat, { timeDim, parcelDim, quadPointDim, spaceDim });
  NcVar rhoVar = file.addVar("rho", ncFloat, { timeDim, parcelDim, quadPointDim });
  NcVar vVar = file.addVar("v", ncFloat, { timeDim, parcelDim, quadPointDim, spaceDim });

  float *data = new float[quadPoints.size()*QuadPoints<NUM_DIM>::num*NUM_DIM];
  int i;
  vector<size_t> start, count;

  start = { 0 };
  count = { 1 };

  data[0] = TimeManager::elapsedSeconds();
  timeVar.putVar(start, count, data);

  start = { 0, 0, 0, 0 };
  count = { 1, quadPoints.size(), QuadPoints<NUM_DIM>::num, NUM_DIM };

  i = 0;
  for (int pi = 0; pi < quadPoints.size(); pi++) {
    for (int qi = 0; qi < QuadPoints<NUM_DIM>::num; qi++) {
      for (int di = 0; di < NUM_DIM; di++) {
        data[i++] = quadPoints[pi].x[qi][di];
      }
    }
  }
  xVar.putVar(start, count, data);

  i = 0;
  for (int pi = 0; pi < quadPoints.size(); pi++) {
    for (int qi = 0; qi < QuadPoints<NUM_DIM>::num; qi++) {
      for (int di = 0; di < NUM_DIM; di++) {
        data[i++] = quadPoints[pi].v[qi][di];
      }
    }
  }
  vVar.putVar(start, count, data);

  start = { 0, 0, 0 };
  count = { 1, quadPoints.size(), QuadPoints<NUM_DIM>::num };

  i = 0;
  for (int pi = 0; pi < quadPoints.size(); pi++) {
    for (int qi = 0; qi < QuadPoints<NUM_DIM>::num; qi++) {
      data[i++] = quadPoints[pi].rho[qi];
    }
  }
  rhoVar.putVar(start, count, data);

  delete [] data;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::outputBarotropicData(const DomainType &domain, const MeshType &mesh, const FieldType &h, const FieldType &u, const FieldType &v, double totalEnergy) {
  if (!TimeManager::alerts["output"].isOn()) return;

  // format fileNamePattern(filePrefix + ".fields.%1%.nc");
  // fileNamePattern % TimeManager::currTimeToString();
  format fileNamePattern(filePrefix + ".fields.%1$05d.nc");
  fileNamePattern % TimeManager::timeStep;
  NcFile file(fileNamePattern.str(), NcFile::replace);

  NcDim timeDim = file.addDim("time");
  NcDim xDim = file.addDim("x", mesh.numGridAlongX());
  NcDim yDim = file.addDim("y", mesh.numGridAlongY());

  NcVar timeVar = file.addVar("time", ncFloat, timeDim);
  NcVar xVar = file.addVar("x", ncFloat, xDim);
  NcVar yVar = file.addVar("y", ncFloat, yDim);

  timeVar.putAtt("long_name", "time");
  format timeUnits("seconds since %1%");
  timeUnits % TimeManager::startTimeToString();
  timeVar.putAtt("units", timeUnits.str());

  xVar.putAtt("long_name", "x");
  xVar.putAtt("units", "m");
  yVar.putAtt("long_name", "y");
  yVar.putAtt("units", "m");

  NcVar hVar = file.addVar("h", ncFloat, {timeDim, yDim, xDim});
  NcVar uVar = file.addVar("u", ncFloat, {timeDim, yDim, xDim});
  NcVar vVar = file.addVar("v", ncFloat, {timeDim, yDim, xDim});

  NcVar totalEnergyVar = file.addVar("total_energy", ncFloat, timeDim);
  totalEnergyVar.putAtt("long_name", "kinetic energy + geopotential energy");

  float *data = new float[mesh.numGrid()];
  int k;
  vector<size_t> start, count;

  start = { 0 };
  count = { 1 };

  data[0] = TimeManager::elapsedSeconds();
  timeVar.putVar(start, count, data);

  data[0] = totalEnergy;
  totalEnergyVar.putVar(start, count, data);

  start = { 0 };
  count = { mesh.numGridAlongX() };
  for (size_t i = 0; i < mesh.numGridAlongX(); i++) {
    data[i] = mesh.x(i);
  }
  xVar.putVar(start, count, data);

  start = { 0 };
  count = { mesh.numGridAlongY() };
  for (size_t j = 0; j < mesh.numGridAlongY(); j++) {
    data[j] = mesh.y(j);
  }
  yVar.putVar(start, count, data);

  start = { 0, 0, 0 };
  count = {
    1,
    static_cast<long unsigned int>(mesh.numGridAlongY()),
    static_cast<long unsigned int>(mesh.numGridAlongX())
  };

  k = 0;
  for (int j = 0; j < mesh.numGridAlongX(); j++) {
    for (int i = 0; i < mesh.numGridAlongY(); i++) {
      data[k++] = h(i, j);
    }
  }
  hVar.putVar(start, count, data);

  k = 0;
  for (int j = 0; j < mesh.numGridAlongX(); j++) {
    for (int i = 0; i < mesh.numGridAlongY(); i++) {
      data[k++] = u(i, j);
    }
  }
  uVar.putVar(start, count, data);

  k = 0;
  for (int j = 0; j < mesh.numGridAlongX(); j++) {
    for (int i = 0; i < mesh.numGridAlongY(); i++) {
      data[k++] = v(i, j);
    }
  }
  vVar.putVar(start, count, data);

  delete [] data;
}

}
