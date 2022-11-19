include(FindPackageHandleStandardArgs)

include(FetchContent)
set(EIGEN_GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git")
message(STATUS "Fetching Eigen (version ${Eigen3_FIND_VERSION}) from ${EIGEN_GIT_REPOSITORY}")

FetchContent_Declare(
  Eigen
  GIT_REPOSITORY "${EIGEN_GIT_REPOSITORY}"
  GIT_TAG "${Eigen3_FIND_VERSION}"
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
seT(PROJECT_IS_TOP_LEVEL OFF)
set(EIGEN_BUILD_DOC OFF)
set(EIGEN_BUILD_SPBENCH OFF)
set(EIGEN_BUILD_BTL OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)
FetchContent_MakeAvailable(Eigen)
