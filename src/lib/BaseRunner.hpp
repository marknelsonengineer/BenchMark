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

#include <immintrin.h>
#include <string>

#include "../typedefs.hpp"


/// Base class for methods under test
class BaseRunner {
private:
   uint64_t m_overhead { 0 };    ///< An optional overhead time that can be deducted from the results

protected:
   std::string m_description;    ///< A description of this runner
   uint64_t m_start_time { 0 };  ///< The start time of the test
   uint64_t m_end_time { 0 };    ///< The end time of the test

   /// Set the overhead of the benchmark (to be subtracted when users call getDuration())
   /// @param newOverhead The number of ticks to subtract from getDuration()
   [[maybe_unused]] void setOverhead( uint64_t newOverhead ) { m_overhead = newOverhead; }

   /// Get the current overhead of the benchmark
   /// @return The number of ticks set as overhead
   [[maybe_unused]] [[nodiscard]] uint64_t getOverhead() const { return m_overhead; }

   /// Get the duration of the run
   /// @return The number of ticks (minus the overhead)
   [[nodiscard]] uint64_t getDuration() const { return m_end_time - m_start_time - m_overhead; }

   /// Start the benchmark
   inline void start_benchmark() { m_start_time = __rdtsc(); }

   /// End the benchmark
   inline void end_benchmark() { m_end_time = __rdtsc(); }

public:
   /// Create a basic BaseRunner
   BaseRunner() = default;

   /// Create a BaseRunner with a description
   /// @param newDescription The description for this BaseRunner
   explicit BaseRunner( const std::string_view& newDescription ) : m_description( newDescription ) {};

   /// The default destructor
   virtual ~BaseRunner() = default;


   /// Get the description
   /// @return The description for this BaseRunner
   [[maybe_unused]] [[nodiscard]] const std::string& getDescription() const {
      return m_description;
   }


   /// Set the description
   /// @param newDescription A description for this BaseRunner
   [[maybe_unused]] void setDescription( const std::string& newDescription ) {
      m_description = newDescription;
   }


   /// Implement this to actually do the test
   /// @return The number of ticks that the run consumed
   [[nodiscard]] virtual uint64_t doRun() = 0;
};
