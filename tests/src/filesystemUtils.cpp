/*
 * Tests for "filesystemUtils.h"
 */

#include <cstdlib>
#include <string>
#include <vector>
#include <filesystemUtils.h>
#include <debugUtils.h>

int main(int argc, char **argv)
{
    INFO("== Test filesystemUtils.h ==");
    typedef std::vector<std::string> FilesList;
    typedef FilesList::iterator FilesListIt;
    typedef FilesList::const_iterator FilesListCIt;

    FilesList filePaths;
    std::string dir = ".";
    bool withHidden = true;
    bool exists = false;

    // Print the directory contents and check if the files exist.
    INFO("Directory: " << dir);
    filesystem::getFilesInDirectory(filePaths, dir, withHidden);
    FilesListCIt it = filePaths.cbegin();
    for (; it != filePaths.cend(); ++it)
    {
        INFO("File Path: " << *it);
        exists = filesystem::filePathExists(*it);
        if (exists) {
            INFO("File Exists");
        }
    }

    // Print the directory.
    filesystem::printDirectory(dir);

    // TODO: Write test for "filesystem::writeToDisk();".

    return EXIT_SUCCESS;
}
