//
// Created by EunhakLee on 1/22/25.
//

#ifndef L0_CACHE_TEST_BASE_H
#define L0_CACHE_TEST_BASE_H

#include "../buffer/memory-buffer.h"
#include "wise/abc/serializable.h"

namespace wise::protocol {

class WisePacket : public wise::abc::Serializable {
public:
    virtual uint16_t packet_id();
    void serialize(void*) override;
};

}

#endif //L0_CACHE_TEST_BASE_H
