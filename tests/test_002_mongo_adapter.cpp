#include <iostream>

#include "wise/mongo-adapter.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <cassert>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;


int test_002_mongo_adapter(int argc, char *argv[]) {
    wise::adapter::mongo adapter;
    adapter.host = "127.0.0.1";
    adapter.port = 27017;
    adapter.dbname = "";

    adapter.initialize();
    auto entry = adapter.acquire();
    auto db = entry["wise"];
    auto collection = db["logs"];

    int64_t doc_count1 = collection.count_documents({});
    std::cout << "You have " << doc_count1 << " documents in wise.logs\n";

    bsoncxx::types::b_oid documentId;

    {
        auto doc = document{}
                << "name" << "Eunhak Lee"
                << "studentId" << 202020779
                << finalize;
        std::cout << "Inserting " << bsoncxx::to_json(doc) << '\n';
        auto result = collection.insert_one((bsoncxx::document::view_or_value) doc);
        std::cout << "Result is " << (bool) result << '\n';
        assert((bool) result);
        assert(!result.value().inserted_id().get_oid().value.to_string().empty());

        if (result) {
            documentId = result->inserted_id().get_oid();
            std::cout << "- doc id: " << documentId.value.to_string() << '\n';
        }
    }


    int64_t doc_count2 = collection.count_documents({});
    std::cout << "You have " << doc_count2 << " documents in wise.logs\n";
    assert(doc_count1 + 1 == doc_count2);

    if (!documentId.value.to_string().empty()) {
        auto filter = make_document(kvp("_id", documentId));
        std::cout << "Deleting doc: " << documentId.value.to_string() << '\n';

        auto result = collection.delete_one((bsoncxx::document::view_or_value) filter);
        std::cout << "Result is " << (bool) result << '\n';
        assert(result);

        if (result) {
            std::cout << "Deleted " << result->deleted_count() << " documents\n";
        }
    }

    {
        std::cout << "Bulk delete\n";
        auto result = collection.delete_many({});
        std::cout << "Result is " << (bool) result << '\n';
        assert(result);

        if (result) {
            std::cout << "Deleted " << result->deleted_count() << " documents\n";
        }
    }

    return 0;

}
