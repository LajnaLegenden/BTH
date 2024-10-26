//
// Created by lajna on 2024-10-26.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H


#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class StringUtils {
public:
    // Split string by delimiter
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }

        tokens.push_back(str.substr(start));
        return tokens;
    }

    // Join vector of strings with delimiter
    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
        std::stringstream ss;
        for (size_t i = 0; i < vec.size(); ++i) {
            ss << vec[i];
            if (i < vec.size() - 1) {
                ss << delimiter;
            }
        }
        return ss.str();
    }

    // Trim whitespace from start and end
    static std::string trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            start++;
        }

        auto end = str.end();
        do {
            end--;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        return std::string(start, end + 1);
    }

    // Convert to uppercase
    static std::string toUpper(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    // Convert to lowercase
    static std::string toLower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    // Check if string starts with prefix
    static bool startsWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() &&
               str.compare(0, prefix.size(), prefix) == 0;
    }

    // Check if string ends with suffix
    static bool endsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    // Replace all occurrences of a substring
    static std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t pos = 0;
        while ((pos = str.find(from, pos)) != std::string::npos) {
            str.replace(pos, from.length(), to);
            pos += to.length();
        }
        return str;
    }

    // Pad string to the left
    static std::string padLeft(const std::string& str, size_t length, char padChar = ' ') {
        if (length <= str.length()) return str;
        return std::string(length - str.length(), padChar) + str;
    }

    // Pad string to the right
    static std::string padRight(const std::string& str, size_t length, char padChar = ' ') {
        if (length <= str.length()) return str;
        return str + std::string(length - str.length(), padChar);
    }
};



#endif //STRINGUTILS_H
