#ifndef __LADY_IO
#define __LADY_IO

#include <netcdf>
#include "common.hpp"
#include "time_manager.hpp"
#include "parcel.hpp"
#include "quad_points.hpp"

using namespace netCDF;

namespace lady {

template <int NUM_DIM, template <int ...> class FieldTemplate>
class IO {
public:
  typedef FieldTemplate<NUM_DIM> FieldType;
  typedef typename FieldType::DomainType DomainType;
  typedef typename FieldType::MeshType MeshType;
private:
  static string filePrefix;
  static format fileNamePattern;
  static time_duration outputInterval;
public:
  static void init(const string &fileNamePattern, const time_duration &outputInterval);

  static void outputParcels(const vector<Parcel<NUM_DIM>> &parcels);

  static void outputQuadPoints(const vector<QuadPoints<NUM_DIM>> &quadPoints);

  static void outputBarotropicData(const DomainType &domain, const MeshType &mesh, const FieldType &h, const FieldType &u, const FieldType &v);

  static void outputBaroclinicData(const FieldType &p, const FieldType &T);
};

}

#endif
