#include "runtime.h"

namespace runtime {

    void Runtime::init() {
        /*     0 */ impls.emplace(ops[NOP],    std::make_unique<NekoOpNop>(ops[NOP]));
        /*     1 */ impls.emplace(ops[POP],    std::make_unique<NekoOpPop>(ops[POP]));
        /*     2 */ impls.emplace(ops[POP_N],  std::make_unique<NekoOpPop>(ops[POP_N]));

        /*     3 */ impls.emplace(ops[DUP],    std::make_unique<NekoOpDup>(ops[DUP]));
        /*     4 */ impls.emplace(ops[DUP_2],  std::make_unique<NekoOpDup>(ops[DUP_2]));
        /*     5 */ impls.emplace(ops[DUP_3],  std::make_unique<NekoOpDup>(ops[DUP_3]));
        /*     6 */ impls.emplace(ops[DUP_N],  std::make_unique<NekoOpDup>(ops[DUP_N]));
        /*     7 */ impls.emplace(ops[DUP_ALL], std::make_unique<NekoOpDup>(ops[DUP_ALL]));

        /*     8 */ impls.emplace(ops[NDUP],    std::make_unique<NekoOpDup>(ops[NDUP]));
        /*     9 */ impls.emplace(ops[NDUP_2],  std::make_unique<NekoOpDup>(ops[NDUP_2]));
        /*    10 */ impls.emplace(ops[NDUP_3],  std::make_unique<NekoOpDup>(ops[NDUP_3]));
        /*    11 */ impls.emplace(ops[NDUP_N],  std::make_unique<NekoOpDup>(ops[NDUP_N]));
        /*    12 */ impls.emplace(ops[NDUP_ALL], std::make_unique<NekoOpDup>(ops[NDUP_ALL]));

        /*    20 */ impls.emplace(ops[CS],       std::make_unique<NekoOpCs>(ops[CS]));

        /*  1000 */ impls.emplace(ops[LABEL],    std::make_unique<NekoOpLabel>(ops[LABEL]));
        /*  1001 */ impls.emplace(ops[RETURN],   std::make_unique<NekoOpReturn>(ops[RETURN]));
//        /*  1002 */ impls.emplace(ops[JUMP],     std::make_unique<NekoOpJump>(ops[JUMP]));

//        /*  2000 */ impls.emplace(ops[CREATE],     std::make_unique<NekoOpCreate>(ops[CREATE]));
//        /*  2001 */ impls.emplace(ops[TYPE],     std::make_unique<NekoOpType>(ops[TYPE]));
//        /*  2002 */ impls.emplace(ops[CALL],     std::make_unique<NekoOpCall>(ops[CALL]));

        /*  3000 */ impls.emplace(ops[NUMBER], std::make_unique<NekoOpNumber>(ops[NUMBER]));
        /*  3001 */ impls.emplace(ops[STRING], std::make_unique<NekoOpString>(ops[STRING]));
        /*  3002 */ impls.emplace(ops[BOOL], std::make_unique<NekoOpBool>(ops[BOOL]));

        /*  4000 */ impls.emplace(ops[CONCAT], std::make_unique<NekoOpConcat>(ops[CONCAT]));
        /*  4001 */ impls.emplace(ops[CONCAT_N], std::make_unique<NekoOpConcat>(ops[CONCAT_N]));
        /*  4002 */ impls.emplace(ops[CONCAT_ALL], std::make_unique<NekoOpConcat>(ops[CONCAT_ALL]));

//        /*  5000 */ impls.emplace(ops[REPEAT], std::make_unique<NekoOpRepeat>(ops[REPEAT]));
//        /*  5001 */ impls.emplace(ops[REPEAT_N], std::make_unique<NekoOpRepeat>(ops[REPEAT_N]));
//        /*  5002 */ impls.emplace(ops[REPEAT_LL], std::make_unique<NekoOpRepeat>(ops[REPEAT_LL]));
//        /*  5003 */ impls.emplace(ops[REPEAT_LL_N], std::make_unique<NekoOpRepeat>(ops[REPEAT_LL_N]));

//        /*  5004 */ impls.emplace(ops[NREPEAT], std::make_unique<NekoOpRepeat>(ops[NREPEAT]));
//        /*  5005 */ impls.emplace(ops[NREPEAT_N], std::make_unique<NekoOpRepeat>(ops[NREPEAT_N]));

        /* 10000 */ impls.emplace(ops[OUT], std::make_unique<NekoOpOut>(ops[OUT]));
        /* 10001 */ impls.emplace(ops[OUT_ALL], std::make_unique<NekoOpOut>(ops[OUT_ALL]));
        /* 10010 */ impls.emplace(ops[ERR], std::make_unique<NekoOpOut>(ops[ERR]));
        /* 10011 */ impls.emplace(ops[ERR_ALL], std::make_unique<NekoOpOut>(ops[ERR_ALL]));
    }

} // runtime