#pragma once

#ifndef NEKO_OP_STRING_H
#define NEKO_OP_STRING_H

#include "NekoOp.h"

namespace ops {
class NekoOpString : public NekoOp {

public:
    explicit NekoOpString()
            : NekoOp(STRING) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpString>(*this);
    }

    void execute(Runtime& r, NekoStack& s) override {
        cout << "NekoOpString\n";
        if (args.empty()) {
            cerr << "Error: NekoOpString args was empty\n";
            exit(1);
        }
        auto first = args[0];
        if (!first.has_value()) {
            cerr << "Error: NekoOpString args was empty\n";
            exit(1);
        }
        const auto& type = first.type();
        if (type == typeid(const char *)) {
            s.add(std::any_cast<const char *>(first), T_STRING);
            return;
        } else if (type == typeid(string)) {
            s.add(any_cast<string>(first), T_STRING);
            return;
        }
        cerr << "Error: NekoOpString args[0] wasn't a string, "
                "it was: '" << type.name() << "'\n";
        exit(1);
    }

};
}

#endif //NEKO_OP_STRING_H