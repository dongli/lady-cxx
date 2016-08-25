#ifndef __LADY_IO
#define __LADY_IO

#include "common.hpp"
#include <netcdf>
#include "parcel.hpp"

using namespace netCDF;

namespace lady {

template <int NUM_DIM, template <int ...> class FieldTemplate>
class IO {
public:
  typedef FieldTemplate<NUM_DIM> FieldType;
  typedef typename FieldType::DomainType DomainType;
  typedef typename FieldType::MeshType MeshType;
private:
  static format fileNamePattern;
public:
  static void init(const string &fileNamePattern);

  static void outputParcels(const vector<Parcel<NUM_DIM>> &parcels);

  static void outputBarotropicData(const DomainType &domain, const MeshType &mesh, const FieldType &h, const FieldType &u, const FieldType &v);

  static void outputBaroclinicData(const FieldType &p, const FieldType &T);
};

}

#endif
