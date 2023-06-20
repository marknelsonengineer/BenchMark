###############################################################################
### BenchMark - Quality is free, but only if you are willing to pay for it
###
### Use `cmake` to build targets from the project's source files
###
### @see https://cmake.org/cmake/help/latest/manual/cmake-language.7.html
###
### @file      CMakeLists.txt
### @author    Mark Nelson <marknels@hawaii.edu>
### @copyright (c) 2021 Mark Nelson.  All rights reserved.
###############################################################################

CMAKE_MINIMUM_REQUIRED( VERSION 3.26 )

PROJECT( "BenchMark"
         VERSION "2.0.0"
         DESCRIPTION "Quality is free, but only if you are willing to pay for it"
         LANGUAGES CXX )

# MESSAGE( STATUS "CMAKE_SOURCE_DIR = [${CMAKE_SOURCE_DIR}]" )
# MESSAGE( STATUS "CMAKE_BUILD_TYPE = [${CMAKE_BUILD_TYPE}]" )
# MESSAGE( STATUS "CMAKE_CXX_COMPILER = [${CMAKE_CXX_COMPILER}]" )
# MESSAGE( STATUS "CMAKE_CXX_COMPILER_ID = [${CMAKE_CXX_COMPILER_ID}]" )
# MESSAGE( STATUS "CMAKE_PROJECT_VERSION = [${CMAKE_PROJECT_VERSION}]" )

SET( CMAKE_CXX_STANDARD 20 )
SET( CMAKE_CXX_STANDARD_REQUIRED TRUE )

SET( BUILDABLE True )  # Set to true by default, but it may get disabled

IF( ${CMAKE_BUILD_TYPE} STREQUAL "Doxygen" )
   SET( BUILDABLE False )
ELSEIF( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )
ELSEIF( ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel" )
ELSEIF( ${CMAKE_BUILD_TYPE} STREQUAL "Clang" )
ELSEIF( ${CMAKE_BUILD_TYPE} STREQUAL "Lint" )
   MESSAGE( STATUS "Lint with clang-tidy" )
   SET( CMAKE_CXX_CLANG_TIDY clang-tidy --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy )
   # set( CMAKE_CXX_CPPCHECK cppcheck --quiet --enable=all -I ${Boost_INCLUDE_DIRS} -i ./tests/ )
ELSE()
   MESSAGE( STATUS "Unknown build type" )
   RETURN()
ENDIF()


############################## Boost Library Configuration #####################
# see https://cmake.org/cmake/help/latest/module/FindBoost.html
SET( Boost_USE_RELEASE_LIBS ON )  # Boost is production-for-us (we're not developing Boost code), so we'd always use their released libraries
SET( Boost_USE_DEBUG_LIBS OFF )  # Boost is production-for-us (we're not developing Boost code), so we'd never use debug libraries
SET( Boost_USE_STATIC_LIBS OFF )  # By default, use shared libraries, but on Release builds, use static libs

IF( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )  # We build our own Boost libraries to get these static libraries
   SET( Boost_USE_STATIC_LIBS ON )  # By default, use shared libraries, but on Release builds, use static libs
ENDIF()

FIND_PACKAGE( Boost REQUIRED COMPONENTS unit_test_framework serialization )  # Needed for libraries (not Boost header-only components).

INCLUDE_DIRECTORIES( BEFORE SYSTEM ${Boost_INCLUDE_DIRS} )
MESSAGE( STATUS "Boost_INCLUDE_DIRS = [${Boost_INCLUDE_DIRS}]" )


################################ Compiler Configuration #######################

ADD_COMPILE_OPTIONS( -Wall -Wextra )

IF( ${CMAKE_COMPILER_IS_GNUCXX} )
   MESSAGE( STATUS "Compile with g++" )
   ADD_COMPILE_OPTIONS( -lstdc++ -fuse-ld=gold -masm=intel )
ELSEIF( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
   MESSAGE( STATUS "Compile with clang++" )
   ADD_COMPILE_OPTIONS( -march=native -masm=intel )
ENDIF()

SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native -Ofast -funroll-loops -static -mfma" )
SET( CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_DEBUG} -march=native -mtune=native -Oz -mfma" )

IF( ${CMAKE_BUILD_TYPE} STREQUAL "Doxygen" )
   CONFIGURE_FILE( .doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile )

   ADD_CUSTOM_TARGET( doxygen_local_build
                      COMMENT "Generating documentation"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      COMMAND .doxygen/stats.py
                      COMMAND rsync --recursive --checksum --delete --mkpath --chmod=o+r,Do+x ${CMAKE_SOURCE_DIR}/images ${CMAKE_SOURCE_DIR}/.doxygen/generated_docs/html/
                      COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      )

   SET_TARGET_PROPERTIES( doxygen_local_build
                       PROPERTIES
                       ADDITIONAL_CLEAN_FILES "${CMAKE_SOURCE_DIR}/.doxygen/generated_docs"
                       )

   ADD_CUSTOM_TARGET( doxygen_publish
                      COMMENT "Pushing files to UHUnix"
                      COMMAND rsync --recursive --checksum --delete --compress --stats --chmod=o+r,Do+x ${CMAKE_SOURCE_DIR}/.doxygen/generated_docs/html/ marknels@uhunix.hawaii.edu:~/public_html/${CMAKE_PROJECT_NAME}
                      )

ENDIF()


IF( ${BUILDABLE} )
   IF( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )  # We build our own Boost libraries to get these static libraries
      SET( BUILD_SHARED_LIBS FALSE )
   ELSE()
      SET( BUILD_SHARED_LIBS TRUE )
      ADD_COMPILE_DEFINITIONS( BOOST_TEST_DYN_LINK )
   ENDIF()

   ADD_LIBRARY( libBenchMark src/lib/BaseRunner.hpp src/lib/BufferRunner.cpp src/lib/BufferRunner.hpp src/lib/LogRunner.hpp src/lib/Test0_Nothing.hpp src/lib/Series.cpp src/lib/Series.hpp src/lib/LogStudy.hpp src/lib/HexDump.cpp src/lib/HexDump.hpp )

   ADD_EXECUTABLE( BenchMark src/main_BenchMark.cpp src/version.hpp src/typedefs.hpp src/version.cpp src/Test1_memcpy.hpp src/Test2_memset.hpp src/Test3_stosq.hpp )
   TARGET_LINK_LIBRARIES( BenchMark ${Boost_LIBRARIES} )
   TARGET_LINK_LIBRARIES( BenchMark libBenchMark )

   ADD_CUSTOM_TARGET( update_version
                      COMMENT "Update version"
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      COMMAND .doxygen/update_version.py )
   ADD_DEPENDENCIES( BenchMark update_version )

   ADD_EXECUTABLE( All_Boost_Tests tests/test_libBenchMark.cpp tests/test_version.cpp src/typedefs.hpp src/version.hpp src/version.cpp )
   TARGET_LINK_LIBRARIES( All_Boost_Tests ${Boost_LIBRARIES} )
   TARGET_LINK_LIBRARIES( All_Boost_Tests libBenchMark )
   ADD_DEPENDENCIES( All_Boost_Tests update_version )
ENDIF()
