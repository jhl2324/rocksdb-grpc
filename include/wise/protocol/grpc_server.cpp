#include "wise/protocol/grpc_server.h"

RocksDBServiceImpl::RocksDBServiceImpl(RocksDBAdapter *db_adapter) : db(db_adapter) {}

grpc::Status RocksDBServiceImpl::PutData(grpc::ServerContext* context, const wise::api::PutRequest* request, wise::api::PutResponse* response) {
    response->set_success(db->Put(request->key(), request->value()));
    return grpc::Status::OK;
}

grpc::Status RocksDBServiceImpl::GetData(grpc::ServerContext* context, const wise::api::GetRequest* request, wise::api::GetResponse* response) {
    std::string value;
    bool found = db->Get(request->key(), value);
    response->set_value(value);
    response->set_found(found);
    return grpc::Status::OK;
}
