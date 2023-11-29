#pragma once

#ifndef COMPILER_H
#define COMPILER_H

#include "../headers.h"
#include "reader.h"

namespace compiler {
class Compiler {

private:
    const ops::Opcodes& ops;

public:
    explicit Compiler(const ops::Opcodes& ops) :
            ops(reinterpret_cast<const Opcodes &>(ops)) { }

    void parseFile(string);
    void doParseFile(string&);

};
} // compiler

#endif //COMPILER_H