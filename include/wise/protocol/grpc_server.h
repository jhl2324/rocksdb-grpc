#ifndef WISE_PROTOCOL_GRPC_SERVER_H
#define WISE_PROTOCOL_GRPC_SERVER_H

#include "wise/storage/rocksdb_adapter.h"
#include "wise/api/grpc_service.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class RocksDBServiceImpl final : public wise::api::RocksDBService::Service {
public:
    explicit RocksDBServiceImpl(RocksDBAdapter *db_adapter);
    
    grpc::Status PutData(grpc::ServerContext* context, const wise::api::PutRequest* request, wise::api::PutResponse* response) override;
    
    grpc::Status GetData(grpc::ServerContext* context, const wise::api::GetRequest* request, wise::api::GetResponse* response) override;

private:
    RocksDBAdapter *db;
};

#endif
