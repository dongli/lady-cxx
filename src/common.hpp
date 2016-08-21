#ifndef __LADY_Common
#define __LADY_Common

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <mlpack/core.hpp>
#include <armadillo>
#include <mlpack/core/tree/cover_tree.hpp>
#include <mlpack/methods/range_search/range_search.hpp>
#include "constants.hpp"
#include "logger.hpp"

using std::cout;
using std::endl;
using std::setw;
using std::setprecision;
using std::vector;
using std::map;
using std::string;
using arma::uvec;
using arma::vec;
using arma::mat;
using arma::sp_mat;
using arma::field;
using arma::prod;

using namespace mlpack::tree;
using namespace mlpack::range;
using mlpack::math::Range;

#endif
