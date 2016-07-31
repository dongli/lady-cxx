#ifndef __LADY_DomainMetric
#define __LADY_DomainMetric

#include "common.hpp"
#include "cartesian_domain.hpp"

namespace lady {

class DomainMetric : public mlpack::metric::LMetric<2> {
  static const DomainType *_domain;
public:
  DomainMetric() {}

  static void init(const Domain *domain);

  template <typename VecTypeA, typename VecTypeB>
  static double Evaluate(const VecTypeA &x, const VecTypeB &y) {
    return _domain->distance(x, y);
  }
};

}

#endif
