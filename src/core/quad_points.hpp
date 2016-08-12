#ifndef __LADY_QuadPoints
#define __LADY_QuadPoints

#include "common.hpp"

namespace lady {

template <int NUM_DIM> class Parcel;

template <int NUM_DIM>
class QuadPoints {
public:
  static vector<vec::fixed<NUM_DIM>> y;
  static vec w;
  static vec f;
  Parcel<NUM_DIM> *hostParcel;
  vector<vec::fixed<NUM_DIM>> x;
  vector<vec::fixed<NUM_DIM>> v;
  vec rho;
  vec T;

  static int num;

  QuadPoints();
  ~QuadPoints();

  static void init();

  void init(Parcel<NUM_DIM> *parcel);

  template <class DomainType>
  void update(const DomainType &domain);
};

}

#endif
