#pragma once
#ifndef READER_H
#define READER_H

#include <any>
#include <string>
#include <utility>
#include <variant>

using std::any, std::string, std::variant;

namespace compiler {

enum MappingType {
    CODE = 0,
    COMMENT = 1,
    STRING1 = 2,
    STRING2 = 3,
    STRING3 = 4
};

struct Ret1 { char p, c, n; };
struct Ret2 { char p2, p, c, n, n2; };
struct Ret3 { char p3, p2, p, c, n, n2, n3; };
struct Ret4 { char p4, p3, p2, p, c, n, n2, n3, n4; };
struct Ret5 { char p5, p4, p3, p2, p, c, n, n2, n3, n4, n5; };

class Reader {
private:

public:
    string str;
    long int index = 0;
    long int end = 0;
    int* mappings;

    explicit Reader(const string& s) :
        Reader(s, true, true) { }

    explicit Reader(const string& s, bool doRemoveComments, bool doSkipWhitespace) {
        str = s;
        end = str.length() - 1;
        if (doRemoveComments)
            removeComments();
        mappings = new int[str.length()];
        mapString();
        if (doSkipWhitespace)
            skipWhitespace();
    }

    char peekPrev();
    char peekPrev(int n);
    char curr();
    char peekNext();
    char peekNext(int n);
    _GLIBCXX_NODISCARD bool hasMore() const;

    any charN(int n);

    _GLIBCXX_NODISCARD bool isCode() const;
    _GLIBCXX_NODISCARD bool isComment() const;
    _GLIBCXX_NODISCARD bool isString() const;

    void move(long int dir);
    constexpr void set(long int i);

    string currentString();

    void removeComments();
    void removeComments(bool doMapping);

    void mapString();

    static char getClosingChar(char opening);
    _GLIBCXX_NODISCARD std::tuple<int, int, int> findRange(char opening) const;
    char findFirstOpening();
    void skipWhitespace();
    static bool isWhiteSpace(char c);

};
}

#endif //READER_H