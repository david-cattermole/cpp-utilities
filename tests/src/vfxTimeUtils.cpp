/*
 * Test for "stringUtils.h".
 */

#include <cstdlib>
#include <cassert>
#include <vfxTimeUtils.h>
#include <debugUtils.h>


int main(int argc, char **argv)
{
    INFO("== Test vfxTimeUtils.h ==");
    unsigned int fps = 24;
    double t1 = 23.48;
    double v1 = vfxtime::getSafeMayaTime(t1, fps);
    DBG("t1=" << t1);
    DBG("v1=" << v1);

    double t2 = 23.04;
    double v2 = vfxtime::getSafeMayaTime(t2, fps);
    DBG("t2=" << t2);
    DBG("v2=" << v2);

    assert(v1 == 23.48);
    assert(v2 == 23.04);

    return EXIT_SUCCESS;
}
