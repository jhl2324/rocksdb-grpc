#include "wise/protocol/grpc_client.h"
#include <iostream>

int main() {
    std::string server_address("localhost:50051");
    RocksDBClient client(server_address);

    std::cout << "[CLIENT TEST] Connecting to gRPC Server at " << server_address << std::endl;

    // PutData 테스트
    std::string test_key = "test_key";
    std::string test_value = "Hello, gRPC with RocksDB!";
    
    bool put_success = client.PutData(test_key, test_value);
    std::cout << "[CLIENT TEST] PutData(" << test_key << ", " << test_value << ") -> " 
              << (put_success ? "SUCCESS" : "FAILED") << std::endl;

    // GetData 테스트
    auto [get_success, value] = client.GetData(test_key);
    if (get_success) {
        std::cout << "[CLIENT TEST] GetData(" << test_key << ") -> " << value << std::endl;
    } else {
        std::cout << "[CLIENT TEST] GetData(" << test_key << ") -> FAILED (Key Not Found)" << std::endl;
    }

    return 0;
}
