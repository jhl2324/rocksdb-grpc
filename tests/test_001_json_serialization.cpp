#include <iostream>

#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <utility>

#include <cassert>

class Student {
public:
    int studentId;
    std::string name;

    Student(int studentId, std::string name) {
        this->studentId = studentId;
        this->name = std::move(name);
    }

    explicit Student(const bsoncxx::document::view &view) {
        this->studentId = view["studentId"].get_int32();
        this->name = view["name"].get_string().value.data();
    }

    [[nodiscard]] bsoncxx::document::value to_document() const {
        using bsoncxx::builder::stream::document;
        using bsoncxx::builder::stream::finalize;

        return document{}
                << "studentId" << studentId
                << "name" << name
                << finalize;
    };

    [[nodiscard]] std::string to_json() const {
        return bsoncxx::to_json(to_document());
    }

    bool operator ==(const Student &a) const {
        return a.studentId == this->studentId
            && a.name == this->name;
    }
};

int test_001_json_serialization(int argc, char *argv[]) {
    auto student = Student(202020779, "Eunhak Lee");
    std::string a = student.to_json();
    assert(a == std::string(R"({ "studentId" : 202020779, "name" : "Eunhak Lee" })") && "serialization mismatched");

    Student created = Student(bsoncxx::from_json(a));
    assert((student == created) && "deserialization mismatched");

    return 0;
}
