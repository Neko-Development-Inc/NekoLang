#pragma once

#ifndef OPCODES_H
#define OPCODES_H

#include <map>

const short
       NOP     = 0 // do nothing

     , POP     = 1 // pop 1 element
     , POP_N   = 2 // pop N elements

     , DUP     = 3 // duplicate 1 element
     , DUP_2   = 4 // duplicate 2 elements
     , DUP_3   = 5 // duplicate 3 elements
     , DUP_N   = 6 // duplicate N elements
     , DUP_ALL = 7 // duplicate all elements

     , NDUP     = 8 // duplicate 1 element, N times
     , NDUP_2   = 9 // duplicate 2 elements, N times
     , NDUP_3   = 10 // duplicate 3 elements, N times
     , NDUP_N   = 11 // duplicate N elements, N times
     , NDUP_ALL = 12 // duplicate all elements, N times

     , CS       = 20 // clear stack
     , SWAP     = 21 // swap top two elements
     , NULL     = 22 // push null

     , LABEL     = 1000 // label (position in code)
     , RETURN    = 1001 // return from function
     , JUMP      = 1002 // jump to label

     , JUMP_IF_EQ = 1100 // equal
     , JUMP_IF_NE = 1101 // not equal
     , JUMP_IF_GT = 1102 // greater than
     , JUMP_IF_LT = 1103 // less than
     , JUMP_IF_GE = 1104 // greater or equal
     , JUMP_IF_LE = 1105 // less or equal
     , JUMP_IF_IZ = 1106 // is zero
     , JUMP_IF_NT = 1107 // is not zero
     , JUMP_IF_HD = 1108 // has decimal
     , JUMP_IF_ND = 1108 // no decimal
     , JUMP_IF_NULL     = 1109 // is null
     , JUMP_IF_NOT_NULL = 1110 // is not null

     , STORE      = 1200 // local variable store
     , FETCH      = 1201 // local variable fetch
     , ASTORE     = 1202 // lv array store
     , AFETCH     = 1203 // lv array fetch
     , ALEN       = 1204 // get array length

     , INC        = 1300 // increment
     , DEC        = 1301 // decrement
     , AINC       = 1302 // array increment
     , ADEC       = 1303 // array decrement

     , ADD        = 1400 // add
     , SUB        = 1401 // subtract
     , MUL        = 1402 // multiply
     , DIV        = 1403 // divide
     , MOD        = 1404 // modulo
     , REM        = 1405 // remainder
     , NEG        = 1406 // negate
     , AND        = 1407 // and
     , NOT        = 1408 // not
     , OR         = 1409 // inclusive or
     , XOR        = 1410 // exclusive or
     , SHL        = 1411 // shift left
     , SHR        = 1412 // shift right
     , USHR       = 1413 // unsigned shift right
     , CMP        = 1414 // push -1, 0, 1 if the two top values are the same
     , RMD        = 1415 // remove decimal part

     , CREATE      = 2000 // type create
     , ACREATE     = 2001 // array type create
     , TYPE        = 2002 // type casting
     , CALL        = 2003 // call function
     , GET         = 2004 // get field value
     , PUT         = 2005 // put field value
     , THROW       = 2006 // throw exception
     , IS_INSTANCE = 2007 // is instance of

     , LOCK        = 2100 // lock object (for threading)
     , UNLOCK      = 2101 // unlock object (for threading)

     , NUMBER      = 3000 // push number
     , STRING      = 3001 // push string
     , BOOL        = 3002 // push bool

     , CONCAT      = 4000 // concat top two elements
     , CONCAT_N    = 4001 // concat top N elements
     , CONCAT_ALL  = 4002 // concat all elements

     , REPEAT      = 5000 // repeat last instruction
     , REPEAT_N    = 5001 // repeat last N instructions
     , REPEAT_LL   = 5002 // repeat all instructions between labels
     , REPEAT_LL_N = 5003 // repeat all instructions between labels N times

     , NREPEAT     = 5004 // repeat previous/next instruction
     , NREPEAT_N   = 5005 // repeat previous/next N instructions

     , OUT       = 10000 // output top element
     , OUT_ALL   = 10001 // output all elements
     , ERR       = 10002 // output top element to error
     , ERR_ALL   = 10003 // output all elements to error
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