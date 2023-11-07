#include "opcodes.h"

namespace opcodes {

    Opcodes::Opcodes() {
        /* Default opcode setup */
        for (const auto n: {
                NOP, POP, POP_N, CS,
                LABEL, RETURN, JUMP,
                CREATE, TYPE, CALL,
                NUMBER, STRING, CONCAT,
                REPEAT, REPEAT_N, REPEAT_LL, REPEAT_LL_N,
                OUT, ERR
        }) ops.insert(make_pair(n, n));
    }

    [[maybe_unused]]
    Opcodes::Opcodes(int key) {
        /* Key-based opcode setup */
        for (const auto n: {
                NOP, POP, POP_N, CS,
                LABEL, RETURN, JUMP,
                CREATE, TYPE, CALL,
                NUMBER, STRING, CONCAT,
                REPEAT, REPEAT_N, REPEAT_LL, REPEAT_LL_N,
                OUT, ERR
        }) ops.insert(make_pair(n, n ^ key));
    }

}