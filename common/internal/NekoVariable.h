#ifndef NEKOVAR_H
#define NEKOVAR_H

#include "../../headers.h"

class vm::NekoVariable {

public:
    const string name;
    NekoBox& owner;
    Opcodes& ops;

    explicit NekoVariable(const string& name, NekoBox& owner, Opcodes& ops)
        : name(name),
          owner(owner),
          ops(ops) { }

private:

};

#endif //NEKOVAR_H