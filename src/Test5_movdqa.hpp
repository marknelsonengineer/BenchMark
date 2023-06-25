///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// BenchMark moving data using 128-bit SSE2 instructions
///
/// @file   Test5_movdqa.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstring>

#include "lib/HexDump.hpp"
#include "lib/LogRunner.hpp"

/// BenchMark moving data using 128-bit SSE2 instructions
class [[maybe_unused]] Test5_movdqa : public LogRunner {
public:
   /// Create a Test5_movdqa as using buffers that are a power of 2
   /// @param newBufferSizeInBits The size of the buffers as a power of 2
   /// @param newGuardSizeInBits The size of the guard as a power of 2
   /// @param newDescription A description of this test
   [[maybe_unused]] Test5_movdqa (
         const log_2_t newBufferSizeInBits
         , const log_2_t newGuardSizeInBits
         , const std::string_view& newDescription )
         : LogRunner( newBufferSizeInBits, newGuardSizeInBits, newDescription )
   {}

   uint64_t doRun() override {

      hexdump( m_src, m_buffer_size );
      // hexdump( m_dest, m_buffer_size );

      start_benchmark();

      asm( "cld;"                   // Clear the Direction Flag
           "mov rdi, %[m_dest];"    // Load m_dest into RDI
           "mov rsi, %[m_src];"     // Load m_src into RSI
           "mov rcx, %[size];"      // Load m_buffer_size into RCX
           "shr rcx, 3;"            // Divide RCX by 8
           "loop:"                  // Label to loop back to
           "movdqa xmm8, [rsi];"    // Copy from [RSI] to xmm1 in 128-bit (16-byte) chunks
           "movdqa [rdi], xmm8;"    // Copy from xmm8 to [RDI]
           "add rdi, 8"
            :  // Output
            :  [m_dest] "r" (m_dest) // Input
            ,  [m_src] "r" (m_src)
            ,  [size] "r" (m_buffer_size)
      :  "xmm8", "rdi", "rsi", "rcx", "cc", "memory" // Clobbered
      );

      end_benchmark();

      // hexdump( m_src, m_buffer_size );
      hexdump( m_dest, m_buffer_size );

      return getDuration();
   };

};
