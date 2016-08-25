#include "io.hpp"
#include "time_manager.hpp"
#include "cartesian_field.hpp"

namespace lady {

template class IO<2, CartesianField>;
template class IO<3, CartesianField>;

template <int NUM_DIM, template <int ...> class FieldTemplate>
format IO<NUM_DIM, FieldTemplate>::fileNamePattern;

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::init(const string &_fileNamePattern) {
  fileNamePattern = format(_fileNamePattern);
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::outputParcels(const vector<Parcel<NUM_DIM>> &parcels) {
  fileNamePattern % TimeManager::currTimeToString();
  NcFile file(fileNamePattern.str(), NcFile::replace);

  NcDim spaceDim = file.addDim("space", NUM_DIM);
  NcDim parcelDim = file.addDim("parcel", parcels.size());

  vector<NcDim> parcelSpaceDims = { parcelDim, spaceDim };
  vector<NcDim> parcelSpaceSpaceDims = { parcelDim, spaceDim, spaceDim };

  NcVar mVar = file.addVar("m", ncFloat, parcelDim);
  NcVar xVar = file.addVar("x", ncFloat, parcelSpaceDims);
  NcVar HVar = file.addVar("H", ncFloat, parcelSpaceSpaceDims);

  double *data = new double[NUM_DIM*NUM_DIM*parcels.size()];
  int i;

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    data[i++] = parcels[pi].m;
  }
  mVar.putVar(data);

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    for (int di = 0; di < NUM_DIM; di++) {
      data[i++] = parcels[pi].x[di];
    }
  }
  xVar.putVar(data);

  i = 0;
  for (int pi = 0; pi < parcels.size(); pi++) {
    for (int di2 = 0; di2 < NUM_DIM; di2++) {
      for (int di1 = 0; di1 < NUM_DIM; di1++) {
        data[i++] = parcels[pi].H(di1, di2);
      }
    }
  }
  HVar.putVar(data);

  delete [] data;
}

template <int NUM_DIM, template <int ...> class FieldTemplate>
void IO<NUM_DIM, FieldTemplate>::outputBarotropicData(const DomainType &domain, const MeshType &mesh, const FieldType &h, const FieldType &u, const FieldType &v) {
  fileNamePattern % TimeManager::currTimeToString();
  NcFile file(fileNamePattern.str(), NcFile::replace);

  NcDim timeDim = file.addDim("time");
  NcDim xDim = file.addDim("x", mesh.numGridAlongX());
  NcDim yDim = file.addDim("y", mesh.numGridAlongY());

  NcVar timeVar = file.addVar("time", ncFloat, timeDim);
  NcVar xVar = file.addVar("x", ncFloat, xDim);
  NcVar yVar = file.addVar("y", ncFloat, yDim);

  NcVar hVar = file.addVar("h", ncFloat, {timeDim, yDim, xDim});
  NcVar uVar = file.addVar("u", ncFloat, {timeDim, yDim, xDim});
  NcVar vVar = file.addVar("v", ncFloat, {timeDim, yDim, xDim});

  double *data = new double[mesh.numGrid()];
  int k;

  k = 0;
  for (int j = 0; j < mesh.numGridAlongX(); j++) {
    for (int i = 0; i < mesh.numGridAlongY(); i++) {
      data[k++] = h(i, j);
    }
  }
  hVar.putVar(data);

  k = 0;
  for (int j = 0; j < mesh.numGridAlongX(); j++) {
    for (int i = 0; i < mesh.numGridAlongY(); i++) {
      data[k++] = u(i, j);
    }
  }
  uVar.putVar(data);

  k = 0;
  for (int j = 0; j < mesh.numGridAlongX(); j++) {
    for (int i = 0; i < mesh.numGridAlongY(); i++) {
      data[k++] = v(i, j);
    }
  }
  vVar.putVar(data);

  delete [] data;
}

}
