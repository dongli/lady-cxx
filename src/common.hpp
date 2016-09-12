#ifndef __LADY_Common
#define __LADY_Common

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <boost/format.hpp>
#include <boost/timer/timer.hpp>
#include <mlpack/core.hpp>
#include <armadillo>
#include <mlpack/core/tree/cover_tree.hpp>
#include <mlpack/methods/range_search/range_search.hpp>

using std::cout;
using std::endl;
using std::stringstream;
using std::setw;
using std::setfill;
using std::setprecision;
using std::vector;
using std::map;
using std::string;

using boost::format;
using boost::timer::cpu_timer;
using boost::timer::auto_cpu_timer;

using arma::uvec;
using arma::vec;
using arma::mat;
using arma::sp_mat;
using arma::field;
using arma::prod;

using namespace mlpack::tree;
using namespace mlpack::range;
using mlpack::math::Range;

#include "constants.hpp"
#include "logger.hpp"
#include "timer.hpp"

#endif
