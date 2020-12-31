## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")

set(WITH_MEMCHECK TRUE)
set(WITH_COVERAGE TRUE)

find_program(CTEST_GIT_COMMAND NAMES git)
find_program(CTEST_COVERAGE_COMMAND NAMES gcov)
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

if(NOT EXISTS "${CTEST_SOURCE_DIRECTORY}")
    set(CTEST_CHECKOUT_COMMAND "${CTEST_GIT_COMMAND} clone git://git@github.com:Ghettovich/bsf-lib.git ${CTEST_SOURCE_DIRECTORY}")
endif()

set(CTEST_UPDATE_COMMAND "${CTEST_GIT_COMMAND}")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "192.168.178.5:8082/cdash")
set(CTEST_DROP_LOCATION "/submit.php?project=bsf-lib")
set(CTEST_DROP_SITE_CDASH TRUE)
