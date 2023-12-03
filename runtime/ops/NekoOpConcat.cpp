#pragma once

#ifndef NEKO_OP_CONCAT_H
#define NEKO_OP_CONCAT_H

#include "NekoOp.h"

namespace ops {
class NekoOpConcat : public NekoOp {

public:
    explicit NekoOpConcat()
            : NekoOp(CONCAT) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpConcat>(*this);
    }

    void execute(Runtime& r, NekoStack& s) override {
        cout << "NekoOpConcat\n";
        // TODO: Check 'args' for _N. Default 2
        auto pop1 = s.pop();
        if (!pop1.success) {
            cerr << "Error: NekoOpConcat: pop1 failed\n";
            exit(1);
        }
        auto pop2 = s.pop();
        if (!pop2.success) {
            cerr << "Error: NekoOpConcat: pop2 failed\n";
            exit(1);
        }
        // Both are numbers
        if (pop1.type == ObjectType::T_NUMBER && pop2.type == ObjectType::T_NUMBER) {
            auto num1 = dynamic_cast<NekoNumber*>(*pop1.obj->get());
            auto num2 = dynamic_cast<NekoNumber*>(*pop2.obj->get());

            auto result = string();

            long long numLong2 = static_cast<long long>(num2->get());
            if (num2->hasDecimals()) result.append(to_string(num2->get()));
            else result.append(to_string(numLong2));

            long long numLong1 = static_cast<long long>(num1->get());
            if (num1->hasDecimals()) result.append(to_string(num1->get()));
            else result.append(to_string(numLong1));

            s.add(result, T_STRING);
            return;
        }
        // Both are strings
        else if (pop1.type == ObjectType::T_STRING && pop2.type == ObjectType::T_STRING) {
            auto str1 = dynamic_cast<NekoString*>(*pop1.obj->get())->get();
            auto str2 = dynamic_cast<NekoString*>(*pop2.obj->get())->get();
            auto result = str2.append(str1);
            s.add(result, T_STRING);
            return;
        }
        // First is number, Second is string
        else if (pop1.type == ObjectType::T_NUMBER && pop2.type == ObjectType::T_STRING) {
            auto num = dynamic_cast<NekoNumber*>(*pop1.obj->get());
            auto str = dynamic_cast<NekoString*>(*pop2.obj->get())->get();
            auto result = str;

            long long numLong = static_cast<long long>(num->get());
            if (num->hasDecimals()) result.append(to_string(num->get()));
            else result.append(to_string(numLong));

            s.add(result, T_STRING);
            return;
        }
        // First is string, Second is number
        else if (pop1.type == ObjectType::T_STRING && pop2.type == ObjectType::T_NUMBER) {
            auto str = dynamic_cast<NekoString*>(*pop1.obj->get())->get();
            auto num = dynamic_cast<NekoNumber*>(*pop2.obj->get());
            auto result = string();

            long long numLong = static_cast<long long>(num->get());
            if (num->hasDecimals()) result.append(to_string(num->get()));
            else result.append(to_string(numLong));

            result.append(str);
            s.add(result, T_STRING);
            return;
        }
        cerr << "Error: NekoOpConcat: Unknown stack types: "
                "pop1.type(" << pop1.type << "), "
                "pop2.type(" << pop2.type << ")\n";
        exit(1);
    }

};
}

#endif //NEKO_OP_CONCAT_H