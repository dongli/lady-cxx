#ifndef __LADY_Parcel
#define __LADY_Parcel

#include "common.hpp"

namespace lady {

class Parcel {
public:
  int id;
  double m;
  double u;
  Vec x;
  Vec v;
  Mat H;
  Mat dH;
  Mat invH;
  Mat U;
  Mat V;
  Vec S;
  double detH;
  Vec Fp;
  Vec Mp;
  Vec Fr;
  Vec Mr;
  double Q;

  int numNeighbor;
  vector<Parcel*> neighbors;

  Parcel();
  ~Parcel();

  void init(int id, const Vec &x, const Vec &size);

  double shapeSize(int ai) const { return S[ai]; }

  void getBodyCoord(const Vec &x, Vec &y) const;

  void getSpaceCoord(const Vec &y, Vec &x) const;

  void getLocalVelocity(const Vec &y, Vec &v) const;

  void getShapeFunctionDerivatives(const Vec &y, double f, Vec &dfdx, Vec &dfdH) const;

  void afterMatrixChanged();
};

}

#endif
