#include "runtime.h"
#include "ops/NekoOpNop.cpp"

namespace runtime {

    void Runtime::test() {
        NekoOpNop nop;
        nop.execute(*this);
    }

    void Runtime::testPrint() {
        println("Hello from Runtime#testPrint");
    }

} // runtime