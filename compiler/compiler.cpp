#include "compiler.h"

#include <any>

namespace compiler {

    void Compiler::test() { // NOLINT(*-convert-member-functions-to-static)
        println("Hello world from Compiler");

        std::ifstream stream("../sources/testing/test.cat");
        std::ostringstream ss;
        ss << stream.rdbuf();
        auto str = ss.str();

        Reader reader(str);
        println("reader: `", reader.currentString(), "`");

        char opening = reader.findFirstOpening();
        auto [start, end, len] = reader.findRange(opening);
        auto inner = reader.str.substr(start+1, len-2);
        reader.set(end);
        println("reader: `", reader.currentString(), "`");

        Reader readerInner(inner);
        println("readerInner: `", readerInner.currentString(), "`");

    }

} // compiler