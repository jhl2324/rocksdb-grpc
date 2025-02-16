//
// Created by EunhakLee on 1/22/25.
//

#ifndef L0_CACHE_TEST_SERIALIZABLE_H
#define L0_CACHE_TEST_SERIALIZABLE_H

#include <cstddef>

namespace wise::abc {

class Serializable {
public:
    virtual void serialize(void*) = 0;
};

}

#endif //L0_CACHE_TEST_SERIALIZABLE_H
