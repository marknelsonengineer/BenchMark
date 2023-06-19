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
class [[maybe_unused]] BufferRunner : public BaseRunner {
protected:
   std::size_t m_buffer_size;  ///< The size in bytes of the source and destination buffers

private:
   std::size_t m_guard_size;   ///< The size in bytes of the guard buffer

   /// Fill a buffer with random data
   /// @param buffer The buffer to fill
   /// @param size The number of bytes to fill
   static void fillBufferWithRandomData( const void* buffer, std::size_t size );

public:
   /// Destructor for BufferRunner
   ~BufferRunner() override {
      if( m_src != nullptr ) {
         free( m_src );
         m_src = nullptr;
      }
      if( m_guard != nullptr ) {
         free( m_guard );
         m_guard = nullptr;
      }

      if( m_dest != nullptr ) {
         free( m_dest );
         m_dest = nullptr;
      }
   }

protected:
   void* m_src { nullptr };    ///< A pointer to the source buffer
   void* m_guard { nullptr };  ///< A pointer to the guard buffer
   void* m_dest { nullptr };   ///< A pointer to the destination buffer

public:
   /// Instantiate a BufferRunner
   /// @param newBufferSize The size in bytes of the source and destination buffers
   /// @param newGuardSize The size in bytes of the guard buffer
   /// @param newDescription A description of this test
   BufferRunner(   const std::size_t newBufferSize
                 , const std::size_t newGuardSize
                 , const std::string_view& newDescription )
         : BaseRunner( newDescription)
         , m_buffer_size( newBufferSize )
         , m_guard_size( newGuardSize )
         , m_src( malloc( m_buffer_size ) )
         , m_guard( malloc( m_guard_size ) )
         , m_dest( malloc( m_buffer_size ) )
   {
      fillBufferWithRandomData( m_src, newBufferSize );
      fillBufferWithRandomData( m_dest, newBufferSize );
      fillBufferWithRandomData( m_guard, newGuardSize );
   };

   /// Reset the runner and prepare for another run
   [[maybe_unused]] void reset() override {
      BaseRunner::reset();
      fillBufferWithRandomData( m_src, m_buffer_size );
      fillBufferWithRandomData( m_dest, m_buffer_size );
      fillBufferWithRandomData( m_guard, m_guard_size );
   }

   /// Get the size of the buffer (in bytes)
   /// @return The size of the biffer (in bytes)
   [[maybe_unused]] [[nodiscard]] size_t getBufferSize() const {
      return m_buffer_size;
   }

};
