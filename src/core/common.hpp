#ifndef __LADY_Common
#define __LADY_Common

#include <iostream>
#include <iomanip>
#include <vector>
#include <mlpack/core.hpp>
#include <armadillo>
#include "constants.hpp"

using std::cout;
using std::endl;
using std::setw;
using std::setprecision;
using std::vector;
using arma::uvec;
using arma::vec;
using arma::mat;
using arma::sp_mat;
using arma::field;
using arma::prod;

namespace lady {

typedef uvec::fixed<NUM_DIM> Uvec;
typedef vec::fixed<NUM_DIM> Vec;
typedef mat::fixed<NUM_DIM, NUM_DIM> Mat;

class CartesianDomain;
using DomainType = CartesianDomain;

class StructuredMeshConfig;
using MeshConfigType = StructuredMeshConfig;

class StructuredMesh;
using MeshType = StructuredMesh;

class StructuredFieldConfig;
using FieldConfigType = StructuredFieldConfig;

class StructuredField;
using FieldType = StructuredField;

}

#endif
