#ifndef __LADY_CartesianDomain
#define __LADY_CartesianDomain

#include "domain.hpp"

namespace lady {

template <int NUM_DIM>
class CartesianDomain : public Domain<NUM_DIM> {
public:
  CartesianDomain();
  virtual ~CartesianDomain() {}

  vec::fixed<NUM_DIM> subCoord(const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &y) const;
  vec::fixed<NUM_DIM> addCoord(const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &y) const;

  double distance(const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &y) const;
};

}

#endif
