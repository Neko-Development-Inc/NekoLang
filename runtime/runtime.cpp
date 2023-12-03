#include "runtime.h"

namespace runtime {

    void Runtime::init() {
        // NOP                       = 0 - do nothing
        impls.emplace(ops[NOP],    std::make_unique<NekoOpNop>());



        // POP                       = 1 - pop last element from Stack
        impls.emplace(ops[POP],    std::make_unique<NekoOpPop>());

        // POP_N                     = 2 - pop last N elements from Stack
        //   <n>                         Number
        impls.emplace(ops[POP_N],  std::make_unique<NekoOpPop>());



        // DUP                       = 3 - duplicate the last element on the Stack
        impls.emplace(ops[DUP],    std::make_unique<NekoOpDup>());

        //  DUP_2                    = 4 - duplicate the last 2 elements on the Stack
        impls.emplace(ops[DUP_2],  std::make_unique<NekoOpDup>());

        //  DUP_3                    = 5 - duplicate the last 3 elements on the Stack
        impls.emplace(ops[DUP_3],  std::make_unique<NekoOpDup>());

        //  DUP_N                    = 6 - pop last N elements from Stack
        //    <n>                        Number
        impls.emplace(ops[POP_N],  std::make_unique<NekoOpPop>());



        //  CS                       = 7 - clear the stack
        impls.emplace(ops[CS],     std::make_unique<NekoOpDup>());



        //  NUMBER                   = 3000 - add Number to the Stack
        //    <n>                           Number
        impls.emplace(ops[NUMBER], std::make_unique<NekoOpNumber>());

        //  STRING                   = 3001 - add String to the Stack
        //    <str>                         String
        impls.emplace(ops[STRING], std::make_unique<NekoOpString>());

        //  CONCAT                   = 3002 - concatenates the last two elements
        //                                    on the Stack, and puts the Result
        //                                    back on the Stack
        impls.emplace(ops[CONCAT], std::make_unique<NekoOpConcat>());

        //  CONCAT_N                 = 3003 - concatenates the last N elements
        //                                    on the Stack, and puts the Result
        //                                    back on the Stack
        //    <n>                           Number
        impls.emplace(ops[CONCAT_N], std::make_unique<NekoOpConcat>());



        //  RETURN                   = 1001 - return from function
        impls.emplace(ops[RETURN], std::make_unique<NekoOpReturn>());



        //  OUT                      = 5000 - return from functionprints the last value on the Stack to
        //                                    the active output stream (stdout by default)
        impls.emplace(ops[OUT], std::make_unique<NekoOpOut>());
    }

} // runtime