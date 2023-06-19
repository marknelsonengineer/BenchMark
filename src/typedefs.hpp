///////////////////////////////////////////////////////////////////////////////
//  BenchMark - Quality is free, but only if you are willing to pay for it
//
/// Consolidate all datatype definitions in one place.  In C, header files
/// *should* form Directional Acyclic Graphs (DAGs) but the preprocessor will
/// allow programmers to create cycles.  Good library definitions usually
/// stratify into 3 layers:
///   - Type alias declarations (`typedef` and `using`) (this file)
///   - Traditional type declarations (`class`, `struct`, etc.), forward declarations of
///     functions and variables
///   - Implementations
///
/// @file      typedefs.hpp
/// @author    Mark Nelson <marknels@hawaii.edu>
/// @copyright (c) 2023 Mark Nelson.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdint>     // For uint8_t uint_16_t uint32_t, etc.

/// The type definition for constant semantic version numbers
using const_version_number_t = const uint8_t;

/// The type definition for constant semantic build numbers
using const_build_number_t = const uint32_t;

/// A datetype that represents a number of bits.
using log_2_t = unsigned char;
