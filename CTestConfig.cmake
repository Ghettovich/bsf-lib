## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "192.168.178.5:8082/cdash")
set(CTEST_DROP_LOCATION "/submit.php?project=bsf-lib")
set(CTEST_DROP_SITE_CDASH TRUE)
