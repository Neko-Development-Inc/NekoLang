#include "compiler.h"

namespace compiler {

    void Compiler::parseFile(string filePath) { // NOLINT(*-convert-member-functions-to-static)
        cout << "Hello world from Compiler\n";

        std::ifstream stream("../sources/" + filePath);
        std::ostringstream ss;

        ss << stream.rdbuf();
        auto str = ss.str();
        stream.close();

        doParseFile(str);
    }

    void Compiler::doParseFile(string& str) {
        Reader reader(str);
        cout << "reader: `" << reader.currentString() << "`\n";

        int afterIndex{0};
        auto next = reader.whatIsNext(afterIndex);
        switch (next.what) {
            case BOX:
                break;
            case FUN:
                break;
            case VAR:
                break;
            case FOR_LOOP:
                break;
            case WHILE_LOOP:
                break;
            case IF_CHECK:
                break;
            case CODE_BLOCK:
                break;
            case EX_MARK:
                break;
            case SCAWY_SPOOPY:
                break;
            case UNKNOWN:
                break;
        }

        char opening = reader.findFirstOpening();
        auto [start, end, len] = reader.findRange(opening);
        auto inner = reader.getRange(start, len);
        reader.set(end);
        cout << "reader: `" << reader.currentString() << "`\n";

        Reader readerInner(inner);
        cout << "readerInner: `" << readerInner.currentString() << "`\n";
    }

} // compiler