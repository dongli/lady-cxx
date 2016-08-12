#ifndef __LADY_Field
#define __LADY_Field

#include "common.hpp"

namespace lady {

template <int NUM_DIM, template <int ...> class MeshTemplate>
class Field {
public:
  typedef MeshTemplate<NUM_DIM> MeshType;
  typedef typename MeshType::DomainType DomainType;

  Field();
  virtual ~Field();
};

}

#endif
