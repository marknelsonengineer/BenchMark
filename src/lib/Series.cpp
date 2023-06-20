// Copyright (c) 2023.  Mark Nelson.  All rights reserved.

///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Track a series of identical runs
///
/// @file   Series.cpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <format>

#include "Series.hpp"

using namespace std;

void Series::doSeries() {
   for( size_t i = 0 ; i < m_numberOfPreRuns ; i++ ) {
      m_baseRunner.reset();
      (void) m_baseRunner.doRun();
   }

   for( size_t i = 0 ; i < m_numberOfRuns ; i++ ) {
      m_baseRunner.reset();
      const ticks_t ticks = m_baseRunner.doRun();
      m_results.push_back( ticks );
   }
}


[[maybe_unused]] [[nodiscard]] size_t Series::getActualRuns() const {
   return m_results.size();
}


[[maybe_unused]] [[nodiscard]] ticks_t Series::getSum() const {
   ticks_t sum { 0 };

   for( auto i : m_results ) {
      sum += i;
   }

   return sum;
}


[[maybe_unused]] [[nodiscard]] ticks_t Series::getAverage() const {
   return getSum() / getActualRuns();
}


[[maybe_unused]] [[nodiscard]] std::string Series::getResults() const {
   return format( "{} runs of {} where n={} averages {} ± {} ticks. Min/Max={}/{}", m_results.size(), m_description, m_n, getAverage(), getStandardDeviation(), getMin(), getMax() );
}


[[maybe_unused]] [[nodiscard]] std::string Series::getCSVheading() {
   return format( "{}:{}:{}:{}:{}:{}:{}", "n", "average", "deviation", "min", "max", "runs", "description" );
}


[[maybe_unused]] [[nodiscard]] std::string Series::getCSV() const {
   return format( "{}:{}:{}:{}:{}:{}:{}", m_n, getAverage(), getStandardDeviation(), getMin(), getMax(), m_results.size(), m_description );
}


[[maybe_unused]] [[nodiscard]] ticks_t Series::getStandardDeviation() const {
   const ticks_t mean = getAverage();

   ticks_t sum_of_variances { 0 };

   for( auto i : m_results ) {
      sum_of_variances += (i - mean) * (i - mean);
   }

   const ticks_t variance = sum_of_variances / getActualRuns();

   return (ticks_t) sqrtl( variance );;
}


[[maybe_unused]] [[nodiscard]] ticks_t Series::getMin() const {
   ticks_t extreme { 0 };
   extreme -= 1;  // This should get us to max value

   for( auto i : m_results ) {
      if( i < extreme ) {
         extreme = i;
      }
   }
   return extreme;
}


[[maybe_unused]] [[nodiscard]] ticks_t Series::getMax() const {
   ticks_t extreme { 0 };

   for( auto i : m_results ) {
      if( i > extreme ) {
         extreme = i;
      }
   }
   return extreme;
}
