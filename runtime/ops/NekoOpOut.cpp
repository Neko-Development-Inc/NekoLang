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

    void execute(Runtime& r, NekoStack& s) override {
//        cout << "NekoOpOut\n";
        auto size = s.count();
        auto a = s.pop();
        if (!a.success) {
            cerr << "Error: NekoOpOut: Failed to pop from stack. (Size: " << size << ")\n";
            exit(1);
        }
        if (!a.obj.has_value()) {
            cerr << "Error: NekoOpOut: Optional was empty\n";
            exit(1);
        }
        bool isErr = (opcode == ERR);
        bool doFlush = false;
        if (!args.empty()) {
            auto first = args[0];
            if (!first.has_value()) {
                cerr << "Error: NekoOpOut args was empty\n";
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(bool)) {
                cerr << "Error: NekoOpOut args[0] wasn't a bool, "
                        "it was: '" << type.name() << "'\n";
                exit(1);
            }
            doFlush = std::any_cast<bool>(first);
        }
        if (a.type == ObjectType::T_NUMBER) {
            auto num = dynamic_cast<NekoNumber*>(*a.obj->get())->get();
            if (!isErr) {
                cout << num;
                if (doFlush) cout << std::flush;
            } else {
                cerr << num;
                if (doFlush) cerr << std::flush;
            }
        } else if (a.type == ObjectType::T_STRING) {
            auto str = dynamic_cast<NekoString*>(*a.obj->get())->get();
            if (!isErr) {
                cout << str;
                if (doFlush) cout << std::flush;
            } else {
                cerr << str;
                if (doFlush) cerr << std::flush;
            }
        }
    }

};
}

#endif //NEKO_OP_OUT_H