# NekoLang - cat-ish programming language  
Takes inspiration from multiple languages, including: Java, JavaScript, Python, PHP.  
Uses my very own custom instruction-set; no copy-pasted code from elsewhere, otherwise specifically commented.  

## Preview
<sub><sup>
    This preview might differ from the text inside [main.cpp (at the bottom)](https://github.com/Neko-Development-Inc/NekoLang/blob/master/main.cpp#L122),
    but I'll try to keep it up-to-date.
</sup></sub>
```js
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
 *  neko -r myprogram.cat                     -- execute the source code file
 * Arguments:
 *  -i <file> - Choose one or more input file(s)
 *  -r        - Run a program
 *
 * Macro stuff:
 *  #catflap :3  - entrypoint
 *  #cat-flap :3 - entrypoint
 *
 *  #pls x       - includes x.cat (by copy paste)
 *  #pls x as y  - includes x.cat (as reference y) -- might remove this
 *
 *  #<name>      - insert a literal value
 *
 * box  - class
 * var  - variable
 * owo  - variable
 * uwu  - variable
 * angy - read-only variable
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
 *   [0] empty    = E - empty type
 *   [0] null     = E - ^ alias for the above empty type
 *   [1] object   = * - object, any type below
 *   [2] number   = N - int or decimal (always 64-bit)
 *   [3] string   = S - character array
 *   [4] bool     = B - true/false
 *   [5] box-type = <path/name> - any box type
 *   [6] array    = A - array of any type
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
 *    <N>            Number
 *
 *  DUP          = 3  - duplicate the last element on the Stack
 *  DUP_2        = 4  - duplicate the last 2 elements on the Stack
 *  DUP_3        = 5  - duplicate the last 3 elements on the Stack
 *  DUP_N        = 6  - duplicate the last N elements on the Stack
 *    <N>             Number
 *  DUP_ALL      = 7  - duplicate all the elements on the Stack
 *
 *  NDUP         = 8  - duplicate the last element on the Stack, N times
 *    <N>             Number of times to duplicate
 *  NDUP_2       = 9  - duplicate the last 2 elements on the Stack, N times
 *    <N>             Number of times to duplicate
 *  NDUP_3       = 10 - duplicate the last 3 elements on the Stack, N times
 *    <N>             Number of times to duplicate
 *  NDUP_N       = 11 - duplicate the last N elements on the Stack, N times
 *    <N1>            Number of elements from the stack to duplicate
 *    <N2>            Number of times to duplicate
 *  NDUP_ALL     = 12 - duplicate all the elements on the Stack, N times
 *    <N>             Number of times to duplicate
 *
 *  CS           = 20 - clear the stack
 *
 *  LABEL        = 1000 - label, a specific point in an instruction-set
 *    <id>              Number/String
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
 *    <N>               Number -- number of elements to concatenate
 *  CONCAT_ALL   = 3004 - concatenates all the elements on the Stack, and
 *                        puts the Result back on the Stack
 *
 *  REPEAT       = 4000 - repeat the last instruction once
 *  REPEAT_N     = 4001 - repeat the last instruction N times
 *    <N>               Number -- number of times to repeat
 *  REPEAT_LL    = 4002 - repeats the instructions between two Labels
 *                      - L stands for Label
 *    <L1>              Number -- index of first Label
 *    <L2>              Number -- index of second Label
 *  REPEAT_LL_N  = 4003 - repeats the instructions between two Labels N times
 *                      - L stands for Label
 *    <L1>              Number -- index of first Label
 *    <L2>              Number -- index of second Label
 *    <N>               Number -- number of times to repeat
 *
 *  NREPEAT      = 4004 - repeat the last N instructions once
 *    <N>               Number of times to duplicate
 *  NREPEAT_N    = 4005 - repeat the last N instruction N times
 *    <L1>              Number of elements from the stack to repeat
 *    <L2>              Number of times to repeat
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
 * Example problem using REPEAT_LL and REPEAT_LL_N:
 *  We have an opcode REPEAT_LL_N that is designed to loop 10 times,
 *   but we manually halt it at 5 iterations.
 *  The challenge here is to devise a logic that can accurately instruct
 *   the REPEAT opcode to cease looping.
 *  A potential solution could be to maintain a stack that holds a reference
 *   to each REPEAT_LL or REPEAT_LL_N opcode every time we enter one.
 *  This way, we can introduce a new opcode that can stop or abort the
 *   most recent REPEAT_LL or REPEAT_LL_N by using the reference at the top of the stack.
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
 *    -- this is the end of the program
 *
 * Example program 2 (opcodes):
 *    NUMBER 1
 *    PLACE 0                    -- place the number 1 on the local variable table at index 0
 *    JUMP LBL_1
 *  LABEL LBL_0
 *    STRING 'Hello '            -- push the string 'Hello ' to the stack
 *    NUMBER 420                 -- push the number 420 to the stack
 *    CONCAT                     -- concatenate the last two elements on the stack
 *    STRING ' :)\n'             -- push the string ' :)\n' to the stack
 *    CONCAT                     -- concatenate the last two elements on the stack
 *    OUT true                   -- print the string 'Hello 420 :)' to stdout
 *    FETCH 0                    -- fetch the number 1 from the local variable table at index 0
 *                               -- and place it on the top of the stack
 *    CMP_EQ 5 LBL_END           -- If the top of the stack is equal to 5, jump to LBL_END
 *                               -- otherwise continue to the next instruction
 *    INC 0                      -- increment the number at index 0 on the local variable table
 *  LABEL LBL_1
 *    REPEAT_LL_N LBL_0 LBL_1 10 -- repeat the instructions between LBL_0 and LBL_1 10 times
 *  LABEL LBL_END
 *    -- this is the end of the program
 *
 * Example program 3 (opcodes):
 *    NUMBER 1
 *    PLACE 0
 *    JUMP LBL_1
 *  LABEL LBL_0
 *    STRING 'Hello '
 *    NUMBER 420
 *    CONCAT
 *    STRING ' :)\n'
 *    CONCAT
 *    OUT true                      -- Print the stack first
 *    JUMP TEST_2                   -- Jump immediately to TEST_2 below
 *  LABEL TEST_1
 *    STRING 'OWO'
 *    OUT true
 *  LABEL TEST_2
 *    REPEAT_LL_N TEST_1 TEST_2 100 -- Start an internal loop within the already
 *                                  -- existing loop, and repeat it 100 times
 *    FETCH 0
 *    CMP_EQ 5 LBL_END              -- End the outer loop after 5 iterations
 *    INC 0
 *  LABEL LBL_1
 *    REPEAT_LL_N LBL_0 LBL_1 10    -- Start an outer loop, and repeat it 10 times
 *  LABEL LBL_END
 *    -- this is the end of the program
 *
 * Example program 4 (opcodes):
 * |        NUMBER 1
 * |        PLACE 0
 * |        JUMP TEST_4 >--------------------->|
 * |                                           |
 * |  |>->LABEL TEST_1                         |
 * |  |                                        |
 * |  |  |>->LABEL TEST_2                      |
 * |  |  |     STRING 'OWO'                    |
 * |  |  |     OUT true                        |
 * |  |  |>->LABEL TEST_3                      |
 * |  |  |<--< REPEAT_LL_N TEST_2 TEST_3 100   |
 * |  |                                        |
 * |  |     FETCH 0                            |
 * |  |     CMP_EQ 5 LBL_END >---------------> | >->|
 * |  |     INC 0                              |    |
 * |  |                                        |    |
 * |  |>->LABEL TEST_4 <----------------------<|    |
 * |  |<--< REPEAT_LL_N TEST_1 TEST_4 10            |
 * |                                                |
 * |      LABEL LBL_END <--------------------------<|
 * |        -- this is the end of the program
 *
 * Example program 5 (opcodes):
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
 *    -- this is the end of the program
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
 *  #2   | 1            | General encryption key (everything below uses it) | 0 <-> 255 (0 = not in use) |
 *  #3   | 4            | 32 bits of useful metadata (endianness, etc)      | 0x00000000 <-> 0x7fffffff  |
 *  #4   | 4            | Major version number                              | 0 <-> 2,147,483,647        |
 *  #5   | 4            | Minor version number                              | 0 <-> 2,147,483,647        |
 *  #6   | 4            | Lenght of .neko file (used for file verification) | 0 <-> 2,147,483,647        |
 *  #7   | 32           | SHA-256 of .neko file after these 32 bytes (^)    | must be a valid sha-256    |
 *  #8   | 1            | Opcode key                                        | 0 <-> 255 (0 = not in use) |
 *       | =============+===================================================+=========================== |
 *  #9   | 2            | Number of hidden fields K                         | 0 <-> 65,535               |
 *       | --- loop --- for every K box:                                    |                            |
 *  #10  | - 1          | Hidden field key length N                         | 1 <-> 255                  |
 *  #11  | - N          | Hidden field key content                          | alphanumeric & 1 <-> N     |
 *  #12  | - 2          | Hidden field value length N                       | 1 <-> 65,535               |
 *  #13  | - N          | Hidden field value content                        | 1 <-> N                    |
 *       | =============+===================================================+=========================== |
 *  #14  | 1            | Boolean: Is this a box (1), or boxless code (0)?  | 0 or 1                     |
 *  #15  | 4            | Length of boxless code content N                  | 0 <-> N                    |
 *  #16  | N            | Boxless code                                      |                            |
 *       | =============+===================================================+=========================== |
 *  #17  | 2            | Number of boxes K                                 | 0 <-> 65,535               |
 *       | --- loop --- for every K box:                                    |                            |
 *  #18  | - 4          | 32 bits of box metadata (access, etc)             | 0x00000000 <-> 0x7fffffff  |
 *  #19  | - 1          | Box name length N                                 | 1 <-> 255                  |
 *  #20  | - N          | Box name                                          | alphanumeric, /            |
 *  #21  | - 1          | Box parent name length N                          | 1 <-> 255                  |
 *  #22  | - N          | Box parent name                                   | alphanumeric, /            |
 *  #23  | - 4          | Number of fields                                  | 0 <-> 2,147,483,647        |
 *  #24  | - 4          | Number of functions                               | 0 <-> 2,147,483,647        |
 *       | --- loop --- for each box, for every field:                      |                            |
 *  #25  | -- 4         | 32 bits of field metadata (access, etc)           | 0x00000000 <-> 0x7fffffff  |
 *  #26  | -- 1         | Field name length N                               | 1 <-> 255                  |
 *  #27  | -- N         | Field name                                        | alphanumeric               |
 *  #28  | -- 1         | Field default value type                          | 0 <-> 255                  |
 *  #29  | -- 1         | Field default value length N                      | 0 <-> 255                  |
 *  #30  | -- N         | Field default value                               |                            |
 *       | --- loop --- for each box, for every function:                   |                            |
 *  #31  | -- 4         | 32 bits of function metadata (access, etc)        | 0x00000000 <-> 0x7fffffff  |
 *  #32  | -- 1         | Function name length N                            | 1 <-> 255                  |
 *  #33  | -- N         | Function name                                     | alphanumeric               |
 *  #34  | -- 1         | Function signature length N                       | 1 <-> 255                  |
 *  #35  | -- N         | Function signature                                |                            |
 *  #36  | -- 8         | Function code length N                            | 1 <-> 9223372036854775807  |
 *  #37  | -- N         | Function code                                     | 0 <-> N                    |
 *       | =============+===================================================+=========================== |
 *  #38  | --- the byte counter here should be equal to the file length --- | see #6                     |
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
```