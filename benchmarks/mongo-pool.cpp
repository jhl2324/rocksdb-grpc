#include <iostream>
#include <thread>
#include <chrono>

#include "utils.h"
#include "wise/mongo-adapter.h"
#include <bsoncxx/builder/basic/document.hpp>

using namespace wise::adapter;
using namespace bsoncxx::builder::basic;


#define SAMPLE_COUNT 100000
bool flag = true;
uint64_t doc_count;

auto thread_writes = [](mongo *adapter) {
    auto client = adapter->acquire();
    auto db = client["wise"];
    auto collection = db["logs"];

    printf("\r\nWaiting 5 seconds to write\n");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    printf("\r\nInserting %d documents\n", SAMPLE_COUNT);

    auto time = MEASURE(&collection) {
        for (int i = 0; i < SAMPLE_COUNT; i++) {
            collection.insert_one(make_document(kvp("index", i)));
        }
    }MEASURE_END();
    printf("\rElapsed %lld millisecond\n", time.count());

    printf("\r\nWaiting 5 seconds to purge\n");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    printf("\r\nDeleting all documents\n");
    time = MEASURE(&collection) {
        collection.delete_many({});
    }MEASURE_END();
    printf("\rElapsed %lld millisecond\n", time.count());
    printf("\r\nDone!\n");
};

auto thread_reads = [](mongo *adapter) {
    auto client = adapter->acquire();
    auto db = client["wise"];
    auto collection = db["logs"];

    do {
        try {
            auto result = collection.count_documents({});
            doc_count = result;
        } catch (std::exception &e) {
            printf("\r\nError!\n");
            flag = false;
        }
    } while (flag);
    printf("\r\nreader exited with flag=%d\n", flag);
};

auto thread_print = []() {
    do {
        printf("\r%llu", doc_count);
    } while (flag);
    printf("\r\nprinter exited with flag=%d\n", flag);
};

int main(int argc, char *argv[]) {
    mongo adapter_mongo;
    adapter_mongo.host = "127.0.0.1";
    adapter_mongo.port = 27017;
    adapter_mongo.initialize();

    auto client = adapter_mongo.acquire();
    auto db = client["wise"];

    std::thread reader([&]() {
        thread_reads(&adapter_mongo);
    });
    std::thread printer([&]() {
        thread_print();
    });
    std::thread writer([&]() {
        thread_writes(&adapter_mongo);
    });

    writer.join();
    flag = false;
    reader.join();
    printer.join();

    return 0;
}
