// Copyright (C) 2018-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief This is a header file with common inference engine definitions
 * 
 * @file ie_unicode.hpp
 */
#pragma once

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#ifdef UNICODE
typedef wchar_t tchar;
typedef std::wstring file_name_t;
#else
typedef char tchar;
typedef std::string file_name_t;
#endif

namespace InferenceEngine {

/**
 * @deprecated Use OS-native conversion utilities
 * @brief Conversion from possibly-wide character string to a single-byte chain.
 * @param str A possibly-wide character string
 * @return A single-byte character string
 */
INFERENCE_ENGINE_DEPRECATED("Use OS-native conversion utilities")
inline std::string fileNameToString(const file_name_t& str) {
#ifdef UNICODE
    size_t maxlen = (str.length() + 1) * sizeof(wchar_t) / sizeof(char);
    std::vector<char> mbstr(maxlen);
    mbstr[0] = 0;
    std::wcstombs(&mbstr[0], str.c_str(), maxlen);
    std::string res = std::string(&mbstr[0]);
    return res;
#else
    return str;
#endif
}

/**
 * @deprecated Use OS-native conversion utilities
 * @brief Conversion from single-byte character string to a possibly-wide one
 * @param str A single-byte character string
 * @return A possibly-wide character string
 */
INFERENCE_ENGINE_DEPRECATED("Use OS-native conversion utilities")
inline file_name_t stringToFileName(const std::string& str) {
#ifdef UNICODE
    size_t maxlen = str.length() + 1;
    std::vector<wchar_t> wcstr(maxlen);
    wcstr[0] = 0;
    std::mbstowcs(&wcstr[0], str.c_str(), maxlen);
    file_name_t res = file_name_t(&wcstr[0]);
    return res;
#else
    return str;
#endif
}

}  // namespace InferenceEngine
