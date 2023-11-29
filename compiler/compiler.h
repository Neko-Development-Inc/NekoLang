#pragma once

#ifndef COMPILER_H
#define COMPILER_H

#include "../headers.h"
#include "reader.h"

namespace compiler {
class Compiler {

private:
    const ops::Opcodes& ops;
    //std::map<string, struct> structs; // TODO: Add resulting classes(fields/functions) to this map

public:
    explicit Compiler(const ops::Opcodes& ops) :
            ops(ops) { }

    void parseFile(string);
    void parse(Reader &reader);

    void parseBoxHeader(Reader&);
    void parseBoxBody(Reader&);

    void parseVarHeader(Reader&);
    void parseVarBody(Reader&);

    void parseFunHeader(Reader&);
    void parseFunBody(Reader&);
};
} // compiler

#endif //COMPILER_H