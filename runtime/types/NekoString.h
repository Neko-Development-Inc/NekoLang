#pragma once
#ifndef NEKO_STRING_H
#define NEKO_STRING_H

#include "NekoObject.h"

#include <cmath>
#include <string>

using std::string;

namespace types {
class NekoString : public NekoObject<string> {

public:
    explicit NekoString(string str) :
        NekoObject(str) {}

    string get() override;
    void set(string) override;

};
}

#endif //NEKO_STRING_H