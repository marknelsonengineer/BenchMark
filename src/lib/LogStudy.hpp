///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Study several LogRunner Series
///
/// @file   LogStudy.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../typedefs.hpp"

#include <format>
#include <iostream>
#include <list>
#include <string_view>
#include <type_traits>

#include "LogRunner.hpp"
#include "Series.hpp"

/// Requre that newLogRunner in LogStudy be derived from LogRunner
template <typename T>
concept LogRunnerConcept = std::is_base_of<LogRunner, T>::value;

/// Study several LogRunner Series
template<LogRunnerConcept logRunnerClass>
class [[maybe_unused]] LogStudy {
protected:
   std::string m_description;  ///< A description of this study
   log_2_t min_bits { 0 };     ///< The size of the buffers as a power of 2
   log_2_t max_bits { 0 };     ///< The size of the guard as a power of 2
   ticks_t m_overhead { 0 };   ///< An optional overhead time that can be deducted from the results
   size_t m_numPreRuns { 0 };  ///< The number of runs before starting timed runs
   size_t m_numRuns { 0 };     ///< The number of runs requested for this Series

   std::list<Series> theStudy;  ///< Hold each Series of the Study

public:
   /// Create a LogStudy object
   ///
   /// @param newDescription A description of the LogStudy
   /// @param new_min_bits The starting size of n (in bits)
   /// @param new_max_bits The ending size of n (in bits)
   [[maybe_unused]] LogStudy( const std::string_view& newDescription
                              , log_2_t new_min_bits
                              , log_2_t new_max_bits
                            )
         : m_description( newDescription )
           , min_bits( new_min_bits )
           , max_bits( new_max_bits )
   {};


   /// Get the overhead allocated for this Study
   /// @return The overhead allocated for this Study
   [[maybe_unused]] [[nodiscard]] ticks_t getOverhead() const {
      return m_overhead;
   }


   /// Set the overhead for this Study
   /// @param newOverhead The overhead to allocate for this Study
   [[maybe_unused]] void setOverhead( ticks_t newOverhead ) {
      m_overhead = newOverhead;
   }


   /// Get the number of runs before starting timed runs
   /// @return The number of runs before starting timed runs
   [[maybe_unused]] [[nodiscard]] size_t getNumPreRuns() const {
      return m_numPreRuns;
   }


   /// Set the number of runs before starting timed runs
   /// @param newNumPreRuns The number of runs before starting timed runs
   [[maybe_unused]] void setNumPreRuns( size_t newNumPreRuns ) {
      m_numPreRuns = newNumPreRuns;
   }


   /// Get the number of runs requested for this Series
   /// @return The number of runs requested for this Series
   [[maybe_unused]] [[nodiscard]] size_t getNumRuns() const {
      return m_numRuns;
   }


   /// Set the number of runs requested for this Series
   /// @param newNumRuns The number of runs requested for this Series
   [[maybe_unused]] void setNumRuns( size_t newNumRuns ) {
      m_numRuns = newNumRuns;
   }


   /// Do the study
   [[maybe_unused]] void doStudy() {
      for( log_2_t i = min_bits ; i <= max_bits ; i++ ) {
         const std::string description { std::format( "{} where n={}", m_description, 1U << i ) };
         logRunnerClass logRunner( i, i, description );
         logRunner.setOverhead( m_overhead );

         Series aSeries( description, m_numPreRuns, m_numRuns, logRunner );
         aSeries.doSeries();

         theStudy.push_back( aSeries );
      }
   }


   /// Print results
   [[maybe_unused]] void printResults() {
      for( const auto& series : theStudy ) {
         std::cout << series.getResults();
         std::cout << std::endl;
      }
   }

};
