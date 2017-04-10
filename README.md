# C++ Utilities

C++ Utilities for debug, generic filesystem checks and more.

This is a library of small helpful snippets.  

Most code is only tested for use in Linux, and there may be basic support for Windows or OS X, but no testing on those platforms. 

## Features

- Debug
  - Basic printing macros - Info, Debug, Warning, Error, etc
  - CPU Timer class (benchmarking)
  - Clock Cycle Timer class (benchmarking)
- Number
  - Check two floating point numbers are approximately equal.
- String
  - Convert between string and number.
- Hash
  - DJB hash
  - SDBM hash
  - MurmurHash2 hash (https://github.com/aappleby/smhasher)
  - Merging / combining hashes
- Filesystem
  - Check a file path exists.
  - Write a chunk of memory to disk.
  - List the contents of a directory.
  - Print the contents of a directory.
- Operating System (Linux only)
  - Process memory usage.
  - Get total RAM size.

## Usage

_To be written._

## Dependencies

- C++ compiler with support for C++0x or above
