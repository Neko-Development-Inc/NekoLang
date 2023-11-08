#include "NekoStack.h"

#include "../types/NekoNumber.h"
#include "../../utils/utils.h"

using std::get,
      types::ObjectType,
      types::NekoObject,
      types::NekoNumber;

typedef NekoObject<any> NEKO_OBJ;

namespace vm {

    void NekoStack::add(const std::any& obj, ObjectType type) {
        stackTypes.emplace(type);
        stack.emplace(obj);
    }

    constexpr bool NekoStack::has() {
        return !stack.empty();
    }

    result NekoStack::pop() {
        if (!has())
            return result { false,
                nullptr, nullptr,
                nullptr, ObjectType::NONE
            };

        auto type = stackTypes.top();
        auto item = stack.top();

        stackTypes.pop();
        stack.pop();

        switch (type) {
            case ObjectType::NUMBER:
                return result { true,
                    &item, any_cast<NekoNumber*>(item),
                    nullptr, type
                };
            case ObjectType::STRING:
                return result { true,
                    &item, nullptr,
                    any_cast<string>(&item), type
                };
            default: ;
        }

        return result { false,
            &item, nullptr,
            nullptr, ObjectType::UNKNOWN
        };
    }

    void NekoStack::process() {
        while (true) {
            auto result = pop();
            if (!result.success) break;
            if (result.type == ObjectType::NUMBER)
                println(string("Number: ").append(to_string(result.number->get())));
            else if (result.type == ObjectType::STRING)
                println(string("String: '").append(*result.str).append("'"));
        }
    }

    types::NekoNumber* NekoStack::popNumber() {
        auto result = pop();
        if (result.success && result.type == ObjectType::NUMBER)
            return result.number;
        return nullptr;
    }

    string* NekoStack::popString() {
        auto result = pop();
        if (result.success && result.type == ObjectType::STRING)
            return result.str;
        return nullptr;
    }

}