cmake_minimum_required (VERSION 2.8)

project (lady CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories ("$ENV{MLPACK_ROOT}/include")
link_directories ("$ENV{MLPACK_ROOT}/lib")

include_directories ("$ENV{ARMADILLO_ROOT}/include")
link_directories ("$ENV{ARMADILLO_ROOT}/lib")

set (BOOST_ROOT "$ENV{BOOST_ROOT}")
add_definitions(-DBOOST_LOG_DYN_LINK=1)
find_package (Boost 1.54.0 COMPONENTS log date_time timer REQUIRED)
include_directories ("${Boost_INCLUDE_DIRS}")

include_directories ("$ENV{NETCDF_ROOT}/include")
link_directories ("$ENV{NETCDF_ROOT}/lib")

set (lady_directories
  "${PROJECT_SOURCE_DIR}/src/util"
  "${PROJECT_SOURCE_DIR}/src/domain"
  "${PROJECT_SOURCE_DIR}/src/mesh"
  "${PROJECT_SOURCE_DIR}/src/field"
  "${PROJECT_SOURCE_DIR}/src/core"
)

foreach (dir ${lady_directories})
  include_directories ("${dir}")
  # header files
  file (GLOB tmp "${dir}/*.hpp")
  list (APPEND lady_headers ${tmp})
  # source files
  file (GLOB tmp "${dir}/*.cpp")
  list (APPEND lady_sources ${tmp})
endforeach ()

add_library (lady ${lady_headers} ${lady_sources})
target_link_libraries (lady mlpack netcdf_c++4 netcdf ${Boost_LIBRARIES})

set (test_directories
  "${PROJECT_SOURCE_DIR}/src/test"
)

foreach (dir ${test_directories})
  include_directories ("${dir}")
  # header files
  file (GLOB tmp "${dir}/*.hpp")
  list (APPEND test_headers ${tmp})
  # source files
  file (GLOB tmp "${dir}/*.cpp")
  list (APPEND test_sources ${tmp})
endforeach ()

include_directories ("${PROJECT_SOURCE_DIR}/src")
add_executable (test_lady ${test_headers} ${test_sources})
target_link_libraries (test_lady lady mlpack armadillo ${Boost_LIBRARIES})

add_executable (shallow_water_driver "${PROJECT_SOURCE_DIR}/src/shallow_water_driver.cpp")
target_link_libraries (shallow_water_driver lady mlpack armadillo ${Boost_LIBRARIES})
