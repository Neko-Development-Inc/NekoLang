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

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpNumber");
        if (args.empty()) {
            errorln("Error: NekoOpNumber args was empty");
            exit(1);
        }
        auto first = args[0];
        if (!first.has_value()) {
            errorln("Error: NekoOpNumber args was empty");
            exit(1);
        }
        const auto& type = first.type();
        if (type == typeid(int)) {
            s.add(any_cast<int>(first), T_NUMBER);
            return 0;
        }
        if (type == typeid(long)) {
            s.add(any_cast<long>(first), T_NUMBER);
            return 0;
        }
        if (type == typeid(double)) {
            s.add(any_cast<double>(first), T_NUMBER);
            return 0;
        }
        if (type == typeid(long double)) {
            s.add(any_cast<long double>(first), T_NUMBER);
            return 0;
        }
        if (type == typeid(long long)) {
            s.add(any_cast<long long int>(first), T_NUMBER);
            return 0;
        }
        if (type == typeid(long int)) {
            s.add(any_cast<long int>(first), T_NUMBER);
            return 0;
        }
        errorln("Error: NekoOpNumber args[0] wasn't a number, ",
                "it was: '", type.name(), "'");
        exit(1);
    }

};
}

#endif //NEKO_OP_NUMBER_H