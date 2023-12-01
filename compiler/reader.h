#pragma once

#ifndef READER_H
#define READER_H

#include "../headers.h"

namespace compiler {

enum MappingType {
    CODE = 0,
    COMMENT = 1,
    STRING1 = 2,
    STRING2 = 3,
    STRING3 = 4
};

enum What {
    BOX          = 0,  // Found box text
    FUN          = 1,  // Found function text
    VAR          = 2,  // Found variable text
    FOR_LOOP     = 3,  // Found for-loop text
    WHILE_LOOP   = 4,  // Found while-loop text
    IF_CHECK     = 5,  // Found if-check text
    CODE_BLOCK   = 6,  // Found code block text
    EX_MARK      = 7,  // Found !
    CAT_FLAP     = 8,  // Found cat-flap
    SCAWY_SPOOPY = 9,  // Found SCAWY or SPOOPY

    END          = 98, // End of reader
    UNKNOWN      = 99  // Unknown result
};

struct WhatMap {
public:
    inline static const std::unordered_map<What, const char*> map = {
        {BOX, "Box"},
        {FUN, "Fun"},
        {VAR, "Var"},
        {FOR_LOOP, "ForLoop"},
        {WHILE_LOOP, "WhileLoop"},
        {IF_CHECK, "IfCheck"},
        {CODE_BLOCK, "CodeBlock"},
        {EX_MARK, "ExMark"},
        {CAT_FLAP, "CatFlap"},
        {SCAWY_SPOOPY, "ScawySpoopy"},
        {END, "End"},
        {UNKNOWN, "Unknown"}
    };
    inline static const char* whatName(What& what) {
        return WhatMap::map.at(what);
    }
};

struct WhatResult {
    What what;
    int start, end, len;
};

struct Ret1 { char p, c, n; };
struct Ret2 { char p2, p, c, n, n2; };
struct Ret3 { char p3, p2, p, c, n, n2, n3; };
struct Ret4 { char p4, p3, p2, p, c, n, n2, n3, n4; };
struct Ret5 { char p5, p4, p3, p2, p, c, n, n2, n3, n4, n5; };

class Reader {
private:

public:
    std::string str;
    long int index = 0;
    long int end = 0;
    std::vector<int> mappings;

    explicit Reader(const string& s) :
        Reader(s, true, true, true) { }

    explicit Reader(const string& s, bool doRemoveComments, bool doTrimStart, bool doTrimEnd) {
        str = s;
        end = str.length() - 1;
        if (doRemoveComments)
            removeComments();
        mappings.resize(end+1);
        mapString();
        if (doTrimStart)
            trimStart();
        if (doTrimEnd)
            trimEnd();
    }

    char peekPrev();
    char peekPrev(int);
    char curr();
    char peekNext();
    char peekNext(int);
    bool hasMore() const;

    any charN(int);
    string stringN(int);
    int search(const string &);
    int search(const string &, const string &);

    bool isCode() const;
    bool isCode(int) const;
    bool isComment() const;
    bool isComment(int) const;
    bool isString() const;
    bool isString(int) const;
    bool isAlphanumeric();
    bool isAlphanumeric(int);

    void move(long int);
    void move(long int, bool, bool);
    void set(long int);
    void set(long int, bool, bool);

    string currentString();
    void removeComments();
    void mapString();

    static char getClosingChar(char);
    string getRange(int, int) const;
    std::tuple<int, int, int> findRange(char) const;
    char findFirstOpening();
    void trimStart();
    void trimEnd();
    static bool isWhiteSpace(char);

    WhatResult whatIsNext(int&);

};
}

#endif //READER_H