// Copyright (c) 2023.  Mark Nelson.  All rights reserved.

///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Track a series of identical runs
///
/// @file   Series.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <list>
#include <string>

#include "BaseRunner.hpp"

/// Track a series of identical runs
class [[maybe_unused]] Series {
private:
   std::string m_description;  ///< The description of this Series
   size_t m_numberOfPreRuns;   ///< The number of runs before starting timed runs
   size_t m_numberOfRuns;      ///< The number of runs requested for this Series
   BaseRunner& m_baseRunner;   ///< The BaseRunner for this Series
   std::list<ticks_t> m_results;  ///< The results (if any) of this Series

public:
   /// Create a new Series
   /// @param newDescription A description of this Series
   /// @param newNumberOfPreRuns The number of runs before starting timed runs
   /// @param newNumberOfRuns The number of runs for this Series
   /// @param newBaseRunner The runner for this Series
   [[maybe_unused]] Series( const std::string_view& newDescription, size_t newNumberOfPreRuns, size_t newNumberOfRuns, BaseRunner& newBaseRunner )
         : m_description( newDescription )
         , m_numberOfPreRuns( newNumberOfPreRuns )
         , m_numberOfRuns( newNumberOfRuns )
         , m_baseRunner( newBaseRunner )
   {};

   /// Create a new Series
   /// @param newDescription A description of this Series
   /// @param newNumberOfRuns The number of runs for this Series
   /// @param newBaseRunner The runner for this Series
   [[maybe_unused]] Series( const std::string_view& newDescription, size_t newNumberOfRuns, BaseRunner& newBaseRunner )
         : Series( newDescription, 0, newNumberOfRuns, newBaseRunner )
   {};

   /// Execute this Series (running m_baseRunner m_numberOfRuns times)
   [[maybe_unused]] void doSeries();

   /// Get the actual number of runs recorded
   /// @return The actual number of runs recorded
   [[maybe_unused]] [[nodiscard]] size_t getActualRuns() const;

   /// Get the total number of ticks for each run
   /// @return The total number of ticks from the CPU's Time Stamp Counter
   [[maybe_unused]] [[nodiscard]] ticks_t getSum() const;

   /// Get the average number of ticks for each run
   /// @return The average number of ticks from the CPU's Time Stamp Counter
   [[maybe_unused]] [[nodiscard]] ticks_t getAverage() const;

   /// Get the first standard deviation of ticks for this Series
   /// @return The first standard deviation of ticks for this Series
   [[maybe_unused]] [[nodiscard]] ticks_t getStandardDeviation() const;

   /// Get the minimum number of ticks for this Series
   /// @return The minimum number of ticks for this Series
   [[maybe_unused]] [[nodiscard]] ticks_t getMin() const;

   /// Get the maximum number of ticks for this Series
   /// @return The maximum number of ticks for this Series
   [[maybe_unused]] [[nodiscard]] ticks_t getMax() const;

   /// Get the formatted results of the Series
   /// @return A string with the formatted (human readable) results
   [[maybe_unused]] [[nodiscard]] std::string getResults() const;

};
