/*
 * Test for "numberUtils.h".
 */

#include <cstdlib>
#include <cassert>
#include <numberUtils.h>
#include <debugUtils.h>

int main(int argc, char **argv)
{
    INFO("== Test numberUtils.h ==");
    bool ok;
    float x = 1.1f;
    float y = 1.100001f;
    double m = 1.2;
    double n = 1.1;
    double eps = 0.1;

    ok = number::floatApproxEqual(x, y);
    DBG("number::floatApproxEqual(x, y) == " << ok);
    assert(ok);

    ok = number::isApproxEqual<float>(x, y);
    DBG("number::isApproxEqual<float>(x, y) == " << ok);
    assert(ok);

    ok = number::isApproxEqual<double>(x, y);
    DBG("number::isApproxEqual<double>(x, y) == " << ok);
    assert(ok);

    ok = number::isApproxEqual<double>(m, n);
    DBG("number::isApproxEqual<double>(m, n) == " << ok);
    assert(!ok);

    ok = number::isApproxEqual<double>(m, n, eps);
    DBG("number::isApproxEqual<double>(m, n, eps) == " << ok);
    assert(ok);

    return EXIT_SUCCESS;
}
