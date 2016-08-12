#ifndef __LADY_Dycore
#define __LADY_Dycore

#include "common.hpp"
#include "parcel.hpp"
#include "quad_points.hpp"

#include "domain_metric.hpp"

namespace lady {

template <int NUM_DIM, template <int ...> class FieldTemplate>
class Dycore {
public:
  typedef FieldTemplate<NUM_DIM> FieldType;
  typedef typename FieldType::DomainType DomainType;
  typedef typename FieldType::MeshType MeshType;
  typedef RangeSearch<DomainMetric<DomainType>, mat, StandardCoverTree> SearchType;

private:
  vector<Parcel<NUM_DIM>> parcels[2];
  vector<QuadPoints<NUM_DIM>> quadPoints[2];
  DomainType domain;
  MeshType mesh;
  mat parcelCentroids;
  SearchType *neighborSearch;

  FieldType p;
  FieldType T;
  SearchType *meshSearch;

  int oldTi, newTi;

public:
  Dycore();
  ~Dycore();

  void init(const typename MeshType::MeshConfigType &meshConfig);

  void inputData(const FieldType &p, const FieldType &T);

  void run();

private:
  void findNeighbors(int ti);

  void calcForces(int ti);

  void regrid(int ti);

  void reorder(int ti);
};

}

#endif
