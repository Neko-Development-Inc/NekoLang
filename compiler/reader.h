#pragma once
#ifndef READER_H
#define READER_H

#include <string>
#include <utility>

using std::string;

namespace compiler {
class Reader {
private:
    string str;

public:
    long int index = 0;
    long int end = 0;

    explicit Reader(string s) :
        str(std::move(s)) {
        end = str.length() - 1;
    }

    char peekPrev();
    char curr();
    char peekNext();
    [[nodiscard]] bool hasMore() const;

    void move(long int dir);
    constexpr void set(long int i);

    void removeComments();

};
}

#endif //READER_H