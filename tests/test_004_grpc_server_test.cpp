#include "wise/protocol/grpc_server.h"
#include "wise/storage/rocksdb_adapter.h"

#include <grpcpp/grpcpp.h>
#include <iostream>
#include <thread>
#include <chrono>

void RunTestServer() {
    std::string server_address("0.0.0.0:50051");
    RocksDBAdapter db_adapter("./rocksdb_test");
    RocksDBServiceImpl service(&db_adapter);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "[SERVER] gRPC Test Server running on " << server_address << std::endl;
    
    server->Wait();
}

int main() {
    std::cout << "[TEST] Starting gRPC Server Test" << std::endl;

    // 테스트 서버 실행 (비동기 스레드로 실행)
    std::thread server_thread(RunTestServer);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 서버가 실행될 시간 확보

    std::cout << "[TEST] gRPC Server Test Running. Now run the client test." << std::endl;
    std::cout << "[TEST] Press Ctrl+C to stop the server manually." << std::endl;

    server_thread.join(); // 서버 실행을 계속 유지
    return 0;
}
