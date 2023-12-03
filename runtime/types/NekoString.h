#pragma once

#ifndef NEKO_STRING_H
#define NEKO_STRING_H

#include "../../headers.h"
#include "NekoObject.h"

namespace types {
class NekoString : public NekoObject<string> {

public:
    explicit NekoString(string str) :
        NekoObject(str) {}
    explicit NekoString(const char* str) :
        NekoObject(string(str)) {}

    string get() override;
    void set(string) override;

};
}

#endif //NEKO_STRING_H