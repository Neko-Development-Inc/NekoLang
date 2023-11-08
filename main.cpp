#include "utils/utils.h"

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "common/opcodes.h"

using namespace compiler;
using namespace runtime;
using namespace opcodes;
using namespace vm;

int main() {

    // Set up all opcodes
    Opcodes o;
    println(string("NOP: ").append(to_string(o[NOP])));
    println(string("RETURN: ").append(to_string(o[RETURN])));

    Compiler c(o);
    c.test();

    // Set up runtime env
    Runtime r(o);
    r.init();

    // Create class
    NekoClass clz("default");

    // Create fun main
    NekoFunction fun("main", clz, o);
    // Initialize fun main
    fun.init(r);

    // Add fun main to default class
    clz.addFunction(fun);

    // Execute fun main
    fun.execute(r);

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
* var - variable
* fun - function
*
* #owo - start of a single/multi-line comment
* uwu# - end of a single-line comment
* #uwu - end of a multi-line comment
*
* box syntax:
* < box Name >.<
*   #owo code here uwu#
* >
*
* Types:
*  object   = O - object, any type
*  number   = N - int, or decimal
*  string   = S - character array
*  bool     = B - true/false
*  box type = <TypeNameHere> - any box type
*  empty    = E - empty type
*  null     = E - alias for the above empty type
*
* Opcodes:
*
*  NOP          = 0 - do nothing
*  POP          = 1 - pop last element from Stack
*  POP_N        = 2 - pop last N elements from Stack
*                     N is the last Number on the Stack
*  CS           = 3 - clear the stack
*
*  LABEL<id>    = 1000 - label, a specific point in an instruction-set
*  RETURN       = 1001 - return from function
*  JUMP<lbl>    = 1002 - jump to label instruction
*
*  CREATE<type> = 2000 - create new box
*  TYPE<type>   = 2001 - set box type
*  CALL<owner>  = 2002 - execute function box #owner
*      <name>            by exact name
*
*  NUMBER<num>  = 3000 - add Number to the Stack
*  STRING<str>  = 3001 - add String to the Stack
*  CONCAT       = 3002 - concatenates the last two elements on the Stack, and
*                        puts the result back on the Stack
*
*  REPEAT       = 4000 - repeat the last instruction once
*  REPEAT_N     = 4001 - repeat the last instruction N times
*                        N is the last Number on the Stack
*  REPEAT_LL    = 4002 - repeats the instructions between two Labels
*                      - L stands for Label
*                        uses the indexes from the last two Numbers on the Stack
*  REPEAT_LL_N  = 4003 - repeats the instructions between two Labels N times
*                      - L stands for Label
*                        uses the label indexes from the last two Numbers on the Stack
*                      - N is the last Number on the Stack, after the two indexes above
*
*  OUT          = 5000 - prints the last value on the Stack to
*                        the active output stream (stdout by default)
*  ERR          = 5001 - prints the last value on the Stack to
*                        the active error output stream (stderr by default)
*
* Example program (with opcodes):
*  JUMP 1
*  LABEL 0
*  STRING 'Hello '
*  NUMBER 69
*  CONCAT
*  OUT
*  LABEL 1
*  REPEAT_LL_N 0 1 10
*
* Example program (using NekoLang):
*  for <from 1 to 10 inclusive as i>.<
*      println('Hello ' + i);
*  >
*  var items < 1, 2, 3 >;
*  for <item in items>.<
*      println(item);
*  >
*
*/