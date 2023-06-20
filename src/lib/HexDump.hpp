///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         BenchMark - EE 205 - Spr 2023
//
/// Dump a block of hex to the console
///
/// @see https://stackoverflow.com/questions/29242/off-the-shelf-c-hex-dump-code
///
/// @file   HexDump.hpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

/// Dump a block of hex to the console
/// @param ptr    The starting address to dump
/// @param buflen The lenght of data to dump
[[maybe_unused]] extern void hexdump(void *ptr, int buflen);
