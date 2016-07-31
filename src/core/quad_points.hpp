#ifndef __LADY_QuadPoints
#define __LADY_QuadPoints

#include "common.hpp"

namespace lady {

class Parcel;

class QuadPoints {
public:
  static vector<Vec> y;
  static vec w;
  Parcel *hostParcel;
  vector<Vec> x;
  vector<Vec> v;
  vec rho;
  vec T;

  QuadPoints();
  ~QuadPoints();

  static void init();

  void init(Parcel *parcel);

  void update();
};

}

#endif
