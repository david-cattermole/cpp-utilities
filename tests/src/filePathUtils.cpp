/*
 * Test for "filePathUtils.h".
 */

#include <cstdlib>
#include <cassert>
#include <string>
#include <filePathUtils.h>
#include <debugUtils.h>


int main(int argc, char **argv)
{
    INFO("== Test filePathUtils.h ==");
    std::string path1 = "/projects/project/image.####.exr";
    std::string path2 = "/projects/project/image.%04d.exr";
    std::string path3 = "/projects/project/image.#.exr";
    std::string path4 = "/projects/project/image.%01d.exr";

    std::string result1 = filepath::formatFilePath(path1, 1001);
    std::string result2 = filepath::formatFilePath(path2, 1001);
    std::string result3 = filepath::formatFilePath(path3, 4);
    std::string result4 = filepath::formatFilePath(path4, 4);
    INFO("result1: " << result1);
    INFO("result2: " << result2);
    INFO("result3: " << result3);
    INFO("result4: " << result4);

    assert(result1 == "/projects/project/image.1001.exr");
    assert(result2 == "/projects/project/image.1001.exr");
    assert(result3 == "/projects/project/image.4.exr");
    assert(result4 == "/projects/project/image.4.exr");

    return EXIT_SUCCESS;
}
