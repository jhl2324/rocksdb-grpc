//
// Created by EunhakLee on 1/22/25.
//

#include "mongo-adapter.h"
#include <stdexcept>

namespace wise::adapter {

mongocxx::instance instance;

mongocxx::uri mongo::build_uri() const {
    std::string url = "mongodb://";
    url += this->host;
    url += ":";
    url += std::to_string(this->port);
    if (!this->dbname.empty()) {
        url += "/";
        url += this->dbname;
    }

    return {url};
}

void mongo::initialize() {
    this->pool = new mongocxx::pool(this->build_uri());
}

    mongocxx::pool::entry mongo::acquire() {
        if (this->pool == nullptr)
            throw std::runtime_error("adapter is not initialized");
        return this->pool->acquire();
    }
}

