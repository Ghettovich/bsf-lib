## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
#enable_testing()
#include(CTest)
#cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
#
#set(CTEST_SOURCE_DIRECTORY "${CTEST_SCRIPT_DIRECTORY}")
#set(CTEST_BINARY_DIRECTORY "${CTEST_SCRIPT_DIRECTORY}/cmake-build-debug")
#
#set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
#set(CTEST_MEMORYCHECK_TYPE "ThreadSanitizer")
#ctest_start(Experimental)
#
##set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")
#
#set(CTEST_DROP_METHOD "http")
#set(CTEST_DROP_SITE "192.168.178.5/cdash")
#set(CTEST_DROP_LOCATION "/submit.php?project=basalt")
#set(CTEST_DROP_SITE_CDASH TRUE)
#
#set(WITH_MEMCHECK TRUE)
#set(WITH_COVERAGE TRUE)
#
#find_program(CTEST_GIT_COMMAND NAMES git)
#find_program(CTEST_COVERAGE_COMMAND NAMES gcov)
#find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
#
#if(NOT EXISTS "${CTEST_SOURCE_DIRECTORY}")
#    set(CTEST_GIT_UPDATE_OPTIONS "--tags origin master")
#    set(CTEST_CHECKOUT_COMMAND "${CTEST_GIT_COMMAND} clone git://git@github.com:Ghettovich/bsf-lib.git ${CTEST_SOURCE_DIRECTORY}")
#endif()
#
#set(CTEST_UPDATE_COMMAND "${CTEST_GIT_COMMAND}")
#
#set(CTEST_CONFIGURE_COMMAND "${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=${CTEST_BUILD_CONFIGURATION}")
#set(CTEST_CONFIGURE_COMMAND "${CTEST_CONFIGURE_COMMAND} -DWITH_TESTING:BOOL=ON ${CTEST_BUILD_OPTIONS}")
#set(CTEST_CONFIGURE_COMMAND "${CTEST_CONFIGURE_COMMAND} \"-G${CTEST_CMAKE_GENERATOR}\"")
#set(CTEST_CONFIGURE_COMMAND "${CTEST_CONFIGURE_COMMAND} \"${CTEST_SOURCE_DIRECTORY}\"")
#
#ctest_start("Experimental")
#ctest_update()
#ctest_configure()
#ctest_build()
#ctest_test()
#if(WITH_COVERAGE AND CTEST_COVERAGE_COMMAND)
#    ctest_coverage()
#endif()
#if(WITH_MEMCHECK AND CTEST_MEMORYCHECK_COMMAND)
#    ctest_memcheck()
#endif()
#ctest_submit()
