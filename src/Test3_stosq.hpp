///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// BenchMark setting data in memory using 64-bit `stosq` instructions
///
/// @file   Test3_stosq.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>

#include <cstring>

#include "lib/HexDump.hpp"
#include "lib/LogRunner.hpp"

/// BenchMark setting data in memory using 64-bit `stosq` instructions
class [[maybe_unused]] Test3_stosq : public LogRunner {
public:
   /// Create a Test3_stosq as using buffers that are a power of 2
   /// @param newBufferSizeInBits The size of the buffers as a power of 2
   /// @param newGuardSizeInBits The size of the guard as a power of 2
   /// @param newDescription A description of this test
   [[maybe_unused]] Test3_stosq(
         const log_2_t newBufferSizeInBits
         , const log_2_t newGuardSizeInBits
         , const std::string_view& newDescription )
         : LogRunner( newBufferSizeInBits, newGuardSizeInBits, newDescription )
   {}

   uint64_t doRun() override {

      // hexdump( m_dest, m_buffer_size );

      start_benchmark();

      asm( ".intel_syntax noprefix;"
           "xor rax, rax;"          // Zero out RAX
           "cld;"                   // Clear the Direction Flag
           "mov rdi, %[m_dest];"    // Load m_dest into RDI
           "mov rcx, %[size];"      // Load m_buffer_size into RCX
           "shr rcx, 3;"            // Divide RCX by 8
           "rep stosq;"             // Store 8 bytes from RAX to [RDI].  RDI += 8.
           ".att_syntax prefix;"
            :  // Output
            :  [m_dest] "r" (m_dest) // Input
            ,  [size] "r" (m_buffer_size)
            :  "rax", "rdi", "rcx", "cc", "memory" // Clobbered
            );

      end_benchmark();

      // hexdump( m_dest, m_buffer_size );

      return getDuration();
   };

};
