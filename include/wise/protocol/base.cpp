//
// Created by EunhakLee on 1/22/25.
//

#include "base.h"
#include "wise/abc/errors.h"

void wise::protocol::WisePacket::serialize(void *) {

}

uint16_t wise::protocol::WisePacket::packet_id() {
    throw wise::abc::not_implemented("override this function");
}
