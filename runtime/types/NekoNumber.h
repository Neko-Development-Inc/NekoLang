#pragma once

#ifndef NEKO_NUMBER_H
#define NEKO_NUMBER_H

#include "../../headers.h"
#include "NekoObject.h"
#include "NekoNumber.h"
#include "NekoString.h"

namespace types {
class NekoNumber : public NekoObject<_NekoNumberType_> {

public:
    explicit NekoNumber(_NekoNumberType_ num) :
        NekoObject(num) {}

    _NekoNumberType_ get() override;
    void set(_NekoNumberType_) override;

    bool hasDecimals();

};
}

#endif //NEKO_NUMBER_H