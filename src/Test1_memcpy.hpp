///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// BenchMark memcpy
///
/// @file   Test1_memcpy.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstring>

#include "lib/LogRunner.hpp"

/// BenchMark memcpy
class [[maybe_unused]] Test1_memcpy : public LogRunner {
public:
   /// Create a Test1_memcpy as using buffers that are a power of 2
   /// @param buffer_size_log_2 The size of the buffers as a power of 2
   /// @param guard_size_log_2 The size of the guard as a power of 2
   /// @param newDescription A description of this test
   [[maybe_unused]] Test1_memcpy (
           const log_2_t buffer_size_log_2
         , const log_2_t guard_size_log_2
         , const std::string_view& newDescription )
         : LogRunner( buffer_size_log_2, guard_size_log_2, newDescription )
   {}

   uint64_t doRun() override {

      start_benchmark();

      std::memcpy( m_dest, m_src, m_buffer_size );

      end_benchmark();

      return getDuration();
   };

};
