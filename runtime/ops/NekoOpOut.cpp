#pragma once

#ifndef NEKO_OP_OUT_H
#define NEKO_OP_OUT_H

#include "NekoOp.h"

namespace ops {
class NekoOpOut : public NekoOp {

public:
    explicit NekoOpOut()
            : NekoOp(OUT) {}
    explicit NekoOpOut(short opcode)
            : NekoOp(opcode) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpOut>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpOut");
        auto size = s.count();
        auto a = s.pop();
        if (!a.success) {
            errorln("Error: NekoOpOut: Failed to pop from stack. (Size: ", size, ")");
            exit(1);
        }
        if (!a.obj.has_value()) {
            errorln("Error: NekoOpOut: Optional was empty");
            exit(1);
        }
        bool isErr = (opcode == ERR);
        bool doFlush = false;
        if (!args.empty()) {
            auto first = args[0];
            if (!first.has_value()) {
                errorln("Error: NekoOpOut args was empty");
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(bool)) {
                errorln("Error: NekoOpOut args[0] wasn't a bool, ",
                        "it was: '", type.name(), "'");
                exit(1);
            }
            doFlush = std::any_cast<bool>(first);
        }
        if (a.type == ObjectType::T_NUMBER) {
            auto num = dynamic_cast<NekoNumber*>(*a.obj->get())->get();
            if (!isErr) {
                println(num);
                if (doFlush) cout << std::flush;
            } else {
                errorln(num);
                if (doFlush) cerr << std::flush;
            }
        } else if (a.type == ObjectType::T_STRING) {
            auto str = dynamic_cast<NekoString*>(*a.obj->get())->get();
            if (!isErr) {
                println(str);
                if (doFlush) cout << std::flush;
            } else {
                errorln(str);
                if (doFlush) cerr << std::flush;
            }
        }
        return 0;
    }

};
}

#endif //NEKO_OP_OUT_H