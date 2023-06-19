///////////////////////////////////////////////////////////////////////////////
//  BenchMark - Quality is free, but only if you are willing to pay for it
//
/// A benchmarking runner
///
/// @file      main_BenchMark.cpp
/// @author    Mark Nelson <marknels@hawaii.edu>
/// @copyright (c) 2023 Mark Nelson.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <immintrin.h>

#include <cmath>
#include <cstring>

#include "version.hpp"

#include "lib/BaseRunner.hpp"
#include "lib/BufferRunner.hpp"
#include "lib/LogRunner.hpp"

using namespace std;

/// The number of bits in the buffer we are testing.
constinit const log_2_t MAX_BUF_SIZE_LOG_2 { 10 };

/// The maximum size of the buffer we are testing.  Should be a power of 2
constinit const size_t MAX_BUF_SIZE { 1U << MAX_BUF_SIZE_LOG_2 };





char src[MAX_BUF_SIZE];
char guard[MAX_BUF_SIZE * 10];
char dest[MAX_BUF_SIZE];

void fillBuffers() {
   for( size_t i = 0 ; i < sizeof( src ) ; i += 8 ) {
      _rdrand64_step( (long long unsigned int*)(&src[ i ]) );
   }

   for( size_t i = 0 ; i < sizeof( dest ) ; i += 8 ) {
      _rdrand64_step( (long long unsigned int*)(&dest[ i ]) );
   }

   for( size_t i = 0 ; i < sizeof( guard ) ; i += 8 ) {
      _rdrand64_step( (long long unsigned int*)(&guard[ i ]) );
   }

}


/// This test develops a baseline that represents the overhead of conducting the tests.
class Test0_Nothing : public BaseRunner {
public:
   uint64_t doRun() override {
      m_start_time = __rdtsc();

      m_end_time = __rdtsc();

      return getDuration();
   }
};


uint64_t test0_nothing() {
   fillBuffers();

   uint64_t start_time { __rdtsc() };

   uint64_t end_time { __rdtsc() };

   return end_time - start_time;
}

uint64_t test1_memcpy( size_t size ) {
   fillBuffers();

   uint64_t start_time { __rdtsc() };

   std::memcpy( dest, src, size );

   uint64_t end_time { __rdtsc() };

   return end_time - start_time;
}


uint64_t test2_memset( size_t size ) {
   fillBuffers();

   uint64_t start_time { __rdtsc() };

   std::memset( dest, 0, size );

   uint64_t end_time { __rdtsc() };

   return end_time - start_time;
}


uint64_t test3_xxxx( size_t size ) {
   fillBuffers();

   uint64_t start_time { __rdtsc() };

   asm( ".intel_syntax noprefix;"
        "xor rax, rax;"
        "mov rdi, 0;"
        ".att_syntax prefix;"
      :  // Output
      :  "r"(dest) // Input
      :  "rax" // Clobbered
   );

   uint64_t end_time { __rdtsc() };

   return end_time - start_time;
}


/// A sample Hello World program
///
/// @return Zero
int main() {
   uint64_t result_times[128][4][11];

   for( size_t j = 3 ; j <= 10 ; j++ ) {
      size_t size = 1 << j ;
      cout << j << " " << size << endl;

      for( size_t i = 0 ; i < 128 ; i++ ) {
         result_times[ i ][ 0 ][0] = test0_nothing();
         result_times[ i ][ 1 ][j] = test1_memcpy( size );
         result_times[ i ][ 2 ][j] = test2_memset( size );
         result_times[ i ][ 3 ][j] = test3_xxxx( size );
      }
   }


//   cout << "Nothing" << endl;
//   for( size_t i = 0 ; i < 128 ; i++ ) {
//      cout << result_times[ i ][ 0 ][0];
//      cout << endl;
//   }

   cout << "test1_memcpy" << endl;
   for( size_t j = 3 ; j <=10 ; j++ ) {
      double sum { 0 };
      uint64_t minVal { UINT64_MAX };
      uint64_t maxVal { 0 };
      for( size_t i = 0 ; i < 128 ; i++ ) {
         sum += result_times[ i ][ 1 ][ j ];
         minVal = min( minVal, result_times[ i ][ 1 ][ j ] );
         maxVal = max( maxVal, result_times[ i ][ 1 ][ j ] );
      }
      double mean { sum / 128.0 };
      double stdev { 0 };

      for( size_t i = 0 ; i < 128 ; i++ ) {
         stdev += pow( result_times[ i ][ 1 ][ j ] - mean, 2 );
      }
      stdev = sqrt( stdev / 128.0 );

      cout << "memcpy-" << ( 1 << j ) << ":" ;
      cout << mean << ":" ;
      cout << stdev << ":" ;
      cout << minVal << ":" ;
      cout << maxVal << ":" ;
      cout << endl;
   }


   cout << "test3_xxxx" << endl;
   for( size_t j = 3 ; j <=10 ; j++ ) {
      double sum { 0 };
      uint64_t minVal { UINT64_MAX };
      uint64_t maxVal { 0 };
      for( size_t i = 0 ; i < 128 ; i++ ) {
         sum += result_times[ i ][ 3 ][ j ];
         minVal = min( minVal, result_times[ i ][ 3 ][ j ] );
         maxVal = max( maxVal, result_times[ i ][ 3 ][ j ] );
      }
      double mean { sum / 128.0 };
      double stdev { 0 };

      for( size_t i = 0 ; i < 128 ; i++ ) {
         stdev += pow( result_times[ i ][ 3 ][ j ] - mean, 2 );
      }
      stdev = sqrt( stdev / 128.0 );

      cout << "test3-" << ( 1 << j ) << ":" ;
      cout << mean << ":" ;
      cout << stdev << ":" ;
      cout << minVal << ":" ;
      cout << maxVal << ":" ;
      cout << endl;
   }


//   for( size_t i = 0 ; i < 128 ; i++ ) {
//      cout << "test1_memcpy( " << size << " ) = " << result_times[i][1] << "  ";
//   }

//      cout << "test2_memset( " << size << " ) = " << result_times[i][2] << "  ";
//   }

   std::cout << PROGRAM_TITLE << " version " << FULL_VERSION << std::endl;
   return 0;
}
