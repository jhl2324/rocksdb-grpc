//
// Created by EunhakLee on 1/22/25.
//

#ifndef L0_CACHE_TEST_HANDSHAKE_H
#define L0_CACHE_TEST_HANDSHAKE_H

#include "../base.h"
#include <cstdint>
#include <string>

namespace wise::protocol::packet {

class Handshake : public WisePacket {
public:
    uint64_t machine_id;

    void serialize(void*) override;

    uint16_t packet_id() override;
};

}

#endif //L0_CACHE_TEST_HANDSHAKE_H
