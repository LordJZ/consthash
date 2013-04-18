consthash
=========

This is a header-only library for C++11 used to compute various hash functions at compile time.
All dependencies are required for tests only.

Big-endian is most likely broken for now.

_____________
Currently supported:

- CRC 32 bit
- CRC 64 bit
- Google CityHash 32 bit
- Google CityHash 64 bit (0/1/2 seed versions)
- Google CityHash 128 bit (0/1 seed versions)

_____________
Usage example:

    #include <consthash/all.hxx>

    // Compute CRC 32
    constexpr uint32_t result = consthash::crc32("Hey", 3);

    // Use the value in template arguments
    std::array<int, result> huge_array;

    // Compute CityHash 64
    constexpr uint64_t result = consthash::city64("Hello World", 11);

    // Compute CityHash 128
    constexpr uint128_t result = consthash::city128("Save Rock and Roll", 18);

    // Use 128-bit value as template argument
    template<class VALUE> class my_class
    {
        static constexpr uint128_t value() { return CT2RT128(VALUE); }
    };
    my_class<RT2CT128_T(result)> instance;
