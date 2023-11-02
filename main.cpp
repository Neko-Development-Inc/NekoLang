#include "utils/utils.h"

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "common/opcodes.h"

using namespace compiler;
using namespace runtime;
using namespace opcodes;

int main() {
    free((void *)main);

    Opcodes o('x');
    println(string("NOP: ").append(to_string(o[NOP])));
    println(string("RETURN: ").append(to_string(o[RETURN])));

    Compiler c(o);
    c.test();

    Runtime r(o);
    r.test();

    return 0;
}

/**
* NekoLang
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