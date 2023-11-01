#include "utils/utils.h"

#include "compiler/compiler.h"
#include "runtime/runtime.h"

using namespace compiler;
using namespace runtime;

int main() {

    Compiler c;
    println(c.test1());
    println(c.test2());
    println(c.test3());

    Runtime r;
    println(r.test1());
    println(r.test2());
    println(r.test3());

    return 0;
}

/**
* .cat - source file
* .neko - compiled file
*
* !catflap - entrypoint
* !cat-flap - entrypoint
*
* use x - includes x.cat
* use x as y - includes x.cat as reference y
*
* box - class
* var - field
* fun - function
*/