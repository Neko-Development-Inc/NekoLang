#include "compiler.h"

namespace compiler {

    void Compiler::test() { // NOLINT(*-convert-member-functions-to-static)
        println("Hello world from Compiler");

        std::ifstream stream("../sources/testing/test.cat");
        std::ostringstream ss;
        ss << stream.rdbuf();
        auto str = ss.str();
        println(str);

        Reader reader(str);
        reader.removeComments();
        println("index: ", reader.index, ", length: ", reader.end+1);
        string out;
        while (reader.hasMore()) {
            char p = reader.peekPrev();
            char c = reader.curr();
            char n = reader.peekNext();
            if (reader.index == 0 && c == '!') {

            }
            out += c;
            reader.move(1);
        }
        println(out);
    }

} // compiler