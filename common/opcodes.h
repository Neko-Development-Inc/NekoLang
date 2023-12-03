#pragma once

#ifndef OPCODES_H
#define OPCODES_H

#include <map>

const short
       NOP   = 0
     , POP   = 1
     , POP_N = 2
     , DUP   = 3
     , DUP_2 = 4
     , DUP_3 = 5
     , DUP_N = 6
     , CS    = 7

     , LABEL  = 1000
     , RETURN = 1001
     , JUMP   = 1002

     , CREATE = 2000
     , TYPE   = 2001
     , CALL   = 2002

     , NUMBER     = 3000
     , STRING     = 3001
     , CONCAT     = 3002
     , CONCAT_N   = 3003
     , CONCAT_ALL = 3004

     , REPEAT      = 4000
     , REPEAT_N    = 4001
     , REPEAT_LL   = 4002
     , REPEAT_LL_N = 4003

     , OUT = 5000
     , ERR = 5001
;

namespace ops {
class Opcodes {

protected:
    std::map<short, short> ops;

public:

    Opcodes();

    [[maybe_unused]] explicit Opcodes(int key);

    short& operator[](short index) {
        return ops[index];
    }

};
}

#endif //OPCODES_H