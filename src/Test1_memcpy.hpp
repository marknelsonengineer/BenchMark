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
   uint64_t doRun() override {

      start_benchmark();

      std::memcpy( m_dest, m_src, m_buffer_size );

      end_benchmark();

      return getDuration();
   };

};
