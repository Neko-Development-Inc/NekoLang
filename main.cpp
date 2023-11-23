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
//    println(string("NOP: ").append(to_string(o[NOP])));
//    println(string("RETURN: ").append(to_string(o[RETURN])));

//#define COMPILE
#define RUNTIME
//#define STACK

#ifdef COMPILE

    Compiler c(o);
    c.test();

#endif

#ifdef RUNTIME

    // Set up runtime env
    Runtime r(o);
    r.init();

    // Create class
    NekoClass clz("default");

    // Create fun main
    NekoFunction fun("main", clz, o);
    // Initialize fun main
    fun.init(&r);

    // Add fun main to default class
    clz.addFunction(fun);

    // Execute fun main
    fun.execute(&r);

#endif

#if STACK

    NekoStack stack;
    stack.add(std::make_unique<types::NekoNumber>(9223372036854775807L - 1L),
            types::NUMBER);
    stack.add(std::make_unique<types::NekoString>("Hello world"),
            types::STRING);

    int count = stack.count();
    println("Count: ", count);

    auto str = *stack.popString();
    println("String: ", str);

    auto num = *stack.popNumber();
    println("Number: ", num, ", isSame: ", num == (9223372036854775807L - 1L));

#endif

    return 0;
}

/**
* NekoLang
* .cat - source file
* .neko - compiled file
*
* :3 catflap  - entrypoint
* :3 cat-flap - entrypoint
*
* pls x - includes x.cat
* pls x as y - includes x.cat as reference y
*
* box - class
* owo --v
* var - variable
* uwu --^
* fun - function
*
* // comment
* \/\* comment \*\/
*
* box syntax:
* < box Name >.<
*   // code here
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
*  NOP          = 0 - do nothing
*  POP          = 1 - pop last element from Stack
*  POP_N        = 2 - pop last N elements from Stack
*                     N is the last Number on the Stack
*  DUP          = 3 - duplicate the last element on the Stack
*  DUP_2        = 4 - duplicate the last 2 elements on the Stack
*  DUP_3        = 5 - duplicate the last 3 elements on the Stack
*  DUP_N        = 6 - duplicate the last M elements on the Stack
*                   - N is the last Number on the Stack
*  CS           = 7 - clear the stack
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
*                        puts the Result back on the Stack
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
*  // Json example:
*  owo json <{
*      testKey: 'test value'
*  }>
*  print(json.testKey) // prints 'test value'
*  json.testKey <'OwO'>
*  print(json.testKey) // prints 'OwO'
*
*  // math example:
*  owo a < 3 >         // 3
*  var b < a + 1 >     // 4
*  uwu c < a++ >       // 3 - assigns value 'a' THEN increments afterwards
*  var d < ++a >       // 4 - increments first THEN assigns value 'a'
*  owo e < a++ + a >   // 3 + 3 - assigns value 'a' + 'a' = 6, THEN increments afterwards
*  var f < a++ + ++a > // 3 + 4 - assigns value 'a' + 'a=a+1' = 7
*
*  booleans:
*  fact - true
*  fake - false
*  idfk - maybe
*
*  if < expression is fact >.<
*      println("noice")
*  >
*  if < expression is fake >.<
*      println("oops")
*  >
*
*  if/else-if/else:
*  if < expression >.<
*      // If here
*  > uhm < expression >.<
*      // Else-if here
*  > oh <
*      // Else here
*  >
*
*/