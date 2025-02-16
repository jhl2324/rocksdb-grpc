#include <iostream>
#include <random>

#include "utils.h"
#include <rocksdb/db.h>

#include <thread>

#define BUF_SIZE 128
#define DATABASE_PATH "./tmp/rocks"

#define THREAD_COUNT 32
#define SAMPLE_COUNT (THREAD_COUNT * 10000)
int SAMPLE_PER_THREAD = SAMPLE_COUNT / THREAD_COUNT;

rocksdb::DB *db;
std::string fileContent;

void thread_callback(int index) {
    // std::cout << std::this_thread::get_id() << ": " << index << '\n';
    // std::cout << "Generating random keys...\n";

    int base_index = index * SAMPLE_PER_THREAD;
    rocksdb::WriteOptions wo;

    const auto time = MEASURE(base_index, wo)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, INT32_MAX);
        rocksdb::Status status;

        for (int i = base_index; i < base_index + SAMPLE_PER_THREAD; i++) {
            std::string key = "krby-obj-" + std::to_string(i);
            std::string value = fileContent;
            status = db->Put(wo, key, value);
            assert(status.ok());
        }
    }
    MEASURE_END();

    const double timePerSample = 1.0 * time.count() / SAMPLE_PER_THREAD;
    std::cout << "[" << std::this_thread::get_id() << "] sample " << SAMPLE_PER_THREAD
        << ", elapsed " << time.count() << "ms (" << timePerSample << "ms/it), "
        << 1000 / timePerSample << "it/s\n";
}

int main() {
    FILE* fp;
    fopen_s(&fp, R"(C:\Users\enak\CLionProjects\l0-cache\12420000.json)", "r");

    char FILE_BUF[1024] = {0};
    int i = 0;
    do {
        FILE_BUF[i++] = fgetc(fp);
    } while (FILE_BUF[i - 1] != EOF);

    std::cout << FILE_BUF << '\n';
    fileContent = std::string(FILE_BUF);

    rocksdb::Options options;
    options.IncreaseParallelism(32);
    options.OptimizeLevelStyleCompaction();
    options.create_if_missing = true;
    options.max_background_jobs = 32 * 4;
    options.max_subcompactions = THREAD_COUNT;
    // options.max_open_files = 10000;
    // options.use_fsync = false;
    // options.bytes_per_sync = INT32_MAX;
    // options.write_buffer_size = 64 * 1024 * 1024;
    // options.max_write_buffer_number = THREAD_COUNT;

    rocksdb::Status status = rocksdb::DB::Open(options, DATABASE_PATH, &db);
    if (!status.ok()) {
        std::cerr << status.ToString() << std::endl;
        return 1;
    }
    assert(status.ok());

    rocksdb::WriteOptions wo;
    status = db->Put(wo, "krby-stat-foo", "bar");
    assert(status.ok());
    std::cout << "Put key success\n";

    std::thread THREADS[THREAD_COUNT];

    auto start = std::chrono::high_resolution_clock ::now().time_since_epoch();
    for (int j = 0; j < THREAD_COUNT; j++) {
        THREADS[j] = std::thread(thread_callback, j);
    }
    for (auto & j : THREADS) {
        j.join();
    }
    auto end = std::chrono::high_resolution_clock ::now().time_since_epoch();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto itemPerSecond = 1000.0 * elapsed / SAMPLE_COUNT;
    std::cout << "Total samples: " << SAMPLE_COUNT << "\n";
    std::cout << "ms/it " << 1.0 * SAMPLE_COUNT / elapsed << "\n";
    std::cout << "Items/s: " << itemPerSecond << "\n";

    db->Close();
    return 0;
}
