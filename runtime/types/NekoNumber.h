#pragma once
#ifndef NEKO_NUMBER_H
#define NEKO_NUMBER_H

#include "NekoObject.h"

#include <cmath>

namespace types {
class NekoNumber : public NekoObject<long double> {

public:
    explicit NekoNumber(long double num) :
        NekoObject(num) {}

    long double get() override;
    void set(long double) override;

    bool hasDecimals();

};
}

#endif //NEKO_NUMBER_H