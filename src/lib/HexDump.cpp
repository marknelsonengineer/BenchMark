///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Hex dump utility
///
/// @see https://stackoverflow.com/questions/29242/off-the-shelf-c-hex-dump-code
///
/// @file   HexDump.cpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <cstdio>

#include "HexDump.hpp"

/// The width of a standard hexdump
constinit const unsigned char BYTES_WIDE { 16 };

[[maybe_unused]] void hexdump(void *ptr, int buflen) {
   auto* buf = (unsigned char*) ptr;

   /// @NOLINTBEGIN ( hicpp-vararg, cppcoreguidelines-pro-type-vararg ): Support varargs in printf

   for( int i = 0 ; i < buflen ; i += BYTES_WIDE ) {
      printf( "%06x: ", i );
      for( int j = 0 ; j < BYTES_WIDE ; j++ ) {
         if( i + j < buflen ) {
            printf( "%02x ", buf[ i + j ] );
         } else {
            printf( "   " );
         }
      }
      printf( " " );
      for( int j = 0 ; j < BYTES_WIDE ; j++ ) {
         if( i + j < buflen ) {
            printf( "%c", isprint( buf[ i + j ] ) != 0 ? buf[ i + j ] : '.' );
         }
      }
      printf( "\n" );
   }
   // NOLINTEND ( hicpp-vararg, cppcoreguidelines-pro-type-vararg )
}
