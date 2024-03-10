#include "opcodes.h"

namespace ops {

    Opcodes::Opcodes() {
        /* Default opcode setup */
        for (const auto n: {
                NOP,

                POP, POP_N,

                DUP, DUP_2, DUP_3, DUP_N, DUP_ALL,
                NDUP, NDUP_2, NDUP_3, NDUP_N, NDUP_ALL,

                CS, SWAP, NULL,

                LABEL, RETURN, JUMP,

                JUMP_IF_EQ, JUMP_IF_NE, JUMP_IF_GT, JUMP_IF_LT,
                JUMP_IF_GE, JUMP_IF_LE, JUMP_IF_IZ, JUMP_IF_NT,
                JUMP_IF_HD, JUMP_IF_ND, JUMP_IF_NULL, JUMP_IF_NOT_NULL,

                STORE, FETCH, ASTORE, AFETCH, ALEN,

                INC, DEC, AINC, ADEC,
                ADD, SUB, MUL, DIV, MOD, REM, NEG,
                AND, NOT, OR, XOR, SHL, SHR, USHR, CMP, RMD,

                CREATE, ACREATE, TYPE, CALL,
                GET, PUT, THROW, IS_INSTANCE,

                LOCK, UNLOCK,

                NUMBER, STRING, BOOL,

                CONCAT, CONCAT_N, CONCAT_ALL,

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

                CS, SWAP, NULL,

                LABEL, RETURN, JUMP,

                JUMP_IF_EQ, JUMP_IF_NE, JUMP_IF_GT, JUMP_IF_LT,
                JUMP_IF_GE, JUMP_IF_LE, JUMP_IF_IZ, JUMP_IF_NT,
                JUMP_IF_HD, JUMP_IF_ND, JUMP_IF_NULL, JUMP_IF_NOT_NULL,

                STORE, FETCH, ASTORE, AFETCH, ALEN,

                INC, DEC, AINC, ADEC,
                ADD, SUB, MUL, DIV, MOD, REM, NEG,
                AND, NOT, OR, XOR, SHL, SHR, USHR, CMP, RMD,

                CREATE, ACREATE, TYPE, CALL,
                GET, PUT, THROW, IS_INSTANCE,

                LOCK, UNLOCK,

                NUMBER, STRING, BOOL,

                CONCAT, CONCAT_N, CONCAT_ALL,

                REPEAT, REPEAT_N, REPEAT_LL, REPEAT_LL_N,
                NREPEAT, NREPEAT_N,

                OUT, OUT_ALL,
                ERR, ERR_ALL
        }) ops.insert(std::make_pair(n, n ^ key));
    }

}