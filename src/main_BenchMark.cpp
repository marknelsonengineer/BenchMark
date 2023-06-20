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
#include "Test3_stosq.hpp"
#include "Test4_movsq.hpp"
#include "lib/LogStudy.hpp"
#include "lib/Series.hpp"
#include "lib/Test0_Nothing.hpp"
#include "version.hpp"

using namespace std;


/// The default number of runs for this BenchMark
constinit const size_t NUM_RUNS { 1024 };

/// The min number of bits we will test
constinit const log_2_t MIN_BITS { 3 };

/// The max number of bits we will test
constinit const log_2_t MAX_BITS { 16 };


/// A BenchMark master runner
///
/// @return Zero
/// @NOLINTNEXTLINE( bugprone-exception-escape ): Sometimes main may catch an exception
int main() {
   cout << PROGRAM_TITLE << " version " << FULL_VERSION << endl;

   Test0_Nothing baselineRunner;

   Series baseline_series { Series( "Baseline Test", 4, NUM_RUNS, 0, baselineRunner ) };
   baseline_series.doSeries();

   cout << baseline_series.getResults() << endl;

   {
      LogStudy<Test1_memcpy> memStudy( "memcpy", MIN_BITS, MAX_BITS );
      memStudy.setOverhead( baseline_series.getMin() );
      memStudy.setNumPreRuns( 4 );
      memStudy.setNumRuns( NUM_RUNS );
      memStudy.doStudy();
      memStudy.printResults();
      memStudy.printCSV();
   }

   {
      LogStudy<Test2_memset> memStudy( "memset", MIN_BITS, MAX_BITS );
      memStudy.setOverhead( baseline_series.getMin() );
      memStudy.setNumPreRuns( 4 );
      memStudy.setNumRuns( NUM_RUNS );
      memStudy.doStudy();
      memStudy.printResults();
      memStudy.printCSV();
   }

   {
      LogStudy<Test3_stosq> memStudy( "stosq", MIN_BITS, MAX_BITS );
      memStudy.setOverhead( baseline_series.getMin() );
      memStudy.setNumPreRuns( 4 );
      memStudy.setNumRuns( NUM_RUNS );
      memStudy.doStudy();
      memStudy.printResults();
      memStudy.printCSV();
   }

   {
      LogStudy<Test4_movsq> memStudy( "movsq", MIN_BITS, MAX_BITS );
      memStudy.setOverhead( baseline_series.getMin() );
      memStudy.setNumPreRuns( 4 );
      memStudy.setNumRuns( NUM_RUNS );
      memStudy.doStudy();
      memStudy.printResults();
      memStudy.printCSV();
   }

   return 0;
}
