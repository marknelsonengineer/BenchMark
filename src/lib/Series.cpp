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

#include <format>

#include "Series.hpp"

using namespace std;

void Series::doSeries() {
   for( size_t i = 0 ; i < m_numberOfRuns ; i++ ) {
      const ticks_t ticks = m_baseRunner.doRun();
      m_results.push_back( ticks );
   }
}


[[maybe_unused]] [[nodiscard]] ticks_t Series::getAverage() const {
   ticks_t sum { 0 };

   for( auto i : m_results ) {
      sum += i;
   }

   return sum / m_results.size();
}


std::string Series::getResults() const {
   return format( "{} runs of {} averages {} ticks", m_results.size(), m_description, getAverage() );

   //return std::format( "{} runs of {} averages {} +/- {} ticks", m_results.size(), m_description, getAverage(), 0.0 );
   // return std::string();
}
