///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Support a run with a source, destination and a guard buffer
///
/// @file   BufferRunner.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <immintrin.h>

#include "BaseRunner.hpp"

/// Support a run with a source, destination and a guard buffer
class BufferRunner : public BaseRunner {
private:
   std::size_t m_buffer_size;  ///< The size in bytes of the source and destination buffers
   std::size_t m_guard_size;   ///< The size in bytes of the guard buffer

   /// Fill a buffer with random data
   /// @param buffer The buffer to fill
   /// @param size The number of bytes to fill
   static void fillBufferWithRandomData( const void* buffer, std::size_t size );

protected:
   void* m_src { nullptr };    ///< A pointer to the source buffer
   void* m_guard { nullptr };  ///< A pointer to the guard buffer
   void* m_dest { nullptr };   ///< A pointer to the destination buffer

public:
   /// Instantiate a BufferRunner
   /// @param buffer_size The size in bytes of the source and destination buffers
   /// @param guard_size The size in bytes of the guard buffer
   BufferRunner( std::size_t buffer_size, std::size_t guard_size )
         : m_buffer_size( buffer_size )
           , m_guard_size( guard_size )
           , m_src( malloc( m_buffer_size ) )
           , m_guard( malloc( m_guard_size ) )
           , m_dest( malloc( m_buffer_size ) )
   {
      fillBufferWithRandomData( m_src, buffer_size );
      fillBufferWithRandomData( m_dest, buffer_size );
      fillBufferWithRandomData( m_guard, guard_size );
   };

};
