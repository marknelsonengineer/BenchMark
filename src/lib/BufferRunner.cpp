///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Lorem ipsum dolor sit amet
///
/// @file   BufferRunner.cpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include "BufferRunner.hpp"


void BufferRunner::fillBufferWithRandomData( const void* buffer, const std::size_t size ) {
   if( size == 0 ) {
      return;
   }

   if( buffer == nullptr ) {
      return;
   }

   // Efficiently fill the buffer with random data
   const unsigned char step_size = sizeof( uint64_t );
   std::size_t remaining_buffer = size;

   while( remaining_buffer >= step_size ) {
      const std::size_t current_position = size - remaining_buffer;
      _rdrand64_step( (unsigned long long*)( (char*)buffer + current_position ) );
      remaining_buffer -= step_size;
   }

   while( remaining_buffer > 0 ) {
      remaining_buffer--;
      long long unsigned int random_int { 0 };
      _rdrand64_step( &random_int );
      *((char*)(buffer) + remaining_buffer) = (char)random_int;
   }

}
