#include "opcodes.h"

namespace ops {

    Opcodes::Opcodes() {
        /* Default opcode setup */
        for (const auto n: {
                NOP,

                POP, POP_N,

                DUP, DUP_2, DUP_3, DUP_N, DUP_ALL,
                NDUP, NDUP_2, NDUP_3, NDUP_N, NDUP_ALL,

                CS,

                LABEL, RETURN, JUMP,

                CREATE, TYPE, CALL,

                NUMBER, STRING, CONCAT, CONCAT_N, CONCAT_ALL,

                REPEAT, REPEAT_N, REPEAT_LL, REPEAT_LL_N,
                NREPEAT, NREPEAT_N,

                OUT, OUT_ALL,
                ERR, ERR_ALL
        }) ops.insert(std::make_pair(n, n));
    }

    [[maybe_unused]]
    Opcodes::Opcodes(int key) {
        /* Key-based opcode setup */
        for (const auto n: {
                NOP,

                POP, POP_N,

                DUP, DUP_2, DUP_3, DUP_N, DUP_ALL,
                NDUP, NDUP_2, NDUP_3, NDUP_N, NDUP_ALL,

                CS,

                LABEL, RETURN, JUMP,

                CREATE, TYPE, CALL,

                NUMBER, STRING, CONCAT, CONCAT_N, CONCAT_ALL,

                REPEAT, REPEAT_N, REPEAT_LL, REPEAT_LL_N,
                NREPEAT, NREPEAT_N,

                OUT, OUT_ALL,
                ERR, ERR_ALL
        }) ops.insert(std::make_pair(n, n ^ key));
    }

}