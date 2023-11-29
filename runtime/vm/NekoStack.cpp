#include "NekoStack.h"

namespace vm {

    void NekoStack::add(std::unique_ptr<NekoBase> obj, ObjectType type) {
        stackTypes.emplace(type);
        _stack.emplace(std::move(obj));
    }

    bool NekoStack::has() {
        return !_stack.empty();
    }

    int NekoStack::count() {
        return (int)_stack.size();
    }

    Result NekoStack::pop() {
        if (!has())
            return Result {false,
                           nullptr, ObjectType::T_NONE
            };

        auto type = std::move(stackTypes.top());
        auto item = std::move(_stack.top());

        stackTypes.pop();
        _stack.pop();

        return Result { true,
            std::move(item),
            std::move(type)
        };
    }

    void NekoStack::process() {
        while (true) {
            auto result = pop();
            if (!result.success) break;
            if (result.type == ObjectType::T_NUMBER) {
                auto num = reinterpret_cast<NekoNumber*>(result.obj.get());
                cout << "Number: " << num->get() << "\n";
            }
            else if (result.type == ObjectType::T_STRING) {
                auto str = reinterpret_cast<string*>(result.obj.get());
                cout << "String: '" << *str << "'\n";
            }
        }
    }

    std::unique_ptr<long double> NekoStack::popNumber() {
        auto result = pop();
        if (result.success && result.type == ObjectType::T_NUMBER) {
            auto obj = dynamic_cast<NekoNumber*>(result.obj.get());
            if (obj != nullptr)
                return std::make_unique<long double>(obj->get());
        }
        return nullptr;
    }

    std::unique_ptr<string> NekoStack::popString() {
        auto result = pop();
        if (result.success && result.type == ObjectType::T_STRING) {
            auto obj = dynamic_cast<NekoString*>(result.obj.get());
            if (obj != nullptr)
                return std::make_unique<string>(obj->get());
        }
        return nullptr;
    }

}