#pragma once

#ifndef OPCODES_H
#define OPCODES_H

#include <map>

const short
       NOP     = 0

     , POP     = 1
     , POP_N   = 2

     , DUP     = 3
     , DUP_2   = 4
     , DUP_3   = 5
     , DUP_N   = 6
     , DUP_ALL = 7

     , NDUP     = 8
     , NDUP_2   = 9
     , NDUP_3   = 10
     , NDUP_N   = 11
     , NDUP_ALL = 12

     , CS      = 20

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

     , NREPEAT = 4004
     , NREPEAT_N = 4005

     , OUT = 5000
     , OUT_ALL = 5001
     , ERR = 5002
     , ERR_ALL = 5003
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