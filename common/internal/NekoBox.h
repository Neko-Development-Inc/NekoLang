#pragma once

#ifndef NEKO_CLASS_H
#define NEKO_CLASS_H

#include "../../headers.h"
#include "NekoFunction.h"
#include "NekoVariable.h"

class vm::NekoBox {

public:
    string path, name, extends, filepath;

    std::unique_ptr<NekoBox> boxExtends;
    map<string, std::unique_ptr<NekoVariable>> variables;
    map<string, std::unique_ptr<NekoFunction>> functions;

    explicit NekoBox(const string& name)
        : NekoBox("", name, "") { }

    explicit NekoBox(const string& name, const string& extends)
        : NekoBox("", name, extends) { }

    explicit NekoBox(const string& path, const string& name, const string& extends) :
        path(path),
        name(name),
        extends(extends) { }

    void setFilepath(const string&);
    void setPath(const string&);
    void setExtends(const string&);

    void addVar(std::unique_ptr<NekoVariable>);
    void removeVar(const string&);

    void addFunction(std::unique_ptr<NekoFunction>);
    void removeFunction(const string&);

};

#endif //NEKO_CLASS_H