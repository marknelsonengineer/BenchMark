// Copyright (c) 2023.  Mark Nelson.  All rights reserved.

///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Lorem ipsum dolor sit amet
///
/// @file   LogRunner.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../typedefs.hpp"

#include "BufferRunner.hpp"

/// Supports a run where the dataset is a power of 2
class LogRunner : public BufferRunner {
private:
   log_2_t m_buffer_size_Log_2 { 0 };  ///< The size of the buffers as a power of 2
   log_2_t m_guard_size_Log_2 { 0 };   ///< The size of the guard as a power of 2

public:
   /// Create a BufferRunner as using buffers that are a power of 2
   /// @param buffer_size_log_2 The size of the buffers as a power of 2
   /// @param guard_size_log_2 The size of the guard as a power of 2
   LogRunner( log_2_t buffer_size_log_2, log_2_t guard_size_log_2 )
         : BufferRunner( 1U << buffer_size_log_2, 1U << guard_size_log_2 )
           , m_buffer_size_Log_2( buffer_size_log_2 )
           , m_guard_size_Log_2( guard_size_log_2 )
   {

   }

   /// Get the buffer size as a power of 2
   /// @return The number of bits in the buffer size
   [[nodiscard]] log_2_t getMBufferSizeLog2() const {
      return m_buffer_size_Log_2;
   }

   /// Get the guard size as a power of 2
   /// @return The number of bits in the guard size
   [[nodiscard]] log_2_t getMGuardSizeLog2() const {
      return m_guard_size_Log_2;
   }
};
