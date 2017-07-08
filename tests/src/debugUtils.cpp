/*
 * Tests for "debugUtils.h".
 */

#include <cstdlib>
#include <debugUtils.h>

int main(int argc, char **argv)
{
    INFO("== Test debugUtils.h ==");
    unsigned int num = 100000000;

    // Test TimestampBenchmark.
    debug::TimestampBenchmark timeBenchmark;
    timeBenchmark.start();
    long double k = 0;
    for (long int i=0; i<num; ++i)
    {
        k += (i*i) + i;
    }
    timeBenchmark.stop();

    // Test TimestampBenchmark.
    debug::CPUBenchmark cpuBenchmark;
    cpuBenchmark.start();
    long double j = 0;
    for (long int i=0; i<num; ++i)
    {
        k += (i*i) + i;
    }
    cpuBenchmark.stop();

    // Print out some info
    timeBenchmark.printInSec("Test");
    timeBenchmark.printInSec("Test", num);
    DBG("total time=" << timeBenchmark.timestampTotal);
    DBG("total ticks=" << cpuBenchmark.ticktime);
    INFO("k=" << k);
    WRN("k=" << k);
    ERR("k=" << k);
    DBG("k=" << k);
    return EXIT_SUCCESS;
}
