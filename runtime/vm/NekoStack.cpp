#include "NekoStack.h"

namespace vm {

    bool NekoStack::has() {
        return !_stack.empty();
    }

    size_t NekoStack::count() {
        return _stack.size();
    }

    ObjectType NekoStack::peek() {
        if (!has()) return T_NONE;
        return stackTypes.top();
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

    void NekoStack::clear() {
        while (!_stack.empty())
            _stack.pop();
    }

    void NekoStack::process() {
        while (true) {
            auto result = pop();
            if (!result.success) break;
            if (result.type == ObjectType::T_NUMBER) {
                auto num = reinterpret_cast<NekoNumber*>(*result.obj->get());
                cout << "Number: " << num->get() << "\n";
            }
            else if (result.type == ObjectType::T_STRING) {
                auto str = reinterpret_cast<NekoString*>(*result.obj->get());
                cout << "String: '" << str->get() << "'\n";
            }
        }
    }

    std::unique_ptr<string> NekoStack::popToString() {
        auto result = pop();
        if (!result.success)
            return nullptr;
        if (result.type == ObjectType::T_NUMBER) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoNumber*>(*(&opt->value())->get());
                return std::make_unique<string>(to_string(s->get()));
            }
        } else if (result.type == ObjectType::T_STRING) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoString*>(*(&opt->value())->get());
                return std::make_unique<string>(s->get());
            }
        }
        return nullptr;
    }

    std::unique_ptr<long double> NekoStack::popNumber() {
        auto result = pop();
        if (result.success && result.type == ObjectType::T_NUMBER) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoNumber*>(*(&opt->value())->get());
                return std::make_unique<long double>(s->get());
            }
            cerr << "popNumber: no value\n";
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
            cerr << "popString: no value\n";
        }
        return nullptr;
    }

}