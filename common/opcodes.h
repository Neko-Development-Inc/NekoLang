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

     , CS       = 20

     , LABEL     = 1000
     , RETURN    = 1001
     , JUMP      = 1002

     , CREATE    = 2000
     , TYPE      = 2001
     , CALL      = 2002

     , NUMBER     = 3000
     , STRING     = 3001
     , BOOL       = 3002

     , CONCAT     = 4000
     , CONCAT_N   = 4001
     , CONCAT_ALL = 4002

     , REPEAT      = 5000
     , REPEAT_N    = 5001
     , REPEAT_LL   = 5002
     , REPEAT_LL_N = 5003

     , NREPEAT     = 5004
     , NREPEAT_N   = 5005

     , OUT       = 10000
     , OUT_ALL   = 10001
     , ERR       = 10002
     , ERR_ALL   = 10003
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