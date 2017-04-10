/*
 * Utilities and definitions related to numbers.
 */

#ifndef NUMBER_UTILS_H
#define NUMBER_UTILS_H

// #rspImagePlane <vector>   // vector
// #rspImagePlane <string>   // string
// #rspImagePlane <iostream> // cout, cerr
#include <cmath>    // fabs

// Radians / Degrees
#define RADIANS_TO_DEGREES 57.295779513082323 // 180.0/M_PI
#define DEGREES_TO_RADIANS 0.017453292519943295 // M_PI/180.0

// Memory Conversion
#define BYTES_TO_KILOBYTES 1024 // int(pow(2, 10))
#define BYTES_TO_MEGABYTES 1048576 // int(pow(2, 20))
#define BYTES_TO_GIGABYTES 1073741824 // int(pow(2, 30))
#define KILOBYTES_TO_MEGABYTES 1024 // int(pow(2, 10))
#define KILOBYTES_TO_GIGABYTES 1048576 // int(pow(2, 20))


namespace number
{
  static inline
  bool floatApproxEqual(float left, float right)
  {
    const float eps = 0.0001f;
    return fabs(left - right) < eps;
  }

}

#endif // NUMBER_UTILS_H
