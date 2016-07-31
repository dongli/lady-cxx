#include "shape_function.hpp"

namespace lady {

vec ShapeFunction::nodes;
vec ShapeFunction::weights;
const double ShapeFunction::J = 1.0 / 12.0;

void ShapeFunction::init() {
  nodes.set_size(5);
  nodes[0] = -2.0 / 3.0;
  nodes[1] = -1.0 / 3.0;
  nodes[2] =        0.0;
  nodes[3] =  1.0 / 3.0;
  nodes[4] =  2.0 / 3.0;
  weights.set_size(5);
  weights[0] =  41.0 / 1280.0;
  weights[1] = 316.0 / 1280.0;
  weights[2] = 566.0 / 1280.0;
  weights[3] = 316.0 / 1280.0;
  weights[4] =  41.0 / 1280.0;

}

void ShapeFunction::eval(const Vec &y, double &f) {
  f = 1.0;
  for (int i = 0; i < y.size(); ++i) {
    if (-1.0 <= y[i] && y[i] <= -0.5) {
      f *= 2.0 * pow(1.0 + y[i], 3.0);
    } else if (-0.5 <= y[i] && y[i] <= 0.0) {
      f *= 1.0 - 6.0 * pow(y[i], 2.0)*(1.0 + y[i]);
    } else if (0.0 <= y[i] && y[i] <= 0.5) {
      f *= 1.0 - 6.0 * pow(y[i], 2.0) * (1.0 - y[i]);
    } else if (0.5 <= y[i] && y[i] <= 1.0) {
      f *= 2.0 * pow(1.0 - y[i], 3.0);
    } else {
      f = 0.0;
      return;
    }
    f *= 4.0 / 3.0;
  }
}

void ShapeFunction::diff(const Vec &y, Vec &df) {
  df.ones();
  for (int i = 0; i < y.size(); ++i) {
    for (int j = 0; j < y.size(); ++j) {
      if (i == j) {
        if (-1.0 <= y[j] && y[j] <= -0.5) {
            df[i] *= 6.0 * pow(1.0 + y[j], 2.0);
        } else if (-0.5 <= y[j] && y[j] <= 0.0) {
            df[i] *= - 12.0 * y[j] - 18.0 * pow(y[j], 2.0);
        } else if (0.0 <= y[j] && y[j] <= 0.5) {
            df[i] *= - 12.0 * y[j] + 18.0 * pow(y[j], 2.0);
        } else if (0.5 <= y[j] && y[j] <= 1.0) {
            df[i] *= -6.0 * pow(1.0 - y[j], 2.0);
        } else {
            df[i] = 0.0;
            continue;
        }
      } else {
        if (-1.0 <= y[j] && y[j] <= -0.5) {
          df[i] *= 2.0 * pow(1.0 + y[j], 3.0);
        } else if (-0.5 <= y[j] && y[j] <= 0.0) {
          df[i] *= 1.0 - 6.0 * pow(y[j], 2.0) * (1.0 + y[j]);
        } else if (0.0 <= y[j] && y[j] <= 0.5) {
          df[i] *= 1.0 - 6.0 * pow(y[j], 2.0) * (1.0-y[j]);
        } else if (0.5 <= y[j] && y[j] <= 1.0) {
          df[i] *= 2.0 * pow(1.0 - y[j], 3.0);
        } else {
          df[i] = 0.0;
          continue;
        }
      }
      df[i] *= 4.0 / 3.0;
    }
  }
}

}
