
//#define COMPILE
//#define RUNTIME
#define STACK



#define DEBUG 1

#if DEBUG
    #define TIMER(var, name) Timer var(name);
    #define STOP_TIMER(var) var.Stop();
#else
    #define TIMER(a, b)
    #define STOP_TIMER(a)
#endif



#include "headers.h"
#include "common/opcodes.h"



#ifdef COMPILE
#include "compiler/compiler.h"
#endif



#ifdef RUNTIME
#include "runtime/runtime.h"
#include "runtime/vm/NekoClass.h"
#endif



#ifdef STACK
#include "runtime/vm/NekoStack.h"
#endif



int main() {
TIMER(timer, "main.cpp")

TIMER(timerOpcodes, "opcodes")
    // Set up all opcodes
    Opcodes o;
STOP_TIMER(timerOpcodes)

#ifdef COMPILE
TIMER(timerCompiler, "compiler")

    Compiler c(o);
    c.parseFile("testing/test.cat");

STOP_TIMER(timerCompiler)
#endif

#ifdef RUNTIME
TIMER(timerRuntime, "runtime")

    // Set up runtime env
    Runtime r(o); {
        r.init();
    }

    // Create class
    NekoClass clz("Default"); {
        // Create fun main
        NekoFunction fun("main", clz, o); {
            // Initialize fun main
            fun.init(r);
        }

        // Add fun main to default class
        clz.addFunction(fun);

        // Execute fun main
        fun.execute(r);
    }

STOP_TIMER(timerRuntime)
#endif

#ifdef STACK
TIMER(timerStack, "stack")

    NekoStack _stack;

    _stack.add(
        9223372036854775807L - 1L,
        T_NUMBER
    );
    _stack.add(
        "hello world 2",
        T_STRING
    );
    _stack.add(
        string("hello world 1"),
        T_STRING
    );

    _stack.process();

//    size_t count = _stack.count();
//    println("Count: ", count);
//
//    println("String: ", *_stack.popString());
//    println("String: ", *_stack.popString());
//
//    auto num = *_stack.popNumber();
//    println("Number: ", num, ", isSame: ", (num == (9223372036854775807L - 1L) ? "true" : "false"));

STOP_TIMER(timerStack)
#endif

    return 0;
}

