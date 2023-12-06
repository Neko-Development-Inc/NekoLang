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
        using TT = std::decay_t<T>;
        constexpr auto& typeInfo = typeid(TT);
        if constexpr (std::is_same<TT, NekoBase*>::value) {
            auto n = static_cast<NekoBase*>(obj);
            _stack.emplace(std::move(&n));
            stackTypes.emplace(type);
            return;
        } else if constexpr (std::is_arithmetic<TT>::value) {
            auto num = static_cast<long double>(obj);
            _stack.emplace(std::make_unique<NekoBase*>(new NekoNumber(num)));
            stackTypes.emplace(type);
            return;
        } else if constexpr (std::is_same<TT, string>::value) {
            auto str = static_cast<string>(obj);
            _stack.emplace(std::make_unique<NekoBase*>(new NekoString(str)));
            stackTypes.emplace(type);
            return;
        } else if constexpr (std::is_same<TT, const char *>::value) {
            _stack.emplace(std::make_unique<NekoBase*>(new NekoString(obj)));
            stackTypes.emplace(type);
            return;
        }
        errorln("Error: NekoStack: Unknown type: ", typeInfo.name());
        exit(1);
    }

    bool has();
    size_t count();
    ObjectType peek();
    Result pop();
    void clear();
    void process();

    std::unique_ptr<string> popToString();
    std::unique_ptr<long double> popNumber();
    std::unique_ptr<string> popString();

};
}

#endif //NEKO_STACK_H