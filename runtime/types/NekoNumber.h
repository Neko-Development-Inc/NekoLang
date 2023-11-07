#pragma once
#ifndef NEKO_NUMBER_H
#define NEKO_NUMBER_H

#include "NekoObject.h"

namespace types {
class NekoNumber : public NekoObject<double> {

public:
    explicit NekoNumber(double num) : NekoObject(num) {}

    double get() override;
    void set(double) override;

};
}

#endif //NEKO_NUMBER_H