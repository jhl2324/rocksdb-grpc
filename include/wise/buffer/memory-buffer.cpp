//
// Created by EunhakLee on 1/22/25.
//

#include "memory-buffer.h"

using wise::buffer::MemoryBuffer;

MemoryBuffer &MemoryBuffer::operator<<(MemoryBuffer *sb) {
    this->write((void*)sb, sb->capacity());
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(bool n) {
    this->write((void*)&n, sizeof(bool));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(short n) {
    this->write((void*)&n, sizeof(short));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(unsigned short n) {
    this->write((void*)&n, sizeof(unsigned short));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(int n) {
    this->write((void*)&n, sizeof(int));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(unsigned int n) {
    this->write((void*)&n, sizeof(unsigned int));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(long n) {
    this->write((void*)&n, sizeof(long));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(unsigned long n) {
    this->write((void*)&n, sizeof(unsigned long));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(long long n) {
    this->write((void*)&n, sizeof(long long));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(unsigned long long n) {
    this->write((void*)&n, sizeof(unsigned long long));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(float n) {
    this->write((void*)&n, sizeof(float));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(double n) {
    this->write((void*)&n, sizeof(double));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(long double n) {
    this->write((void*)&n, sizeof(long double));
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(const std::string& _s) {
    MemoryBuffer _this = *this;
    auto c_str = _s.c_str();
    size_t length = strlen(c_str);

    write((void*)&length, sizeof(size_t));
    write((void*)c_str, sizeof(*c_str) * length);
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(wise::abc::Serializable* _s) {
    _s->serialize(this);
    return *this;
}

MemoryBuffer &MemoryBuffer::operator<<(wise::abc::Serializable& _s) {
    _s.serialize(this);
    return (MemoryBuffer &) *this;
}
