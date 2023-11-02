#pragma once
#ifndef OPCODES_H
#define OPCODES_H

#include <string>
#include <map>

using namespace std;

const int
      NOP = 0
     ,RETURN = 1
;

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

};
}

#endif //OPCODES_H