/**
* NekoLang
* .cat - source file
* .neko - compiled file
* .mew - runnable executable (zip file)
* .exe - packed runnable executable (can't be opened as zip)
*
* Commandline stuff:
*  Main command: neko / neko.exe
* Examples:
*  neko -i main.cat -o main.neko             -- compile single file into a binary format
*  neko -i main test utils -o myprogram.mew  -- compile multiple files into a zipped format
*  neko -r myprogram.mew                     -- execute the zipped neko program
* Arguments:
*  -i <file> - Choose one or more input file(s)
*  -r        - Run a program
*
* :3 catflap  - entrypoint
* :3 cat-flap - entrypoint
*
* pls x      - includes x.cat (by copy paste)
* pls x as y - includes x.cat (as reference y)
*
* box  - class
* owo  --v
* var  - variable
* uwu  --^
* fun  - function
* pls  - include
* psps --^
*
* // comment
* \/\* comment \*\/
*
* box syntax:
*   < box Name1 >.<
*     // code here
*   >
*   < box path/here/Name2 >^.^<
*     // code here
*   >
*   < box path/here/Name3 / Name1 >^.^<
*     // code here
*   >
*
* Bytecode types:
*   object   = * - object, any type below
*   number   = N - int or decimal (always 64-bit)
*   string   = S - character array
*   bool     = B - true/false/maybe
*   box-type = <path/name> - any box type
*   array    = A - array of any type
*   empty    = E - empty type
*   null     = E - ^ alias for the above empty type
*
* Types examples:
*   single object: *
*     1d array of objects: A*
*     2d array of objects: AA*
*   single number: N
*     1d array of numbers: AN
*     2d array of numbers: AAN
*   single string: S
*     1d array of strings: AS
*     2d array of strings: AAS
*   single a/b/c/Box1: <a/b/c/Box1>
*     1d array of strings: A<a/b/c/Box1>
*     2d array of strings: AA<a/b/c/Box1>
*   single number, string, bool: NSB
*     1d array of number only: ANSB  -- SB is not an array
*     2d array of number only: AANSB -- SB is not an array
*     1d array of string only: NASB  -- NB is not an array
*     2d array of string only: NAASB -- NB is not an array
*     1d array of bool only:   NSAB  -- NS is not an array
*     2d array of bool only:   NSAAB -- NS is not an array
*
* Opcodes:
*  NOP          = 0 - do nothing
*  POP          = 1 - pop last element from Stack
*  POP_N        = 2 - pop last N elements from Stack
*    <n>            Number
*
*  DUP          = 3  - duplicate the last element on the Stack
*  DUP_2        = 4  - duplicate the last 2 elements on the Stack
*  DUP_3        = 5  - duplicate the last 3 elements on the Stack
*  DUP_N        = 6  - duplicate the last N elements on the Stack
*    <n>             Number
*  DUP_ALL      = 7  - duplicate all the elements on the Stack
*
*  NDUP         = 8  - duplicate the last element on the Stack, N times
*    <n>             Number of times to duplicate
*  NDUP_2       = 9  - duplicate the last 2 elements on the Stack, N times
*    <n>             Number of times to duplicate
*  NDUP_3       = 10 - duplicate the last 3 elements on the Stack, N times
*    <n>             Number of times to duplicate
*  NDUP_N       = 11 - duplicate the last N elements on the Stack, N times
*    <n1>            Number of elements from the stack to duplicate
*    <n2>            Number of times to duplicate
*  NDUP_ALL     = 12 - duplicate all the elements on the Stack, N times
*    <n>             Number of times to duplicate
*
*  CS           = 20 - clear the stack
*
*  LABEL        = 1000 - label, a specific point in an instruction-set
*    <id>              Number
*  RETURN       = 1001 - return from function
*  JUMP         = 1002 - jump to label instruction
*    <lbl id>          Number
*
*  CREATE       = 2000 - create new box
*    <type>            String <path/owner>
*  TYPE         = 2001 - set box type
*    <type>            String <path/owner>
*  CALL         = 2002 - execute function in box <path/owner>
*    <path>            String path (a/b/c)
*    <owner>           String owner (Box1)
*    <name>            String function name (test_function)
*    <argc>            Number -- number of arguments -- optional
*    <sign>            String -- signature of arguments -- optional
*
*  NUMBER       = 3000 - add Number to the Stack
*    <num>             Number
*  STRING       = 3001 - add String to the Stack
*    <str>             String
*  CONCAT       = 3002 - concatenates the last two elements on the Stack, and
*                        puts the Result back on the Stack
*  CONCAT_N     = 3003 - concatenates the last N elements on the Stack, and
*                        puts the Result back on the Stack
*    <n>               Number -- number of elements to concatenate
*  CONCAT_ALL   = 3004 - concatenates all the elements on the Stack, and
*                        puts the Result back on the Stack
*
*  REPEAT       = 4000 - repeat the last instruction once
*  REPEAT_N     = 4001 - repeat the last instruction N times
*    <n>               Number -- number of times to repeat
*  REPEAT_LL    = 4002 - repeats the instructions between two Labels
*                      - L stands for Label
*    <n1>              Number -- index of first Label
*    <n2>              Number -- index of second Label
*  REPEAT_LL_N  = 4003 - repeats the instructions between two Labels N times
*                      - L stands for Label
*    <n1>              Number -- index of first Label
*    <n2>              Number -- index of second Label
*    <n>               Number -- number of times to repeat
*
*  NREPEAT      = 4004 - repeat the last N instructions once
*    <n>               Number of times to duplicate
*  NREPEAT_N    = 4005 - repeat the last N instruction N times
*    <n1>              Number of elements from the stack to repeat
*    <n2>              Number of times to repeat
*
*  OUT          = 5000 - prints the last value on the Stack to
*                        the active output stream (stdout by default)
*    <bool>            Bool -- force flush or not -- optional
*  OUT_ALL      = 5001 - prints all the last values on the Stack to
*                        the active output stream (stdout by default)
*    <bool>            Bool -- force flush or not -- optional
*  ERR          = 5010 - prints the last value on the Stack to
*                        the active error output stream (stderr by default)
*    <bool>            Bool -- force flush or not -- optional
*  ERR_ALL      = 5011 - prints all the last values on the Stack to
*                        the active error output stream (stderr by default)
*    <bool>            Bool -- force flush or not -- optional
*
* Example program 1 (opcodes):
*    JUMP 1
*  LABEL 0
*    STRING 'Hello '
*    NUMBER 420
*    CONCAT
*    STRING ' :)\n'
*    CONCAT
*    OUT true
*  LABEL 1
*    REPEAT_LL_N 0 1 10
*
* Example program 2 (opcodes):
*    JUMP 1
*  LABEL 0
*    STRING 'abc' -- argument 1 (S)
*    NUMBER  123  -- argument 2 (N)
*    CALL    a/b/c    Box1   function_test   2     SN    true
*    --      path    |^      func_name      |^    |^     auto pop call result
*    --              |box_name              |^    |signature (S = String, N = Number)
*    --                                     |argument_count (String, Number)
*  LABEL 1
*    REPEAT_LL_N 0 1 3 -- call a/b/c/Box1.function_test(SN) three times,
*                      -- using 'abc' and 123 as the arguments.
*                      -- automatically pop call result from the stack.
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
*  owo e < a++ + a >   // 3 + 4 - assigns value 'a' + '1+a' = 7
*  var f < a++ + ++a > // 3 + 5 - assigns value 'a' + '1+1+a' = 8
*  var g < ++a + ++a > // 4 + 5 - assigns value '1+a' + '1+a' = 9
*
*  booleans:
*   fact - true
*   fake - false
*   idfk - maybe -- will probably be scrapped as it makes no sense :D
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

/**
*  How NekoLang works (:D)
*
*  1. Say you have these files:
*    a. main.cat
*    b. test.cat
*    c. utils.cat
*
*  2. Inside main.cat, it includes test.cat and utils.cat
*    a. pls test
*    b. pls utils
*
*  3. The compiler will read this, and copy-paste the contents
*      of test.cat and utils.cat into main.cat, at those exact places.
*
*  4. Ways to use boxes from other files:
*    a. You can include the box by using a filepath, using pls,
*        this will copy-paste the contents of it at this very place in the code,
*        unless you do `as X`.
*      - pls f1/f2/CatFileHere  -- assuming CatFileHere.cat (or .neko) is in the folder `f1/f2/`
*      - pls utils              -- assuming utils.cat (or .neko) is in the same folder
*      - pls utils.cat as u     -- ^. This won't copy-paste, but make a reference accessible by 'u'.
*
 *    b. You can access boxes from other files, by using their direct box paths (not filepaths),
*         and you won't need to `pls` them first:
*      - create a/b/c/Box1()
*      - create a.b.c/Box1()
*
*  5. If you write Code/Function directly in a .cat file, without surrounding it with a box:
*    a. Code: It will be put into a box called "Default" automatically.
*             A default box will be created if it doesn't exist.
*    b. Function: It will be put into the "Default" box's functions table.
*                 A default init function will be created if it doesn't exist.
*
*  6. If you have multiple .cat files with code (without a box), it will all
*      be included in the "Default" box automatically, appending itself.
*
*  7. The order of fields and functions in a box is not important.
*    a. Fields and Functions can be in any order, above or below each other.
*    b. The place where you include another file (the pls word), DOES matter.
*
*  8. If you define a function or a box inside a function (or in the root of a file),
*    a. Function: The function will be moved to the current Box (perhaps Default)
*    b. Box: The box will be globally available, just like any other.
*
*/

