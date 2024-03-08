#include "NekoBox.h"

void vm::NekoBox::setFilepath(const string& str) {
    this->filepath = str;
}

void vm::NekoBox::setPath(const string& str) {
    this->path = str;
}

void vm::NekoBox::setExtends(const string& str) {
    this->extends = str;
}

void vm::NekoBox::addVar(std::unique_ptr<NekoVariable> var) {
    variables.insert(std::make_pair(var->name, std::move(var)));
}

void vm::NekoBox::removeVar(const string& str) {
    variables.erase(str);
}

void vm::NekoBox::addFunction(std::unique_ptr<NekoFunction> func) {
    functions.insert(std::make_pair(func->name, std::move(func)));
}

void vm::NekoBox::removeFunction(const string& str) {
    functions.erase(str);
}