#pragma once

#ifndef NEKO_OP_CONCAT_H
#define NEKO_OP_CONCAT_H

#include "NekoOp.h"

namespace ops {
class NekoOpConcat : public NekoOp {

public:
    explicit NekoOpConcat()
            : NekoOp(CONCAT) {}
    explicit NekoOpConcat(short opcode)
            : NekoOp(opcode) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpConcat>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        cout << "NekoOpConcat\n";

        auto peek1 = s.peek();
        if (peek1 == T_NONE || peek1 == T_UNKNOWN) {
            cerr << "Error: NekoOpConcat: peek1 failed\n";
            exit(1);
        }

        string result;

        int n;
        if (opcode == CONCAT) {
            // Last 2 elements
            if (s.count() >= 2)
                n = 2;
            else
                n = 1;
        } else if (opcode == CONCAT_N) {
            if (!hasArg(0)) {
                cerr << "Error: NekoOpConcat: CONCAT_N: args[0] not found\n";
                exit(1);
            }
            if (!argIsType(0, typeid(int))) {
                cerr << "Error: NekoOpConcat: CONCAT_N: args[0] wasn't a number\n";
                exit(1);
            }
            n = getArgNumber(0);
            if (n < 1) {
                cerr << "Error: NekoOpConcat: CONCAT_N: N was below 1\n";
                exit(1);
            } else if (n > 100) {
                cout << "Warning: NekoOpConcat: CONCAT_N: N was over 100 "
                        "(N: " << n << "), did you mean to do that?\n";
            }
        } else if (opcode == CONCAT_ALL) {
            n = s.count();
            if (n > 100) {
                cout << "Warning: NekoOpConcat: CONCAT_ALL: N was over 100 "
                        "(N: " << n << "), did you mean to do that?\n";
            }
        } else {
            cerr << "Error: NekoOpConcat: Unknown opcode: " << opcode << "\n";
            exit(1);
        }

        vector<string> strings(n);
        while (n--) {
            // reversed order
            auto peek = s.peek();
            if (peek == T_NONE || peek == T_UNKNOWN) {
                cerr << "Error: NekoOpConcat: peekN(" << (n+1) << ") failed\n";
                exit(1);
            }
            switch (peek) {
                case T_NUMBER: {
                    auto num = *s.popNumber();
                    if (num > std::floor(num))
                        strings.emplace_back(to_string(num));
                    else
                        strings.emplace_back(to_string(static_cast<long long int>(num)));
                } break;
                case T_STRING: {
                    auto str = *s.popString();
                    strings.emplace_back(str);
                } break;
                case T_NONE:
                case T_UNKNOWN:
                    break;
            }
        }

        for (const auto &item: strings)
            result = item + result;

        s.add(result, T_STRING);

        return 0;
    }

};
}

#endif //NEKO_OP_CONCAT_H