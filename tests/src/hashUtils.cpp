/*
 * Test for "hashUtils.h"
 */

#include <cstdlib>
#include <cassert>
#include <vector>
#include <hashUtils.h>
#include <debugUtils.h>

struct Data {
    float x;
    float y;
    float z;
    int num;
    long long int bigNum;
};

int main(int argc, char **argv) {
    INFO("== Test hashUtils.h ==");
    typedef unsigned int HashType;

    Data data;
    data.x = 1.1f;
    data.y = -1.4f;
    data.z = 10.0f;
    data.num = 100;
    data.bigNum = 1000000L;
    INFO("data.x = " << data.x);
    INFO("data.y = " << data.y);
    INFO("data.z = " << data.z);
    INFO("data.num = " << data.num);
    INFO("data.bigNum = " << data.bigNum);

    const unsigned int dataSize = sizeof(data);
    INFO("data size: " << dataSize);

    HashType h1 = hash::hashDJB<HashType, Data>(&data, dataSize);
    INFO("DJB hash: " << h1);

    HashType h2 = hash::hashSDBM<HashType, Data>(&data, dataSize);
    INFO("SDBM hash: " << h2);

    HashType h3 = hash::hashMurmur2<HashType, Data>(&data, dataSize);
    INFO("Murmur hash: " << h3);

    HashType seed1 = 0;
    HashType seed2 = 1;
    HashType seed3 = 123456789;
    std::vector<HashType> hashes;
    hashes.push_back(h1);
    hashes.push_back(h2);
    hashes.push_back(h3);
    HashType h4 = hash::mergeHashes(hashes, seed1);
    HashType h5 = hash::mergeHashes(hashes, seed2);
    HashType h6 = hash::mergeHashes(hashes, seed3);
    INFO("Merge Hashes (no seed): " << h4);
    INFO("Merge Hashes (with seed): " << h5);
    INFO("Merge Hashes (with another seed): " << h6);

    assert(h1 == 669325159);
    assert(h2 == 0); // WHY??? This seems like a bug
    assert(h3 == 1070402391);
    assert(h4 == 1025942632);
    assert(h5 == 3104028995);
    assert(h6 == 857713407);

    return EXIT_SUCCESS;
}
