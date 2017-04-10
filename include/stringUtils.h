/*
 * Generic string helper functions
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cstdio>   // FILE, fwrite, fopen
#include <sstream>  // stringstream
#include <cmath>    // fabs

namespace string
{

  // Convert a number to a string
  template<typename NUM_TYPE>
  inline
  std::string numberToString(NUM_TYPE num)
  {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }

  // Convert a string to a number.
  template<typename NUM_TYPE>
  inline
  NUM_TYPE stringToNumber(const std::string &text)
  {
    std::stringstream ss(text);
    NUM_TYPE result;
    return ss >> (result ? result : 0);
  }

}

#endif // STRING_UTILS_H
