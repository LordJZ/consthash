consthash
=========

This is a header-only library for C++11 used to compute various hash functions at compile time.
All dependencies are required for tests only.

Big-endian is most likely broken for now.

_____________
Currently supported:

- CRC 32 bit
- CRC 64 bit
- Google CityHash 64

_____________
Usage example:

    #include <consthash/all.hxx>

    // Compute CRC 32
    constexpr uint32_t result = consthash::crc32("Hey", 3);

    // Use the value in template arguments
    std::array<int, result> huge_array;

    // Compute CityHash 64
    constexpr uint64_t result = consthash::city64("Hello World", 11);
