#ifndef __LADY_StructuredField
#define __LADY_StructuredField

#include "field.hpp"
#include "structured_field_config.hpp"

namespace lady {

class StructuredField : public Field {
  field<double> _data;
public:
  StructuredField();
  virtual ~StructuredField();

  void init(const StructuredFieldConfig &fieldConfig);

  double operator()(int i) const { return _data(i); }
  double& operator()(int i) { return _data(i); }
  double operator()(int i, int j) const { return _data(i, j); }
  double& operator()(int i, int j) { return _data(i, j); }
  double operator()(int i, int j, int k) const { return _data(i, j, k); }
  double& operator()(int i, int j, int k) { return _data(i, j, k); }
  field<double>& operator()() { return _data; }
};

}

#endif
