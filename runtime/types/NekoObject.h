#pragma once

#ifndef NEKO_OBJECT_H
#define NEKO_OBJECT_H

#include "../../headers.h"

namespace types {
    enum ObjectType {
        T_NONE = 0,
        T_UNKNOWN = 1,
        T_NUMBER = 2,
        T_STRING = 3
    };

    class NekoBase {
    public:
        virtual ~NekoBase() = default;
    };

    template <class T>
    class NekoObject : public NekoBase {

    protected:
        T value;

    public:
        explicit NekoObject(T t) :
            value(t) { }

        virtual T get();
        virtual void set(T);

        static std::string typeString() {
            const auto& type = typeid(T);
            if (type == typeid(ObjectType::T_NUMBER))
                return "Number";
            if (type == typeid(ObjectType::T_STRING))
                return "String";
            return "Unknown";
        }

    };

    template<class T>
    void NekoObject<T>::set(T) {
        // By default, do nothing
    }

    template<class T>
    T NekoObject<T>::get() {}
}

#endif //NEKO_OBJECT_H