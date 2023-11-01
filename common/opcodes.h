#pragma once
#ifndef OPCODES_H
#define OPCODES_H

#include <string>
#include <map>

using namespace std;

namespace opcodes {
class Opcodes {

protected:
    map<int, int> ops;

public:

    Opcodes();

    [[maybe_unused]] explicit Opcodes(int key);

    int& operator[](int index) {
        return ops[index];
    }

    const int
         NOP = 0
        ,RETURN = 1
    ;

};
}

#endif //OPCODES_H