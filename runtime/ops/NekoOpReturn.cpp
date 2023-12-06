#pragma once

#ifndef NEKO_OP_RETURN_H
#define NEKO_OP_RETURN_H

#include "NekoOp.h"

namespace ops {
class NekoOpReturn : public NekoOp {

public:
    explicit NekoOpReturn()
            : NekoOp(RETURN) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpReturn>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpReturn");
        return -1; // stop function
    }

};
}

#endif //NEKO_OP_RETURN_H