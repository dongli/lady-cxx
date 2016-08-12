#ifndef __LADY_ShapeFunction
#define __LADY_ShapeFunction

#include "common.hpp"

namespace lady {

template <int NUM_DIM>
class ShapeFunction {
public:
  static vec nodes;
  static vec weights;
  static const double C;
  static const double J;

  static void init();

  static void eval(const vec::fixed<NUM_DIM> &y, double &f);

  static void diff(const vec::fixed<NUM_DIM> &y, vec::fixed<NUM_DIM> &df);
};

}

#endif
