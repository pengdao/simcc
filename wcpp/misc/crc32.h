#pragma once

#include "wcpp/wcpp_export.h"
#include <stdint.h>
#include <string>

namespace wcpp {

class WCPP_EXPORT CRC32 {
public:
    // @brief
    // @param d   Source data buffer, If length is length than dwLength, result is unknown.
    // @param len The size of d.
    // @return crc value.
    static uint32_t Sum(const void* d, size_t len);
    static uint32_t Sum(const std::string& s) {
        return Sum(s.data(), s.size());
    }

private:
    // Initialize the CRC table with 256 elements.
    static void InitTable(uint32_t* table);
    static uint32_t Reflect(uint32_t ref, char ch);
};
}