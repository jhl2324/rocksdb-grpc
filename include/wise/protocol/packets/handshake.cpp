//
// Created by EunhakLee on 1/22/25.
//

#include "handshake.h"

void wise::protocol::packet::Handshake::serialize(void *_p) {
    auto *buffer = (wise::buffer::MemoryBuffer *) _p;
}

uint16_t wise::protocol::packet::Handshake::packet_id() {
    return 0x01;
}
