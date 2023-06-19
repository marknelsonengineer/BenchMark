// Copyright (c) 2023.  Mark Nelson.  All rights reserved.

///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Lorem ipsum dolor sit amet
///
/// @file   Test1_memcpy.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstring>

#include "lib/LogRunner.hpp"

class [[maybe_unused]] Test1_memcpy : public LogRunner {
   uint64_t doRun() override {

      start_benchmark();

      std::memcpy( m_dest, m_src, m_buffer_size );

      end_benchmark();

      return getDuration();
   };

};
