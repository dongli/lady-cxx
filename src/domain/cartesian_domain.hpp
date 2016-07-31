#ifndef __LADY_CartesianDomain
#define __LADY_CartesianDomain

#include "domain.hpp"

namespace lady {

class CartesianDomain : public Domain {
public:
  CartesianDomain() : Domain() {}
  virtual ~CartesianDomain() {}

  Vec diffCoord(const Vec &x, const Vec &y) const;

  double distance(const Vec &x, const Vec &y) const;
};

}

#endif
