// Copyright (c) 2023.  Mark Nelson.  All rights reserved.

///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// BenchMark memset
///
/// @file   Test2_memset.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstring>

#include "lib/LogRunner.hpp"

/// BenchMark memset
class [[maybe_unused]] Test2_memset : public LogRunner {
public:
   /// Create a Test2_memset as using buffers that are a power of 2
   /// @param newBufferSizeInBits The size of the buffers as a power of 2
   /// @param newGuardSizeInBits The size of the guard as a power of 2
   /// @param newDescription A description of this test
   [[maybe_unused]] Test2_memset (
         const log_2_t newBufferSizeInBits
         , const log_2_t newGuardSizeInBits
         , const std::string_view& newDescription )
         : LogRunner( newBufferSizeInBits, newGuardSizeInBits, newDescription )
   {}

   uint64_t doRun() override {

      start_benchmark();

      std::memset( m_dest, 0, m_buffer_size );

      end_benchmark();

      return getDuration();
   };

};
