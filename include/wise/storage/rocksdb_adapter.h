#ifndef WISE_STORAGE_ROCKSDB_ADAPTER_H
#define WISE_STORAGE_ROCKSDB_ADAPTER_H

#include <rocksdb/db.h>
#include <string>

class RocksDBAdapter {
public:
    RocksDBAdapter(const std::string &db_path);
    ~RocksDBAdapter();
    
    bool Put(const std::string &key, const std::string &value);
    bool Get(const std::string &key, std::string &value);

private:
    rocksdb::DB *db;
};

#endif
