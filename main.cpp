#include "utils/utils.h"

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "common/opcodes.h"

using namespace compiler;
using namespace runtime;
using namespace opcodes;

int main() {

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
*  number = N - int, or decimal
*  string = S - character array
*  bool   = B - true/false
*  box type = <TypeNameHere> - any box type
*
* Opcodes:
*
*  NOP          = 0 - do nothing
*  POP          = 1 - pop last element from Stack
*  POP_N        = 2 - pop last N elements from Stack
*                     N is the last Number on the Stack
*  CS           = 3 - clear the stack
*
*  LABEL<id>    = 100 - label, a specific point in an instruction-set
*  RETURN       = 101 - return from function
*  JUMP<lbl>    = 102 - jump to label instruction
*
*  CREATE<type> = 200 - create new box
*  TYPE<type>   = 201 - set box type
*
*  NUMBER<num>  = 300 - add Number to the Stack
*  STRING<str>  = 301 - add String to the Stack
*  CONCAT       = 302 - concatenates the last two elements on the Stack, and
*                       puts the result back on the Stack
*
*  REPEAT       = 400 - repeat the last instruction once
*  REPEAT_N     = 401 - repeat the last instruction N times
*                       N is the last Number on the Stack
*  REPEAT_LL    = 402 - repeats the instructions between two Labels
*                     - L stands for Label
*                       uses the indexes from the last two Numbers on the Stack
*  REPEAT_LL_N  = 403 - repeats the instructions between two Labels N times
*                     - L stands for Label
*                       uses the label indexes from the last two Numbers on the Stack
*                     - N is the last Number on the Stack, after the two indexes above
*
*  OUT          = 500 - prints the last value on the Stack to
*                       the active output stream (stdout by default)
*  ERR          = 501 - prints the last value on the Stack to
*                       the active error output stream (stderr by default)
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
*  var start = 0;
*  var end = 10;
*  var isIncl = true;
*  for times <start to end isIncl>.<
*      println('Hello ' + 69);
*  >
*
*/