#include "runtime.h"

namespace runtime {

    void Runtime::init() {
        /*     0 */ impls.emplace(ops[NOP],    std::make_unique<NekoOpNop>(ops[NOP], ops));
        /*     1 */ impls.emplace(ops[POP],    std::make_unique<NekoOpPop>(ops[POP], ops));
        /*     2 */ impls.emplace(ops[POP_N],  std::make_unique<NekoOpPop>(ops[POP_N], ops));

        /*     3 */ impls.emplace(ops[DUP],    std::make_unique<NekoOpDup>(ops[DUP], ops));
        /*     4 */ impls.emplace(ops[DUP_2],  std::make_unique<NekoOpDup>(ops[DUP_2], ops));
        /*     5 */ impls.emplace(ops[DUP_3],  std::make_unique<NekoOpDup>(ops[DUP_3], ops));
        /*     6 */ impls.emplace(ops[DUP_N],  std::make_unique<NekoOpDup>(ops[DUP_N], ops));
        /*     7 */ impls.emplace(ops[DUP_ALL], std::make_unique<NekoOpDup>(ops[DUP_ALL], ops));

        /*     8 */ impls.emplace(ops[NDUP],    std::make_unique<NekoOpDup>(ops[NDUP], ops));
        /*     9 */ impls.emplace(ops[NDUP_2],  std::make_unique<NekoOpDup>(ops[NDUP_2], ops));
        /*    10 */ impls.emplace(ops[NDUP_3],  std::make_unique<NekoOpDup>(ops[NDUP_3], ops));
        /*    11 */ impls.emplace(ops[NDUP_N],  std::make_unique<NekoOpDup>(ops[NDUP_N], ops));
        /*    12 */ impls.emplace(ops[NDUP_ALL], std::make_unique<NekoOpDup>(ops[NDUP_ALL], ops));

        /*    20 */ impls.emplace(ops[CS],       std::make_unique<NekoOpCs>(ops[CS], ops));

        /*  1000 */ impls.emplace(ops[LABEL],    std::make_unique<NekoOpLabel>(ops[LABEL], ops));
        /*  1001 */ impls.emplace(ops[RETURN],   std::make_unique<NekoOpReturn>(ops[RETURN], ops));
//        /*  1002 */ impls.emplace(ops[JUMP],     std::make_unique<NekoOpJump>(ops[JUMP], ops));

//        /*  2000 */ impls.emplace(ops[CREATE],     std::make_unique<NekoOpCreate>(ops[CREATE], ops));
//        /*  2001 */ impls.emplace(ops[TYPE],     std::make_unique<NekoOpType>(ops[TYPE], ops));
//        /*  2002 */ impls.emplace(ops[CALL],     std::make_unique<NekoOpCall>(ops[CALL], ops));

        /*  3000 */ impls.emplace(ops[NUMBER], std::make_unique<NekoOpNumber>(ops[NUMBER], ops));
        /*  3001 */ impls.emplace(ops[STRING], std::make_unique<NekoOpString>(ops[STRING], ops));
        /*  3002 */ impls.emplace(ops[BOOL], std::make_unique<NekoOpBool>(ops[BOOL], ops));

        /*  4000 */ impls.emplace(ops[CONCAT], std::make_unique<NekoOpConcat>(ops[CONCAT], ops));
        /*  4001 */ impls.emplace(ops[CONCAT_N], std::make_unique<NekoOpConcat>(ops[CONCAT_N], ops));
        /*  4002 */ impls.emplace(ops[CONCAT_ALL], std::make_unique<NekoOpConcat>(ops[CONCAT_ALL], ops));

//        /*  5000 */ impls.emplace(ops[REPEAT], std::make_unique<NekoOpRepeat>(ops[REPEAT], ops));
//        /*  5001 */ impls.emplace(ops[REPEAT_N], std::make_unique<NekoOpRepeat>(ops[REPEAT_N], ops));
//        /*  5002 */ impls.emplace(ops[REPEAT_LL], std::make_unique<NekoOpRepeat>(ops[REPEAT_LL], ops));
//        /*  5003 */ impls.emplace(ops[REPEAT_LL_N], std::make_unique<NekoOpRepeat>(ops[REPEAT_LL_N], ops));

//        /*  5004 */ impls.emplace(ops[NREPEAT], std::make_unique<NekoOpRepeat>(ops[NREPEAT], ops));
//        /*  5005 */ impls.emplace(ops[NREPEAT_N], std::make_unique<NekoOpRepeat>(ops[NREPEAT_N], ops));

        /* 10000 */ impls.emplace(ops[OUT], std::make_unique<NekoOpOut>(ops[OUT], ops));
        /* 10001 */ impls.emplace(ops[OUT_ALL], std::make_unique<NekoOpOut>(ops[OUT_ALL], ops));
        /* 10010 */ impls.emplace(ops[ERR], std::make_unique<NekoOpOut>(ops[ERR], ops));
        /* 10011 */ impls.emplace(ops[ERR_ALL], std::make_unique<NekoOpOut>(ops[ERR_ALL], ops));
    }

} // runtime