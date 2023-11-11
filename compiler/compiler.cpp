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
        println("index: ", reader.index, ", length: ", reader.end+1);
        string out;
        while (reader.hasMore()) {
            char p2 = reader.peekPrev(2);
            char p = reader.peekPrev();
            char c = reader.curr();
            char n = reader.peekNext();
            char n2 = reader.peekNext(2);
            if (reader.index == 0 && c == '!') {

            }
            out += c;
            reader.move(1);
        }
        println(out);

        out = "";
        reader.set(0);
        while (reader.hasMore()) {
            out += reader.curr();
            out += ": " + to_string((int)reader.mappings[reader.index]) + '\n';
            reader.move(1);
        }
        println(out);
    }

} // compiler