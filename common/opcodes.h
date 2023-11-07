#pragma once
#ifndef OPCODES_H
#define OPCODES_H

#include <string>
#include <map>

using namespace std;

const short
       NOP   = 0
     , POP   = 1
     , POP_N = 2
     , CS    = 3

     , LABEL  = 100
     , RETURN = 101
     , JUMP   = 102

     , CREATE = 200
     , TYPE   = 201

     , NUMBER = 300
     , STRING = 301
     , CONCAT = 302

     , REPEAT      = 400
     , REPEAT_N    = 401
     , REPEAT_LL   = 402
     , REPEAT_LL_N = 403

     , OUT = 500
     , ERR = 501
;

namespace opcodes {
class Opcodes {

protected:
    map<short, short> ops;

public:

    Opcodes();

    [[maybe_unused]] explicit Opcodes(int key);

    constexpr short& operator[](short index) {
        return ops[index];
    }

};
}

#endif //OPCODES_H