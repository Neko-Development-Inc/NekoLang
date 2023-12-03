#include "NekoStack.h"

namespace vm {

    bool NekoStack::has() {
        return !_stack.empty();
    }

    size_t NekoStack::count() {
        return _stack.size();
    }

    Result NekoStack::pop() {
        if (!has())
            return Result { false,
                nullptr,
               ObjectType::T_NONE
            };

        auto& type = stackTypes.top();
        auto item = std::move(_stack.top());

        stackTypes.pop();
        _stack.pop();

        return Result { true,
            std::move(item),
            type
        };
    }

    void NekoStack::process() {
        while (true) {
            auto result = pop();
            if (!result.success) break;
            if (result.type == ObjectType::T_NUMBER) {
                auto num = reinterpret_cast<NekoNumber*>(result.obj->get());
                cout << "Number: " << num->get() << "\n";
            }
            else if (result.type == ObjectType::T_STRING) {
                auto str = reinterpret_cast<string*>(result.obj->get());
                cout << "String: '" << *str << "'\n";
            }
        }
    }

    std::unique_ptr<long double> NekoStack::popNumber() {
        auto result = pop();
        cout << "popNumber: " << result.type << "\n";
        if (result.success && result.type == ObjectType::T_NUMBER) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoNumber*>(*(&opt->value())->get());
                return std::make_unique<long double>(s->get());
            }
            cout << "popNumber: no value\n";
        }
        return nullptr;
    }

    std::unique_ptr<string> NekoStack::popString() {
        auto result = pop();
        if (result.success && result.type == ObjectType::T_STRING) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoString*>(*(&opt->value())->get());
                return std::make_unique<string>(s->get());
            }
            cout << "popString: no value\n";
        }
        return nullptr;
    }

}