///////////////////////////////////////////////////////////////////////////////
//  BenchMark - Quality is free, but only if you are willing to pay for it
//
/// Test Boost global logging services for Empire V
///
/// @file      tests/test_libBenchMark.cpp
/// @author    Mark Nelson <mr_nelson@icloud.com>
/// @copyright (c) 2021 Mark Nelson.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////
/// @cond Suppress Doxygen warnings

#define BOOST_TEST_MODULE BenchMark
#define BOOST_TEST_MAIN  // Include this to get Boost Test's main()

#include <boost/test/unit_test.hpp>

#define LOG_MODULE "test_libBenchMark"  ///< The name of the module for logging purposes @NOLINT( cppcoreguidelines-macro-usage ): `#define` is OK here


BOOST_AUTO_TEST_SUITE( libBenchMark )

BOOST_AUTO_TEST_CASE( Test_general ) {
}

BOOST_AUTO_TEST_SUITE_END()
/// @endcond
