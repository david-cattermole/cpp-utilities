/*
 * Test for "stringUtils.h".
 */

#include <cstdlib>
#include <cassert>
#include <stringUtils.h>
#include <debugUtils.h>


int main(int argc, char **argv)
{
    INFO("== Test stringUtils.h ==");
    double x1 = 42.0;
    float y1 = 3.147;
    int z1 = 42;
    std::string s1 = string::numberToString<double>(x1);
    std::string s2 = string::numberToString<float>(y1);
    std::string s3 = string::numberToString<int>(z1);

    double x2 = string::stringToNumber<double>(s1);
    float y2 = string::stringToNumber<float>(s2);
    int z2 = string::stringToNumber<int>(s3);

    DBG("x1=" << x1 << ", x2=" << x2);
    DBG("y1=" << y1 << ", y2=" << y2);
    DBG("zz=" << z1 << ", z2=" << z2);

    assert(x1 == x2);
    assert(y1 == y2);
    assert(z1 == z2);

    return EXIT_SUCCESS;
}
