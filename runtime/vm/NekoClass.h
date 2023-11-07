#pragma once
#ifndef NEKO_CLASS_H
#define NEKO_CLASS_H

#include <string>
#include <map>
#include <any>
#include <utility>

using std::string, std::map;

namespace vm {
class NekoClass {

public:
    string name;
    map<string, std::any> functions{};

    explicit NekoClass(string name) :
        name(std::move(name)) { }

};
}

#endif //NEKO_CLASS_H