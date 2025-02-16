//
// Created by EunhakLee on 1/22/25.
//

#ifndef L0_CACHE_TEST_MONGO_ADAPTER_H
#define L0_CACHE_TEST_MONGO_ADAPTER_H


#include <string>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>

extern mongocxx::instance instance;

namespace wise::adapter {

class mongo {
private:
    [[nodiscard]] mongocxx::uri build_uri() const;

    mongocxx::pool *pool;

public:
    std::string host;
    int port;
    std::string dbname;


    void initialize();

    mongocxx::pool::entry acquire();
};

}


#endif //L0_CACHE_TEST_MONGO_ADAPTER_H
