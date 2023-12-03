#pragma once

#ifndef NEKO_OP_OUT_H
#define NEKO_OP_OUT_H

#include "NekoOp.h"

namespace ops {
class NekoOpOut : public NekoOp {

public:
    explicit NekoOpOut()
            : NekoOp(OUT) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpOut>(*this);
    }

    void execute(Runtime& r, NekoStack& s) override {
        cout << "NekoOpOut\n";
        auto size = s.count();
        auto a = s.pop();
        if (!a.success) {
            cerr << "Error: NekoOpOut: Failed to pop from stack. (Size: " << size << ")\n";
            exit(1);
        }
        auto b = &a.obj;
        if (!b->has_value()) {
            cerr << "Error: NekoOpOut: Optional was empty\n";
            exit(1);
        }
        auto c = *b->value();
        if (a.type == ObjectType::T_NUMBER) {
            auto num = dynamic_cast<NekoNumber*>(*a.obj->get())->get();
            cout << num;
        } else if (a.type == ObjectType::T_STRING) {
            auto str = dynamic_cast<NekoString*>(*a.obj->get())->get();
            cout << str;
        }
    }

};
}

#endif //NEKO_OP_OUT_H