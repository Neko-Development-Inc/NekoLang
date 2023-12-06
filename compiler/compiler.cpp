#include "compiler.h"

namespace compiler {

    void Compiler::parseFile(string filePath) {
        println("Hello world from Compiler");

        std::ifstream stream("../sources/" + filePath);
        std::ostringstream ss;

        ss << stream.rdbuf();
        auto str = ss.str();
        stream.close();

        Reader reader(str);
        cout << "file: `" << reader.currentString() << "`\n\n";
        parse(reader);
    }

    void Compiler::parse(Reader& reader) {
        while (true) {
            int afterIndex{0};
            auto next = reader.whatIsNext(afterIndex);
//            cout << "What is next: " << WhatMap::whatName(next.what) << "\n";
            switch (next.what) {
                case BOX:
                case FUN: {
                    string which = next.what == BOX ? "box" : "fun";

                    // Find <> range
                    auto [start, end, len] = reader.findRange('<');
                    if (start == -1 || end == -1) {
                        cerr << "Expected " << which << " header\n";
                        exit(1);
                    }
                    auto inner = reader.getRange(start, len);

                    // Move to after >
                    reader.set(end);

                    // Parse box header (inside <>)
                    Reader readerHeader(inner);
                    if (which == "box")
                        parseBoxHeader(readerHeader);
                    else
                        parseFunHeader(readerHeader);

                    reader.trimStart();
                    auto c = reader.curr();
                    if (c != '.' && c != 'w' && c != '_') {
                        cerr << "Expected `.`, `w` or `_` after " << which << " header\n";
                        exit(1);
                    }

                    // Skip dot, w or underscore
                    reader.move(1, false, true);

                    auto [start2, end2, len2] = reader.findRange('<');
                    if (start2 == -1 || end2 == -1) {
                        cerr << "Expected " << which << " body\n";
                        exit(1);
                    }
                    auto bodyInner = reader.getRange(start2, len2);

                    // Parse box header (inside <>)
                    Reader readerBody(bodyInner);
                    if (which == "box")
                        parseBoxBody(readerBody);
                    else
                        parseFunBody(readerBody);

                    // Move to after >
                    reader.set(end2);
                } goto continue_loop;
                case VAR: {
                    // Find var <> range
                    auto [start, end, len] = reader.findRange('<');
                    if (start == -1 || end == -1) {
                        cerr << "Expected var body\n";
                        exit(1);
                    }
                    auto header = reader.getRange(0, start);
                    auto body = reader.getRange(start, len);

                    // Move to after >
                    reader.set(end, false, true);

                    // Parse var header (inside <>)
                    Reader readerHeader(header);
                    parseVarHeader(readerHeader);

                    // Parse var body (inside <>)
                    Reader readerBody(body);
                    parseVarBody(readerBody);

                    // Move to after >
                    reader.set(end);
                } goto continue_loop;
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
                case CAT_FLAP: {
                    reader.set(afterIndex, true, false);
                } goto continue_loop;
                case END:
                    cout << "End of reader\n";
                    goto end_loop;
                case UNKNOWN:
                    cerr << "Unknown. Current string: `" << reader.currentString() << "`\n";
                    goto end_loop;
            }
            continue_loop:;
        }
        end_loop:;
    }

    void Compiler::parseBoxHeader(Reader& reader) {
        cout << "\nbox header: `" << reader.currentString() << "`\n";
    }
    void Compiler::parseBoxBody(Reader& reader) {
        cout << "box body: `" << reader.currentString() << "`\n\n";
        parse(reader);
    }

    void Compiler::parseVarHeader(Reader& reader) {
        cout << "\nvar header: `" << reader.currentString() << "`\n";
    }
    void Compiler::parseVarBody(Reader& reader) {
        cout << "var body: `" << reader.currentString() << "`\n\n";
    }

    void Compiler::parseFunHeader(Reader& reader) {
        cout << "\nfun header: `" << reader.currentString() << "`\n";
    }
    void Compiler::parseFunBody(Reader& reader) {
        cout << "fun body: `" << reader.currentString() << "`\n\n";
    }

} // compiler