## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(CTEST_PROJECT_NAME CMake)
set(dashboard_user_home "$ENV{HOME}")

# Select the top dashboard directory.
if(NOT DEFINED dashboard_root_name)
    set(dashboard_root_name "My Tests")
endif()
if(NOT DEFINED CTEST_DASHBOARD_ROOT)
    get_filename_component(CTEST_DASHBOARD_ROOT "${CTEST_SCRIPT_DIRECTORY}/../${dashboard_root_name}" ABSOLUTE)
endif()

# Select the model (Nightly, Experimental, Continuous).
if(NOT DEFINED dashboard_model)
    set(dashboard_model Nightly)
endif()
if(NOT "${dashboard_model}" MATCHES "^(Nightly|Experimental|Continuous)$")
    message(FATAL_ERROR "dashboard_model must be Nightly, Experimental, or Continuous")
endif()


set(CTEST_PROJECT_NAME "First project")
set(CTEST_NIGHTLY_START_TIME "20:53:00 UTC")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "192.168.178.5:8082")
set(CTEST_DROP_LOCATION "/cdash/submit.php?project=First+project")
set(CTEST_DROP_SITE_CDASH TRUE)