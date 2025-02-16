#include <iostream>
#include <cassert>

#include "utils.h"
#include "wise/buffer/memory-buffer.h"

using namespace wise;

#define BUFFER_SIZE 128

int test_003_memorybuffer(int argc, char *argv[]) {
    auto *_buffer = new WISE_SERIALIZE_TYPE[BUFFER_SIZE];
    buffer::MemoryBuffer buffer(_buffer, _buffer + BUFFER_SIZE);

    buffer << (uint32_t) 0x123456;
    hexdump(_buffer, buffer.offset())

    buffer << 0xabcdef;
    hexdump(_buffer, buffer.offset())

    assert(*(uint32_t *) (_buffer + 0) == 0x123456);
    assert(*(uint32_t *) (_buffer + sizeof(uint32_t)) == 0xabcdef);

    WISE_SERIALIZE_TYPE compare[] = {0x56, 0x34, 0x12, 0x00, 0xef, 0xcd, 0xab, 0x00};
    for (int i = 0; i < sizeof(compare); i++) {
        assert(compare[i] == _buffer[i]);
    }

    /* Final dump is:
     *     0  1  2  3  4  5  6  7
     *  0 56 34 12 00 ef cd ab 00
     */

    return 0;
}
