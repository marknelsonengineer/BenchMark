///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Supports a run where the dataset is a power of 2
///
/// @file   LogRunner.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../typedefs.hpp"

#include "BufferRunner.hpp"

/// Supports a run where the dataset is a power of 2
class [[maybe_unused]] LogRunner : public BufferRunner {
private:
   log_2_t m_buffer_size_log_2 { 0 };  ///< The size of the buffers as a power of 2
   log_2_t m_guard_size_log_2 { 0 };   ///< The size of the guard as a power of 2

public:
   /// Create a BufferRunner as using buffers that are a power of 2
   /// @param buffer_size_log_2 The size of the buffers as a power of 2
   /// @param guard_size_log_2 The size of the guard as a power of 2
   /// @param newDescription A description of this test
   [[maybe_unused]] LogRunner (
           const log_2_t buffer_size_log_2
         , const log_2_t guard_size_log_2
         , const std::string_view& newDescription )
         : BufferRunner( 1U << buffer_size_log_2, 1U << guard_size_log_2, newDescription )
         , m_buffer_size_log_2( buffer_size_log_2 )
         , m_guard_size_log_2( guard_size_log_2 )
   {}

   /// Get the buffer size as a power of 2
   /// @return The number of bits in the buffer size
   [[maybe_unused]] [[nodiscard]] log_2_t getBufferSizeLog2() const {
      return m_buffer_size_log_2;
   }

   /// Get the guard size as a power of 2
   /// @return The number of bits in the guard size
   [[maybe_unused]] [[nodiscard]] log_2_t getGuardSizeLog2() const {
      return m_guard_size_log_2;
   }
};
