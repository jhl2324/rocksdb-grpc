//
// Created by EunhakLee on 1/23/25.
//

#ifndef L0_CACHE_TEST_UTILS_H
#define L0_CACHE_TEST_UTILS_H

#define hexdump(_buf, _bufsize) printf("   "); \
    for (int _i = 0; _i < ((_bufsize >= 16) ? 16 : _bufsize); _i++) printf("%2x ", _i); \
    printf("\n 0 "); \
    for (int _i = 0; _i < _bufsize; _i++) { \
    printf("%02x ", ((uint8_t*)_buf)[_i] & 0xffff); \
    if ((_i + 1) % 16 == 0 && _i + 1 != _bufsize) printf("\b\n%2x ", (_i+1)/16); \
    } \
    printf("\b\n");

#define hexdump2(_buf, _bufsize) printf("{ "); \
    for (int _i = 0; _i < _bufsize; _i++) { \
    printf("0x%02x, ", ((uint8_t*)_buf)[_i] & 0xffff); \
    } \
    printf("\b\b }\n");

#define MEASURE(...) [__VA_ARGS__]() { \
    auto start = std::chrono::high_resolution_clock ::now().time_since_epoch(); \
    [__VA_ARGS__]() \

#define MEASURE_END() (); \
    auto end = std::chrono::high_resolution_clock ::now().time_since_epoch(); \
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start); \
    }();

#endif //L0_CACHE_TEST_UTILS_H
