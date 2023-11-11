#pragma once
#ifndef READER_H
#define READER_H

#include <string>
#include <utility>

using std::string;

namespace compiler {
enum MappingType {
    CODE = 0,
    COMMENT = 1,
    STRING1 = 2,
    STRING2 = 3,
    STRING3 = 4
};
class Reader {
private:

public:
    string str;
    long int index = 0;
    long int end = 0;
    int* mappings;

    explicit Reader(string s) : Reader(std::move(s), true) { }

    explicit Reader(string s, bool doRemoveComments) {
        str = std::move(s);
        end = str.length() - 1;
        if (doRemoveComments)
            removeComments();
        mappings = new int[str.length()];
        mapString();
    }

    char peekPrev();
    char peekPrev(int n);
    char curr();
    char peekNext();
    char peekNext(int n);
    [[nodiscard]] bool hasMore() const;

    void move(long int dir);
    constexpr void set(long int i);

    void removeComments();
    void removeComments(bool doMapping);

    void mapString();

};
}

#endif //READER_H