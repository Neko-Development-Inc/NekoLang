#pragma once

#ifndef NEKO_STACK_H
#define NEKO_STACK_H

#include "../../headers.h"

#include "../types/NekoObject.h"
#include "../types/NekoNumber.h"
#include "../types/NekoString.h"

namespace vm {

struct Result {
    bool success;
    std::optional<std::unique_ptr<NekoBase*>> obj;
    ObjectType type;
};

class NekoStack {

private:
    stack<ObjectType> stackTypes;
    stack<std::unique_ptr<NekoBase*>> _stack;
    std::mutex _mutex;

public:

    template<typename T>
    void add(T obj, ObjectType type) {
        constexpr auto& typeInfo = typeid(T);
        if constexpr (std::is_same<T, NekoBase>::value) {
            auto n = static_cast<NekoBase>(obj);
            _stack.emplace(std::move(std::make_unique<NekoBase*>(n)));
            stackTypes.emplace(type);
            return;
        } else if constexpr (std::is_arithmetic<T>::value) {
            auto num = static_cast<long double>(obj);
            _stack.emplace(std::move(std::make_unique<NekoBase*>(new NekoNumber(num))));
            stackTypes.emplace(type);
            return;
        } else if constexpr (std::is_same<T, string>::value) {
            auto str = static_cast<string>(obj);
            _stack.emplace(std::move(std::make_unique<NekoBase*>(new NekoString(str))));
            stackTypes.emplace(type);
            return;
        } else if constexpr (std::is_same<T, const char *>::value) {
            _stack.emplace(std::make_unique<NekoBase*>(new NekoString(obj)));
            stackTypes.emplace(type);
            return;
        }
        cerr << "Error: NekoStack: Unknown type: " << typeInfo.name() << "\n";
        exit(1);
    }

    bool has();
    size_t count();
    Result pop();
    void clear();
    void process();

    std::unique_ptr<long double> popNumber();
    std::unique_ptr<string> popString();

};
}

#endif //NEKO_STACK_H