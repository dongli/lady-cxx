#ifndef __LADY_StructuredField
#define __LADY_StructuredField

#include "field.hpp"
#include "structured_field_config.hpp"

namespace lady {

template <int NUM_DIM, template <int ...> class MeshTemplate>
class StructuredField : public Field<NUM_DIM, MeshTemplate> {
public:
  typedef MeshTemplate<NUM_DIM> MeshType;
private:
  field<double> _data;
public:
  StructuredField();
  virtual ~StructuredField();

  void init(const FieldConfig<NUM_DIM, MeshType::template MeshConfigTemplate> &fieldConfig);

  double operator()(int i) const { return _data(i); }
  double& operator()(int i) { return _data(i); }
  double operator()(int i, int j) const { return _data(i, j); }
  double& operator()(int i, int j) { return _data(i, j); }
  double operator()(int i, int j, int k) const { return _data(i, j, k); }
  double& operator()(int i, int j, int k) { return _data(i, j, k); }
  field<double>& operator()() { return _data; }

  StructuredField<NUM_DIM, MeshTemplate>& operator=(const StructuredField<NUM_DIM, MeshTemplate> &other);
};

}

#endif
