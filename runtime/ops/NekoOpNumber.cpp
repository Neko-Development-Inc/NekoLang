#pragma once

#ifndef NEKO_OP_NUMBER_H
#define NEKO_OP_NUMBER_H

#include "NekoOp.h"

namespace ops {
class NekoOpNumber : public NekoOp {

public:
    explicit NekoOpNumber()
            : NekoOp(NUMBER) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpNumber>(*this);
    }

    void execute(Runtime& r, NekoStack& s) override {
        cout << "NekoOpNumber\n";
        if (args.empty()) {
            cerr << "Error: NekoOpNumber args was empty\n";
            exit(1);
        }
        auto first = args[0];
        if (!first.has_value()) {
            cerr << "Error: NekoOpNumber args was empty\n";
            exit(1);
        }
        const auto& type = first.type();
        if (type == typeid(int)) {
            s.add(any_cast<int>(first), T_NUMBER);
            return;
        }
        if (type == typeid(long)) {
            s.add(any_cast<long>(first), T_NUMBER);
            return;
        }
        if (type == typeid(double)) {
            s.add(any_cast<double>(first), T_NUMBER);
            return;
        }
        if (type == typeid(long double)) {
            s.add(any_cast<long double>(first), T_NUMBER);
            return;
        }
        if (type == typeid(long long)) {
            s.add(any_cast<long long>(first), T_NUMBER);
            return;
        }
        if (type == typeid(long int)) {
            s.add(any_cast<long int>(first), T_NUMBER);
            return;
        }
        cerr << "Error: NekoOpNumber args[0] wasn't a number, "
                "it was: '" << type.name() << "'\n";
        exit(1);
    }

};
}

#endif //NEKO_OP_NUMBER_H