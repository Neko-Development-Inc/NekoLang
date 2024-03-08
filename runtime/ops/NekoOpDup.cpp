#include "NekoOp.h"

namespace ops {
class NekoOpDup : public NekoOp {

public:
    explicit NekoOpDup()
        : NekoOp(DUP) {}

    explicit NekoOpDup(short opcode)
            : NekoOp(opcode) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpDup>(*this);
    }

    struct WhatCopy {
        any obj;
        ObjectType type;
    };

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpDup");

        int n;
        if (opcode == DUP) n = 1;
        else if (opcode == DUP_2) n = 2;
        else if (opcode == DUP_3) n = 3;
        else if (opcode == DUP_N) {
            if (args.empty()) {
                errorln("Error: NekoOpDup: DUP_N args was empty");
                exit(1);
            }
            auto first = args[0];
            if (!first.has_value()) {
                errorln("Error: NekoOpDup: DUP_N args was empty");
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(int)) {
                errorln("Error: NekoOpDup args[0] wasn't a number, ",
                        "it was: '", type.name(), "'");
                exit(1);
            }
            n = std::any_cast<int>(first);
        } else {
            errorln("Error: NekoOpDup: Unknown DUP opcode: ", opcode);
            exit(1);
        }

        vector<WhatCopy> items(n);
        while (n--) {
            auto type = s.peek();
            switch (type) {
                case T_NUMBER: {
                    auto item = s.pop();
                    auto num = *reinterpret_cast<NekoNumber*>(*item.obj->get());
                    items.emplace_back(num.get(), type);
                } break;
                case T_STRING: {
                    auto item = s.pop();
                    auto str = *reinterpret_cast<NekoString*>(*item.obj->get());
                    items.emplace_back(str.get(), type);
                } break;
                case T_NONE:
                case T_UNKNOWN:
                    errorln("Error: NekoOpDup: Unknown peek type: ", (int)type);
                    exit(1);
            }
        }

        for (const auto &item: items) {
            switch (item.type) {
                case T_NUMBER: {
                    auto num = std::any_cast<long double>(item.obj);
                    s.add(num, item.type);
                    s.add(num, item.type);
                } break;
                case T_STRING: {
                    auto str = std::any_cast<string>(item.obj);
                    s.add(str, item.type);
                    s.add(str, item.type);
                } break;
                case T_NONE:
                case T_UNKNOWN:
                    break; // Shouldn't happen due to the check above
            }
        }

        return CONTINUE_EXECUTION;
    }

};
}