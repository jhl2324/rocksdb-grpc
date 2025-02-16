//
// Created by EunhakLee on 1/22/25.
//

#ifndef L0_CACHE_TEST_MEMORYBUFFER_H
#define L0_CACHE_TEST_MEMORYBUFFER_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include "wise/abc/serializable.h"

#define WISE_SERIALIZE_TYPE uint8_t

namespace wise::buffer {

class MemoryBuffer {
protected:
    WISE_SERIALIZE_TYPE *cursor;
    WISE_SERIALIZE_TYPE *begin, *end;

    bool _check_cursor_position() {
        return begin <= cursor && cursor <= end;
    }

    size_t _remaining_capacity() {
        if (!_check_cursor_position()) return (size_t) 0;
        return (size_t) (end - cursor);
    }

    void reset_cursor() {
        this->cursor = this->begin;
    }

    static size_t _generalize_size(size_t org) {
        size_t quotient = (org / sizeof(WISE_SERIALIZE_TYPE)) * sizeof(WISE_SERIALIZE_TYPE);
        if (quotient == org) return org;
        return quotient + sizeof(WISE_SERIALIZE_TYPE);
    }

public:
    MemoryBuffer(WISE_SERIALIZE_TYPE *begin, WISE_SERIALIZE_TYPE *end) {
        this->begin = begin;
        this->end = end;
        this->cursor = begin;
    }

    bool write(void *src, size_t len) {
        if (len > _remaining_capacity()) return false;
        memcpy(this->cursor, src, len);
        size_t delta = _generalize_size(len);
        this->cursor = this->cursor + delta;
        return true;
    }

    size_t offset() {
        return (size_t) (this->cursor - this->begin);
    }

    size_t capacity() {
        return (size_t) (this->end - this->begin);
    }

    bool seek(uint8_t *pos) {
        if (this->begin <= pos && pos <= this->end) return false;

        this->cursor = pos;
        return true;
    }

    MemoryBuffer &operator<<(MemoryBuffer *_sb);
    MemoryBuffer &operator<<(bool _n);
    MemoryBuffer &operator<<(short _n);
    MemoryBuffer &operator<<(unsigned short _n);
    MemoryBuffer &operator<<(int _n);
    MemoryBuffer &operator<<(unsigned int _n);
    MemoryBuffer &operator<<(long _n);
    MemoryBuffer &operator<<(unsigned long _n);
    MemoryBuffer &operator<<(long long _n);
    MemoryBuffer &operator<<(unsigned long long _n);
    MemoryBuffer &operator<<(float _f);
    MemoryBuffer &operator<<(double _f);
    MemoryBuffer &operator<<(long double _f);
    MemoryBuffer &operator<<(const std::string& _s);
    MemoryBuffer &operator<<(wise::abc::Serializable *_s);
    MemoryBuffer &operator<<(wise::abc::Serializable &_s);
};

}


#endif //L0_CACHE_TEST_MEMORYBUFFER_H