/**
*  The .neko file binary structure:
*       / =============+===================================================+=========================== \
*       | Num of bytes | Description                                       | Restrictions               |
*       | =============+===================================================+=========================== |
*  #1   | 4            | Magic number (hex for meow)                       | 'meow', not case-sensitive |
*  #2   | 4            | 32 bits of useful metadata (endianness, etc)      | 0x00000000 <-> 0x7fffffff  |
*  #3   | 4            | Major version number                              | 0 <-> 2,147,483,647        |
*  #4   | 4            | Minor version number                              | 0 <-> 2,147,483,647        |
*  #5   | 4            | Lenght of .neko file (used for file verification) | 0 <-> 2,147,483,647        |
*  #6   | 32           | SHA-256 of .neko file after these 32 bytes (^)    | must be a valid sha-256    |
*       | =============+===================================================+=========================== |
*  #7   | 2            | Number of hidden fields                           | 0 <-> 65,535               |
*       | --- loop --- for every box:                                      |                            |
*  #8   | - 1          | Hidden field key length                           | 1 <-> 255                  |
*  #9   | - n          | Hidden field key content                          | alphanumeric               |
*  #10  | - 1          | Hidden field value length                         | 1 <-> 255                  |
*  #11  | - n          | Hidden field value content                        |                            |
*       | =============+===================================================+=========================== |
*  #12  | 1            | Boolean: Is this a box (1), or boxless code (0)?  | 0 or 1                     |
*  #13  | 4            | Length of boxless code content                    | 0 <-> n                    |
*  #14  | n            | Boxless code                                      |                            |
*       | =============+===================================================+=========================== |
*  #15  | 2            | Number of boxes                                   | 0 <-> 65,535               |
*       | --- loop --- for every box:                                      |                            |
*  #16  | - 4          | 32 bits of box metadata (access, etc)             | 0x00000000 <-> 0x7fffffff  |
*  #17  | - 1          | Box name length                                   | 1 <-> 255                  |
*  #18  | - n          | Box name                                          | alphanumeric, /            |
*  #19  | - 1          | Box parent name length                            | 1 <-> 255                  |
*  #20  | - n          | Box parent name                                   | alphanumeric, /            |
*  #21  | - 4          | Number of fields                                  | 0 <-> 2,147,483,647        |
*  #22  | - 4          | Number of functions                               | 0 <-> 2,147,483,647        |
*       | --- loop --- for each box, for every field:                      |                            |
*  #23  | -- 4         | 32 bits of field metadata (access, etc)           | 0x00000000 <-> 0x7fffffff  |
*  #24  | -- 1         | Field name length                                 | 1 <-> 255                  |
*  #25  | -- n         | Field name                                        | alphanumeric               |
*  #26  | -- 1         | Field default value type                          | 1 <-> 255                  |
*  #27  | -- 1         | Field default value length                        | 1 <-> 255                  |
*  #28  | -- n         | Field default value                               |                            |
*       | --- loop --- for each box, for every function:                   |                            |
*  #29  | -- 4         | 32 bits of box metadata (access, etc)             | 0x00000000 <-> 0x7fffffff  |
*  #30  | -- 1         | Function name length                              | 1 <-> 255                  |
*  #31  | -- n         | Function name                                     | alphanumeric               |
*  #32  | -- 1         | Function signature length                         | 1 <-> 255                  |
*  #33  | -- n         | Function signature                                |                            |
*  #34  | -- 8         | Function code length                              | 1 <-> 9223372036854775807  |
*  #35  | -- n         | Function code                                     | 0 <-> n                    |
*       | =============+===================================================+=========================== |
*  #36  | --- the byte counter here should be equal to the file length --- | see #5                     |
*       \ =============+===================================================+=========================== /
*/

/**
Interesting stuff below:

WINDOWS:
    The maximum value for an 'int' is:        2147483647
    The maximum value for a 'long int' is:    2147483647
    The maximum value for a 'long' is:        2147483647
    The maximum value for a 'long long' is:   9223372036854775807

    Size of 'int':        32 bits
    Size of 'long int':   32 bits
    Size of 'long':       32 bits
    Size of 'long long':   64 bits

LINUX (WSL on Windows):
    The maximum value for an 'int' is:        2147483647
    The maximum value for a 'long int' is:    9223372036854775807
    The maximum value for a 'long' is:        9223372036854775807
    The maximum value for a 'long long' is:   9223372036854775807

    Size of 'int':        32 bits
    Size of 'long int':    64 bits
    Size of 'long':        64 bits
    Size of 'long long':   64 bits
*/