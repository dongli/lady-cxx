#ifndef __LADY_Parcel
#define __LADY_Parcel

#include "common.hpp"

namespace lady {

template <int NUM_DIM>
class Parcel {
public:
  int id;
  double m;
  double u;
  vec::fixed<NUM_DIM> x;
  vec::fixed<NUM_DIM> v;
  mat::fixed<NUM_DIM, NUM_DIM> H;
  mat::fixed<NUM_DIM, NUM_DIM> dH;
  mat::fixed<NUM_DIM, NUM_DIM> invH;
  mat::fixed<NUM_DIM, NUM_DIM> U;
  mat::fixed<NUM_DIM, NUM_DIM> V;
  vec::fixed<NUM_DIM> S;
  double detH;
  vec::fixed<NUM_DIM> Fp;
  vec::fixed<NUM_DIM> Mp;
  vec::fixed<NUM_DIM> Fr;
  vec::fixed<NUM_DIM> Mr;
  double Q;

  int numNeighbor;
  vector<Parcel*> neighbors;

  Parcel();
  ~Parcel();

  void init(int id, const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &size);

  double shapeSize(int ai) const { return S[ai]; }

  template <class DomainType>
  void getBodyCoord(const DomainType &domain, const vec::fixed<NUM_DIM> &x, vec::fixed<NUM_DIM> &y) const {
    y = invH * domain.subCoord(x, this->x);
  }

  template <class DomainType>
  void getSpaceCoord(const DomainType &domain, const vec::fixed<NUM_DIM> &y, vec::fixed<NUM_DIM> &x) const {
    x = domain.addCoord(this->x, H * y);
  }

  void getLocalVelocity(const vec::fixed<NUM_DIM> &y, vec::fixed<NUM_DIM> &v) const;

  void getShapeFunctionDerivatives(const vec::fixed<NUM_DIM> &y, double f, vec::fixed<NUM_DIM> &dfdx, vec::fixed<NUM_DIM> &dfdH) const;

  void afterMatrixChanged();
};

}

#endif
