/*! Utilities related to file systems.
 */

#ifndef FILESYSTEM_UTILS_H
#define FILESYSTEM_UTILS_H

// Utils
#include <numberUtils.h>

// STL
#include <cmath>     // floor, ceil, round, pow
#include <cstdio>    // FILE
#include <cstdint>   // uint64_t
#include <sstream>   // stringstream
#include <string>    // string
#include <vector>    // vector
#include <fstream>   // ifstream
#include <iostream>  // cout, cerr, endl
#include <algorithm> //

// Linux
#include <sys/stat.h>  // stat
#include <unistd.h>    // sysconf

// Dir Ent
#include <dirent.h>

namespace filesystem
{

  // Checks if file find
  //
  // NOTE: Linux is supported specifically, other operating systems use portable C functions (for now).
  //
  // http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
  inline
  bool filePathExists(const std::string &filePath)
  {
#ifdef __linux__
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
#else
    if (FILE *file = fopen(m_filePath.c_str(), "r"))
      {
        fclose(file);
        return true;
      }
    return false;
#endif
  }

// Write data directly to disk.
//
// http://stackoverflow.com/questions/11563963/writing-a-binary-file-in-c-very-fast
//
  inline
  void writeToDisk(std::string filepath, std::size_t dataSize, void *dataPtr)
  {
    std::size_t chunkSize = 2 * BYTES_TO_MEGABYTES;
    std::size_t chunkNums = (size_t) ceil((double) dataSize / (double) chunkSize);

    FILE *pFile;
    pFile = fopen(filepath.c_str(), "wb");
    for (std::size_t j = 0; j < chunkNums; ++j)
    {
      std::size_t offset = j * chunkSize;
      std::size_t s = std::min(chunkSize, dataSize - offset);
      void *offsetPtr = dataPtr + s;
      fwrite(offsetPtr, 1, s, pFile);
    }
    fclose(pFile);
  }

// Get the contents of a directory.
//
// http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//
// NOTE: Files are listed non-sorted. '.' and '..' are also listed.
//

  // Returns a list of sorted files in a directory (except the ones
  // that begin with a dot)
  //
  // http://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c
  inline
  void getFilesInDirectory(std::vector<std::string> &out,
                           const std::string &directory,
                           bool withHidden)
  {
#ifdef WINDOWS
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
    {
      return; /* No files found */
    }

    do
    {
      const std::string file_name = file_data.cFileName;
      const std::string full_file_name = directory + "/" + file_name;
      if ((file_name[0] == '.') && withHidden)
      {
        continue;
      }

      const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
      if (is_directory)
      {
        continue;
      }

      out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#else
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL)
    {
      const std::string file_name = ent->d_name;
      const std::string full_file_name = directory + "/" + file_name;
      if ((file_name[0] == '.') && withHidden)
      {
        continue;
      }

      if (stat(full_file_name.c_str(), &st) == -1)
      {
        continue;
      }

      const bool is_directory = (st.st_mode & S_IFDIR) != 0;
      if (is_directory)
      {
        continue;
      }

      out.push_back(full_file_name);
    }
    closedir(dir);
    std::sort(out.begin(), out.end());
#endif
  }

  // Print the contents of the directory, unsorted.
  inline
  bool printDirectory(std::string path)
  {
    DIR *dir;
    if ((dir = opendir(path.c_str())) != NULL)
    {
      // print all the files and directories within directory
      std::cout << "Directory: " << path << std::endl;
      struct dirent *ent;
      while ((ent = readdir(dir)) != NULL)
      {
        std::cout << ent->d_name << std::endl;
      }
      closedir(dir);
    }
    else
    {
      // could not open directory
      std::cout << "Directory does not exist: " << path << std::endl;
      return false;
    }
    return true;
  }

};

#endif // FILESYSTEM_UTILS_H
