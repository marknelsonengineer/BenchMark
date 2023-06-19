///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// An empty BaseRunner.  It's good for benchmarking the overhead of the test
/// framework
///
/// @file   Test0_Nothing.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "BaseRunner.hpp"

/// An empty BaseRunner.  It's good for benchmarking the overhead of the test framework
class [[maybe_unused]] Test0_Nothing : public BaseRunner {
   uint64_t doRun() override {

      start_benchmark();

      end_benchmark();

      return getDuration();
   };
};
