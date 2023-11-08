#pragma once
#ifndef NEKO_OBJECT_H
#define NEKO_OBJECT_H

#include <cstdlib>
#include <any>
#include <string>

namespace types {
    enum ObjectType {
        NONE,
        UNKNOWN,
        NUMBER,
        STRING,
    };

    template <class T>
    class NekoObject {

    protected:
        T value;

    public:
        explicit NekoObject(T t) :
            value(t) { }

        virtual T get();
        virtual void set(T);

        static std::string typeString(ObjectType type) {
            if (type == ObjectType::NUMBER)
                return "Number";
            if (type == ObjectType::STRING)
                return "String";
            return "Unknown";
        }

    };

    template<class T>
    void NekoObject<T>::set(T) {
        // By default, do nothing
    }

    template<class T>
    T NekoObject<T>::get() {
        return 0;
    }
}

#endif //NEKO_OBJECT_H