#include "wise/storage/rocksdb_adapter.h"

RocksDBAdapter::RocksDBAdapter(const std::string &db_path) {
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);
}

RocksDBAdapter::~RocksDBAdapter() {
    delete db;
}

bool RocksDBAdapter::Put(const std::string &key, const std::string &value) {
    rocksdb::WriteOptions wo;
    return db->Put(wo, key, value).ok();
}

bool RocksDBAdapter::Get(const std::string &key, std::string &value) {
    rocksdb::ReadOptions ro;
    return db->Get(ro, key, &value).ok();
}
