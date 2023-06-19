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

#include <string>
#include <vector>

#include "BaseRunner.hpp"

/// Track a series of identical runs
class [[maybe_unused]] Series {
private:
   std::string m_description;  ///< The description of this Series
   size_t m_numberOfRuns;      ///< The number of runs requested for this Series
   BaseRunner& m_baseRunner;   ///< The BaseRunner for this Series
   std::vector<ticks_t> m_results;  ///< The results (if any) of this Series

public:
   /// Create a new Series
   /// @param newDescription A description of this Series
   /// @param newNumberOfRuns The number of runs for this Series
   /// @param newBaseRunner The runner for this Series
   [[maybe_unused]] Series( const std::string_view& newDescription, size_t newNumberOfRuns, BaseRunner& newBaseRunner )
         : m_description( newDescription )
         , m_numberOfRuns( newNumberOfRuns )
         , m_baseRunner( newBaseRunner )
         {};

   /// Execute this Series (running m_baseRunner m_numberOfRuns times)
   [[maybe_unused]] void doSeries();

   /// Get the average number of ticks for each run
   /// @return The average number of ticks from the CPU's Time Stamp Counter
   [[maybe_unused]] [[nodiscard]] ticks_t getAverage() const;

   /// Get the formatted results of the Series
   /// @return A string with the formatted (human readable) results
   [[maybe_unused]] [[nodiscard]] std::string getResults() const;
};
