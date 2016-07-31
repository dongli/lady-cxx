#ifndef __LADY_Dycore
#define __LADY_Dycore

#include "common.hpp"
#include "neighbor_search.hpp"
#include "parcel.hpp"
#include "quad_points.hpp"

#include "cartesian_domain.hpp"
#include "structured_mesh.hpp"
#include "structured_field.hpp"

namespace lady {

class Dycore {
  vector<Parcel> parcels[2];
  vector<QuadPoints> quadPoints[2];
  DomainType domain;
  MeshType mesh;

  mat parcelCentroids;
  SearchType *neighborSearch;

public:
  Dycore();
  ~Dycore();

  void init(const MeshConfigType &meshConfig);

  void inputData(int ti, const FieldType &p, const FieldType &T);

  void run();

private:
  void findNeighbors(int ti);
};

}

#endif
