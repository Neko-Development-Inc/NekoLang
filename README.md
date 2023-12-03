# NekoLang - cat-ish programming language  
Takes inspiration from multiple languages, including: Java, JavaScript, Python, PHP.  
Uses my very own custom instruction-set; no copy-pasted code from elsewhere, otherwise specifically commented.  

## Preview
<sub><sup>
    This preview might differ from the text inside [main.cpp (at the bottom)](https://github.com/Neko-Development-Inc/NekoLang/blob/master/main.cpp#L78),
    but I'll try to keep it up-to-date.
</sup></sub>
```js
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
 *   < box Name >.<
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
 *   null     = E - alias for the above empty type
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
 *  DUP          = 3 - duplicate the last element on the Stack
 *  DUP_2        = 4 - duplicate the last 2 elements on the Stack
 *  DUP_3        = 5 - duplicate the last 3 elements on the Stack
 *  DUP_N        = 6 - duplicate the last N elements on the Stack
 *    <n>            Number
 *  CS           = 7 - clear the stack
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
 *  OUT          = 5000 - prints the last value on the Stack to
 *                        the active output stream (stdout by default)
 *    <bool>            Bool -- force flush or not -- optional
 *  ERR          = 5001 - prints the last value on the Stack to
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
```