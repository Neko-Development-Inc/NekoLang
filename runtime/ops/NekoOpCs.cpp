#pragma once

#ifndef NEKO_OP_CS_H
#define NEKO_OP_CS_H

#include "NekoOp.h"

namespace ops {
class NekoOpCs : public NekoOp {

public:
    explicit NekoOpCs()
        : NekoOp(CS) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpCs>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpCs");
        println("NekoOpCs: Stack size before CS: ", s.count());
        s.clear();
        println("NekoOpCs: Stack size after CS: ", s.count());
        return 0;
    }

};
}

#endif //NEKO_OP_CS_H