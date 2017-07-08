/*
 * Test for "osMemoryUtils.h".
 */

#include <cstdlib>
#include <cassert>
#include <debugUtils.h>
#include <osMemoryUtils.h>

int main(int argc, char **argv)
{
    INFO("== Test osMemoryUtils.h ==");
    std::size_t size = 0;
    size = osmemory::get_total_system_memory();
    assert(size > 0);
    DBG("osmemory::get_total_system_memory() = " << size);

    std::size_t vm_usage = 0;
    std::size_t resident_set = 0;
    osmemory::process_mem_usage(vm_usage, resident_set);
    assert(vm_usage > 0);
    assert(resident_set > 0);
    DBG("osmemory::process_mem_usage("
                << "vm_usage = " << vm_usage
                << ", resident_set = " << resident_set
                << ")");

    return EXIT_SUCCESS;
}
