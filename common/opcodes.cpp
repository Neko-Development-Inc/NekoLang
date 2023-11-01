#include "opcodes.h"

namespace opcodes {

    Opcodes::Opcodes() {
        /* Default opcode setup */
        ops.insert(make_pair(NOP, NOP));
        ops.insert(make_pair(RETURN, RETURN));
    }

    [[maybe_unused]]
    Opcodes::Opcodes(int key) {
        /* Key-based opcode setup */
        ops.insert(make_pair(NOP, NOP ^ key));
        ops.insert(make_pair(RETURN, RETURN ^ key));
    }

}