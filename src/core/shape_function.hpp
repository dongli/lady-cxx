#ifndef __LADY_ShapeFunction
#define __LADY_ShapeFunction

#include "common.hpp"

namespace lady {

class ShapeFunction {
public:
  static vec nodes;
  static vec weights;
  static const double J;

  static void init();

  static void eval(const Vec &y, double &f);

  static void diff(const Vec &y, Vec &df);
};

}

#endif
