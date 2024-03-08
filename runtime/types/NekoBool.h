#pragma once

#ifndef NEKO_BOOL_H
#define NEKO_BOOL_H

#include "../../headers.h"
#include "NekoObject.h"
#include "NekoNumber.h"
#include "NekoString.h"

namespace types {
class NekoBool : public NekoObject<bool> {

public:
    explicit NekoBool(bool b) :
        NekoObject(b) {}

    bool get() override;
    void set(bool) override;

    static const string TRUE;
    static const string FALSE;

};
}

#endif //NEKO_BOOL_H