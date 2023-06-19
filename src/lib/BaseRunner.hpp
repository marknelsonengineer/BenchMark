///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Base class for methods under test
///
/// @file   BaseRunner.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../typedefs.hpp"


/// Base class for methods under test
class BaseRunner {
private:
   uint64_t m_overhead { 0 };    ///< An optional overhead time that can be deducted from the results

protected:
   uint64_t m_start_time { 0 };  ///< The start time of the test
   uint64_t m_end_time { 0 };    ///< The end time of the test

   /// Set the overhead of the benchmark (to be subtracted when users call getDuration())
   /// @param overhead The number of ticks to subtract from getDuration()
   void setOverhead( uint64_t overhead ) { m_overhead = overhead; }

   /// Get the current overhead of the benchmark
   /// @return The number of ticks set as overhead
   [[nodiscard]] uint64_t getOverhead() const { return m_overhead; }

   /// Get the duration of the run
   /// @return The number of ticks (minus the overhead)
   [[nodiscard]] uint64_t getDuration() const { return m_end_time - m_start_time - m_overhead; }

public:
   /// The default destructor
   virtual ~BaseRunner() = default;

   /// Implement this to actually do the test
   /// @return The number of ticks that the run consumed
   virtual uint64_t doRun() = 0;
};
