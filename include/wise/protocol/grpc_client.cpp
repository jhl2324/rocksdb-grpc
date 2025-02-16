#include "wise/protocol/grpc_client.h"

RocksDBClient::RocksDBClient(const std::string& server_address) {
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    stub_ = wise::api::RocksDBService::NewStub(channel);
}

bool RocksDBClient::PutData(const std::string& key, const std::string& value) {
    wise::api::PutRequest request;
    request.set_key(key);
    request.set_value(value);

    wise::api::PutResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->PutData(&context, request, &response);
    return status.ok() && response.success();
}

std::pair<bool, std::string> RocksDBClient::GetData(const std::string& key) {
    wise::api::GetRequest request;
    request.set_key(key);

    wise::api::GetResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetData(&context, request, &response);
    if (status.ok() && response.found()) {
        return {true, response.value()};
    }
    return {false, ""};
}
