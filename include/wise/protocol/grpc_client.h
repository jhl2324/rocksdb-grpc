#ifndef WISE_PROTOCOL_GRPC_CLIENT_H
#define WISE_PROTOCOL_GRPC_CLIENT_H

#include "wise/api/grpc_service.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <string>

class RocksDBClient {
public:
    explicit RocksDBClient(const std::string& server_address);
    
    bool PutData(const std::string& key, const std::string& value);
    std::pair<bool, std::string> GetData(const std::string& key);

private:
    std::unique_ptr<wise::api::RocksDBService::Stub> stub_;
};

#endif  // WISE_PROTOCOL_GRPC_CLIENT_H
