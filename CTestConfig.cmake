## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

# Select the model (Nightly, Experimental, Continuous).
if(NOT DEFINED dashboard_model)
    set(dashboard_model Nightly)
endif()
if(NOT "${dashboard_model}" MATCHES "^(Nightly|Experimental|Continuous)$")
    message(FATAL_ERROR "dashboard_model must be Nightly, Experimental, or Continuous")
endif()

set(CTEST_PROJECT_NAME "bsf-lib")
set(CTEST_NIGHTLY_START_TIME "22:00:00 UTC")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "192.168.178.5:8082/cdash")
set(CTEST_DROP_LOCATION "/submit.php?project=bsf-lib")
set(CTEST_DROP_SITE_CDASH TRUE)

set(CTEST_UPDATE_COMMAND "${CTEST_GIT_COMMAND}")

set(CTEST_CONFIGURE_COMMAND "${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=${CTEST_BUILD_CONFIGURATION}")
set(CTEST_CONFIGURE_COMMAND "${CTEST_CONFIGURE_COMMAND} -DWITH_TESTING:BOOL=ON ${CTEST_BUILD_OPTIONS}")
set(CTEST_CONFIGURE_COMMAND "${CTEST_CONFIGURE_COMMAND} \"-G${CTEST_CMAKE_GENERATOR}\"")
set(CTEST_CONFIGURE_COMMAND "${CTEST_CONFIGURE_COMMAND} \"${CTEST_SOURCE_DIRECTORY}\"")

if(WITH_COVERAGE AND CTEST_COVERAGE_COMMAND)
    ctest_coverage()
endif()
if(WITH_MEMCHECK AND CTEST_MEMORYCHECK_COMMAND)
    ctest_memcheck()
endif()
