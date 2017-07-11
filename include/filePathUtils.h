/*! Utilities for time sampling for visual effects.
 */

#ifndef FILE_PATH_UTILS_H
#define FILE_PATH_UTILS_H

#include <vector>
#include <string>
#include "stringUtils.h"

namespace filepath {

    // TODO: Get file number from file path string.
    // TODO: Add file number with padding into string.

    /*! Parses a file path and returns index values for splitting/replacing the frame number.
     *
     * @param filePath [in] File path string.
     * @param start [out] Start index.
     * @param end [out] End index.
     * @param length [out] Length.
     * @return true or false.
     */
    bool parseFilePath(const std::string &filePath,
                       std::size_t *start,
                       std::size_t *end,
                       int *length) {
        bool result = false;
        *start = 0;
        *end = 0;
        *length = 0;

        std::size_t foundPoundStart = filePath.find("#", 0, 1);
        std::size_t foundFormatStart = filePath.find("%0", 0, 2);
        if ((foundFormatStart != std::string::npos) ||
            (foundPoundStart != std::string::npos)) {
            std::size_t foundNumStart = std::string::npos;
            std::size_t foundNumEnd = std::string::npos;
            size_t num = 0;

            if (foundFormatStart != std::string::npos) {
                std::size_t foundFormatEnd = filePath.find("d", foundFormatStart, 1);
                if (foundFormatEnd != std::string::npos) {
                    foundNumStart = foundFormatStart;
                    foundNumEnd = foundFormatEnd;

                    // Get number of padding.
                    std::size_t startNum = foundNumStart + 2;
                    std::size_t endNum = foundNumEnd;
                    std::string numAsString = "";
                    for (std::size_t i = startNum; i < endNum; i++) {
                        const char *letter = &filePath.at(i);
                        numAsString.append(letter);
                    }
                    num = string::stringToNumber<size_t>(numAsString);
                }
            } else {
                size_t i = foundPoundStart;
                char letter = filePath.at(i);
                while (letter == '#') {
                    letter = filePath.at(i);
                    i++;
                }

                foundNumStart = foundPoundStart;
                foundNumEnd = i - 2;
                num = (i - foundNumStart) - 1;
            }

            *length = (int) num;
            *start = foundNumStart;
            *end = foundNumEnd + 1;
            result = true;
        }

        return result;
    }

    /*! Lookup File Path.
     * Replaces the image sequence frame placeholder with a formatted frame value.
     *
     * @param path [in] File path, with '####' or '%04d' style placeholder tokens.
     * @param frameNumber [in] Frame number to format.
     * @return Formatted file path string.
     */
    std::string formatFilePath(const std::string &path,
                               const int &frameNumber) {
        std::string result(path);

        std::size_t start = 0;
        std::size_t end = 0;
        int length = 0;
        bool ok = parseFilePath(path, &start, &end, &length);

        if (ok) {
            // Create final number string.
            std::ostringstream stream;
            stream.fill('0');
            stream.width(length);
            stream << frameNumber << "\0";
            std::string numStr = stream.str();

            // do the padding.
            std::size_t startReplace = start;
            std::size_t endReplace = end;
            result.erase(startReplace, endReplace - startReplace);
            result.insert(startReplace, numStr);
        }

        return result;
    }
}

#endif // FILE_PATH_UTILS_H
