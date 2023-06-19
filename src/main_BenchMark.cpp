///////////////////////////////////////////////////////////////////////////////
//  BenchMark - Quality is free, but only if you are willing to pay for it
//
/// A benchmarking runner
///
/// @file      main_BenchMark.cpp
/// @author    Mark Nelson <marknels@hawaii.edu>
/// @copyright (c) 2023 Mark Nelson.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Test1_memcpy.hpp"
#include "Test2_memset.hpp"
#include "lib/LogStudy.hpp"
#include "lib/Series.hpp"
#include "lib/Test0_Nothing.hpp"
#include "version.hpp"

using namespace std;


/// The default number of runs for this BenchMark
constinit const size_t NUM_RUNS { 64 };

/// The min number of bits we will test
constinit const log_2_t MIN_BITS { 3 };

/// The max number of bits we will test
constinit const log_2_t MAX_BITS { 16 };


/// A BenchMark master runner
///
/// @return Zero
int main() {
   cout << PROGRAM_TITLE << " version " << FULL_VERSION << endl;

   Test0_Nothing baselineRunner;

   Series baseline_series { Series( "Baseline Test", 4, NUM_RUNS, baselineRunner ) };
   baseline_series.doSeries();

   cout << baseline_series.getResults() << endl;

   LogStudy<Test1_memcpy> memcpyStudy( "memcpy", MIN_BITS, MAX_BITS );
   memcpyStudy.setOverhead( baseline_series.getMin() );
   memcpyStudy.setNumPreRuns( 4 );
   memcpyStudy.setNumRuns( NUM_RUNS );
   memcpyStudy.doStudy();
   memcpyStudy.printResults();

   LogStudy<Test2_memset> memsetStudy( "memset", MIN_BITS, MAX_BITS );
   memsetStudy.setOverhead( baseline_series.getMin() );
   memsetStudy.setNumPreRuns( 4 );
   memsetStudy.setNumRuns( NUM_RUNS );
   memsetStudy.doStudy();
   memsetStudy.printResults();

   return 0;
}
