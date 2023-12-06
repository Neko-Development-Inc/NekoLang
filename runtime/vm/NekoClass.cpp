#include "NekoClass.h"

namespace vm {

    void NekoClass::addFunction(const NekoFunction& func) {
        functions.insert(std::make_pair(func.name, &func));
    }

    void NekoClass::removeFunction(const string& name) {
        functions.erase(name);
    }

}