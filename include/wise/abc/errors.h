//
// Created by EunhakLee on 1/23/25.
//

#ifndef L0_CACHE_TEST_ERRORS_H
#define L0_CACHE_TEST_ERRORS_H

#include <stdexcept>

namespace wise::abc {
    class not_implemented : public std::logic_error {
    public:
        explicit not_implemented(const std::string &_s) : std::logic_error(_s) {}

        explicit not_implemented(const char *_s) : std::logic_error(_s) {}

//    ~not_implemented() _NOEXCEPT override;
    };
}

#endif //L0_CACHE_TEST_ERRORS_H
