#ifndef __LADY_Dycore
#define __LADY_Dycore

#include "common.hpp"
#include "parcel.hpp"
#include "quad_points.hpp"

#include "domain_metric.hpp"

namespace lady {

enum DycoreMode {
  BAROTROPIC, BAROCLINIC
};

template <int NUM_DIM, template <int ...> class FieldTemplate>
class Dycore {
public:
  typedef FieldTemplate<NUM_DIM> FieldType;
  typedef typename FieldType::DomainType DomainType;
  typedef typename FieldType::MeshType MeshType;
  typedef RangeSearch<DomainMetric<DomainType>, mat, StandardCoverTree> SearchType;

private:
  DycoreMode mode;
  double Rr;

  vector<Parcel<NUM_DIM>> parcels[2];
  vector<QuadPoints<NUM_DIM>> quadPoints[2];
  DomainType _domain;
  MeshType _mesh;
  mat parcelCentroids;
  SearchType *neighborSearch;

  FieldType V[NUM_DIM];
  SearchType *meshSearch;

  // For BAROTROPIC mode
  FieldType h;

  // For BAROCLINIC mode
  FieldType p;
  FieldType T;

  int oldTi, newTi;

public:
  Dycore();
  ~Dycore();

  void init(const DycoreMode mode, const typename MeshType::MeshConfigType &meshConfig);

  void inputBarotropicData(const FieldType &h, const FieldType &u, const FieldType &v);

  void inputBaroclinicData(const FieldType &p, const FieldType &T);

  void run();

  void output();

  const DomainType& domain() const { return _domain; }

  const MeshType& mesh() const { return _mesh; }

private:
  void findNeighbors(int ti);

  void updateQuadPoints(int ti);

  void calcForces(int ti);

  void calcHeats(int ti);

  void regridBarotropicData(int ti);

  void regridBaroclinicData(int ti);

  void reorder(int ti);

  void restart(int ti);
};

}

#endif
