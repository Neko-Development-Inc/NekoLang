#pragma once

#ifndef NEKO_STACK_H
#define NEKO_STACK_H

#include "../../headers.h"

#include "../types/NekoObject.h"
#include "../types/NekoNumber.h"
#include "../types/NekoString.h"

namespace vm {

//    class Parent {
//    public:
//        Parent(const std::string& name) : name(name) {}
//
//        std::string getName() const {
//            return name;
//        }
//
//    private:
//        std::string name;
//    };
//
//    class Child : public Parent {
//    public:
//        Child(const std::string& name, int additionalProperty) : Parent(name), additionalProperty(additionalProperty) {}
//
//        int getAdditionalProperty() const {
//            return additionalProperty;
//        }
//
//    private:
//        int additionalProperty;
//    };
//
//    int testt() {
//        std::stack<std::unique_ptr<NekoBase*>> stk;
//        stk.push(std::move(std::make_unique<NekoBase*>(new NekoString("Hello"))));
//        stk.push(std::move(std::make_unique<NekoBase*>(new NekoString("World"))));
//    }

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
        if constexpr (std::is_arithmetic<T>::value) {
            auto num = static_cast<long double>(obj);
            _stack.emplace(std::move(std::make_unique<NekoBase*>(new NekoNumber(num))));
            stackTypes.emplace(type);
            return;
        } else if constexpr (typeInfo == typeid(string)) {
            auto str = static_cast<string>(obj);
            _stack.emplace(std::move(std::make_unique<NekoBase*>(new NekoString(str))));
            stackTypes.emplace(type);
            return;
        } else if constexpr (typeInfo == typeid(const char *)) {
            auto str = reinterpret_cast<const char *>(obj);
            _stack.emplace(std::make_unique<NekoBase*>(new NekoString(str)));
            stackTypes.emplace(type);
            return;
        }
        cout << "NekoStack: Unknown type: " << typeInfo.name() << "\n";
    }

    bool has();
    size_t count();
    Result pop();
    void process();

    std::unique_ptr<long double> popNumber();
    std::unique_ptr<string> popString();

};
}

#endif //NEKO_STACK_H