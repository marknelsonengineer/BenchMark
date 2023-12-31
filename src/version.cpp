///////////////////////////////////////////////////////////////////////////////
//  BenchMark - Quality is free, but only if you are willing to pay for it
//
/// Program version and build tracker
///
/// Use Semantic Versioning 2.0.0:  https://semver.org/
///
/// #VERSION_BUILD is modified by update_version.py
///
/// @file      version.cpp
/// @author    Mark Nelson <marknels@hawaii.edu>
/// @copyright (c) 2021 Mark Nelson.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include "version.hpp"  // Just cuz

[[maybe_unused]] alignas( const std::string_view ) constinit const std::string_view PROGRAM_TITLE { "BenchMark" };

[[maybe_unused]] alignas( int ) const_version_number_t VERSION_MAJOR { 2 };
[[maybe_unused]] alignas( int ) const_version_number_t VERSION_MINOR { 0 };
[[maybe_unused]] alignas( int ) const_version_number_t VERSION_PATCH { 0 };
[[maybe_unused]] alignas( int ) const_build_number_t VERSION_BUILD { 206 };

[[maybe_unused]] alignas( const std::string ) constinit const std::string FULL_VERSION { "2.0.0+206" };

[[maybe_unused]] alignas( const std::string ) const std::string LEGAL_NOTICE {
   "Copyright (c) 2023 Mark Nelson.  All rights reserved.\n"
   "See the source for a detailed license.\n"
   "There is no warranty for this program.\n"
};
