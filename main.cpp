#define COMPILE
//#define RUNTIME
//#define STACK

#include "headers.h"
#include "common/opcodes.h"

#ifdef COMPILE
#include "compiler/compiler.h"
#endif

#ifdef RUNTIME
#include "runtime/runtime.h"
#endif

#ifdef STACK
#include "runtime/types/NekoObject.h"
#include "runtime/vm/NekoStack.h"
#endif

int main() {

    // Set up all opcodes
    ops::Opcodes o;

#ifdef COMPILE

    Compiler c(o);
    c.parseFile("testing/test.cat");

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
    fun.init(r);

    // Add fun main to default class
    clz.addFunction(fun);

    // Execute fun main
    fun.execute(r);

#endif

#ifdef STACK

    NekoStack _stack;
    _stack.add(std::make_unique<NekoNumber>(9223372036854775807L - 1L),
            T_NUMBER);
    _stack.add(std::make_unique<NekoString>("Hello world"),
            T_STRING);

    int count = _stack.count();
    cout << "Count: " << count << "\n";

    auto str = *_stack.popString();
    cout << "String: " << str << "\n";

    auto num = *_stack.popNumber();
    cout << "Number: " << num << ", isSame: " << (num == (9223372036854775807L - 1L) ? "true" : "false") << "\n";

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
*  CS           = 7 - clear the _stack
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
*  T_NUMBER<num>  = 3000 - add Number to the Stack
*  T_STRING<str>  = 3001 - add String to the Stack
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
*  T_STRING 'Hello '
*  T_NUMBER 69
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
*      testKey: 'parseFile value'
*  }>
*  print(json.testKey) // prints 'parseFile value'
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
*  if < expression is maybe >.<
*      println("wtf?")
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