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

#include "lib/Series.hpp"
#include "lib/Test0_Nothing.hpp"
#include "version.hpp"

using namespace std;

/// A BenchMark master runner
///
/// @return Zero
int main() {
   cout << PROGRAM_TITLE << " version " << FULL_VERSION << endl;

   Test0_Nothing baselineRunner;

   Series baseline_series { Series( "Baseline Test", 4, 64, baselineRunner ) };
   baseline_series.doSeries();

   cout << baseline_series.getResults();

   return 0;
}
