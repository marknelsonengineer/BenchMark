///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// BenchMark copying data with a single-byte `mov` instruction and `loop` instruction
///
/// @file   Test6_mov.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstring>
#include <format>

#include "lib/HexDump.hpp"
#include "lib/LogRunner.hpp"


/// BenchMark copying data with a single-byte `mov` instruction and `loop` instruction
class [[maybe_unused]] Test6_mov : public LogRunner {
public:
   /// Create a Test6_mov as using buffers that are a power of 2
   /// @param newBufferSizeInBits The size of the buffers as a power of 2
   /// @param newGuardSizeInBits The size of the guard as a power of 2
   /// @param newDescription A description of this test
   [[maybe_unused]] Test6_mov (
         const log_2_t newBufferSizeInBits
         , const log_2_t newGuardSizeInBits
         , const std::string_view& newDescription )
         : LogRunner( newBufferSizeInBits, newGuardSizeInBits, newDescription )
   {}

   uint64_t doRun() override {

      // hexdump( m_src, m_buffer_size );
      // hexdump( m_dest, m_buffer_size );

      // char aString[128];

      start_benchmark();

//    snprintf( aString, 128, "%d am %s\n", 1, "Sam" );
      std::string xString = std::format( "{} am {}\n", 1, "Sam" );

/*
      asm( "cld;"                   // Clear the Direction Flag
           "mov rdi, %[m_dest];"    // Load m_dest into RDI
           "mov rsi, %[m_src];"     // Load m_src into RSI
           "mov rcx, %[size];"      // Load m_buffer_size into RCX
           "iterate:"               // Label to loop back to
           "mov al, [rsi];"         // Copy from [RSI] to al
           "inc rsi;"
           "mov [rdi], al;"         // Copy from al to [RDI]
           "inc rdi;"
           "dec rcx;"
           "jnz iterate;"
//           "loop iterate;"
            :  // Output
            :  [m_dest] "r" (m_dest) // Input
            ,  [m_src] "r" (m_src)
            ,  [size] "r" (m_buffer_size)
      :  "al", "rdi", "rsi", "rcx", "cc", "memory" // Clobbered
      );
*/
      end_benchmark();

      // hexdump( m_src, m_buffer_size );
      // hexdump( m_dest, m_buffer_size );

      return getDuration();
   };

};
