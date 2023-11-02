#include "runtime.h"

namespace runtime {

    void Runtime::test() {
        println("Hello world from Runtime");
        auto a = opcodes[RETURN];
    }

} // runtime