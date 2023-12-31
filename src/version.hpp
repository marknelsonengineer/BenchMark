///////////////////////////////////////////////////////////////////////////////
//  BenchMark - Quality is free, but only if you are willing to pay for it
//
/// Program version and build tracker
///
/// Use Semantic Versioning 2.0.0:  https://semver.org/
///
/// #VERSION_BUILD is modified by update_version.py
///
/// @file      version.hpp
/// @author    Mark Nelson <marknels@hawaii.edu>
/// @copyright (c) 2021 Mark Nelson.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include "typedefs.hpp"  // For const_version_number_t

/// A grammatically correct title for the application
[[maybe_unused]] extern const std::string_view PROGRAM_TITLE;

/// Increments with __major__ functional changes
[[maybe_unused]] extern const_version_number_t VERSION_MAJOR;

/// Increments with minor functional changes
[[maybe_unused]] extern const_version_number_t VERSION_MINOR;

/// Increments with bugfixes
[[maybe_unused]] extern const_version_number_t VERSION_PATCH;

/// Monotonic constructCounter, set by update_version.py, to track the number of
/// compilations.
[[maybe_unused]] extern const_build_number_t VERSION_BUILD;

/// The full version number as a string
[[maybe_unused]] extern const std::string FULL_VERSION;

/// A bit for the lawyers
[[maybe_unused]] extern const std::string LEGAL_NOTICE;
