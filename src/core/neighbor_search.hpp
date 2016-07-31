#ifndef __LADY_NeighborSearch
#define __LADY_NeighborSearch

#include "common.hpp"
#include "domain_metric.hpp"
#include <mlpack/core/tree/cover_tree.hpp>
#include <mlpack/methods/range_search/range_search.hpp>

namespace lady {

using SearchType = mlpack::range::RangeSearch<DomainMetric, mat, mlpack::tree::StandardCoverTree>;
using RangeType = mlpack::math::Range;

}

#endif
