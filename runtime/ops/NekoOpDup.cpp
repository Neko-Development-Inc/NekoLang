#pragma once

#ifndef NEKO_OP_DUP_H
#define NEKO_OP_DUP_H

#include "NekoOp.h"

namespace ops {
class NekoOpDup : public NekoOp {

public:
    explicit NekoOpDup()
        : NekoOp(DUP) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpDup>(*this);
    }

    void execute(Runtime& r, NekoStack& s) override {
        auto size = s.count();
        cout << "NekoOpDup: Stack size before: " << s.count() << "\n";
        auto a = s.pop();
        cout << "NekoOpDup: Stack size after pop: " << s.count() << "\n";
        if (!a.success) {
            cout << "NekoOpDup: Failed to pop from stack. (Size: " << size << ")\n";
            exit(1);
        }
        cout << "NekoOpDup: Stack size before dup: " << s.count() << "\n";

//        s.add(std::make_unique<NekoBase>(*a.obj->get()), a.type);
//        s.add(std::make_unique<NekoBase>(*a.obj->get()), a.type);

        cout << "NekoOpDup: Stack size after dup: " << s.count() << "\n";
    }

};
}

#endif //NEKO_OP_DUP_H