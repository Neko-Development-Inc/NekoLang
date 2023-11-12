#include "compiler.h"

#include <any>

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

        char opening = reader.findFirstOpening();

        auto [start, end, len] = reader.findRange(opening);
        println(start, " ", end, " ", len);

        auto inner = reader.str.substr(start+1, len-2);
        println(inner);

        Reader readerInner(inner);
        readerInner.skipWhitespace();
        println(readerInner.index);

//        string out;
//        while (reader.hasMore()) {
//            auto [ p, c, n ] = any_cast<Ret1>(reader.charN(1));
////            println(p5, p4, p3, p2, p, c, n, n2, n3, n4, n5);
//            out += c;
//            reader.move(1);
//        }
//        println(out);

//        out = "";
//        reader.set(0);
//        while (reader.hasMore()) {
//            out += reader.curr();
//            out += ": " + to_string((int)reader.mappings[reader.index]) + '\n';
//            reader.move(1);
//        }
//        println(out);
    }

} // compiler