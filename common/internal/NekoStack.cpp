#include "NekoStack.h"

namespace vm {

    bool NekoStack::has() {
        return size > 0;
    }

    size_t NekoStack::count() {
        return size;
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
        size--;

        return Result { true,
            std::move(item), type
        };
    }

    void NekoStack::clear() {
        while (!_stack.empty())
            _stack.pop();
        size = 0;
    }

    void NekoStack::process() {
        while (has()) {
            auto result = peek();
            if (result == T_NONE || result == T_UNKNOWN) break;
            if (result == T_NUMBER) println(*popNumber());
            else if (result == T_STRING) println(*popString());
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
            errorln("popNumber: no value");
        } else if (result.type == ObjectType::T_STRING) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoString*>(*(&opt->value())->get());
                return std::make_unique<string>(s->get());
            }
            errorln("popString: no value");
        } else if (result.type == ObjectType::T_BOOL) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto b = dynamic_cast<NekoBool*>(*(&opt->value())->get());
                return std::make_unique<string>(to_string(b->get()));
            }
            errorln("popBool: no value");
        }
        return nullptr;
    }

    std::unique_ptr<_NekoNumberType_> NekoStack::popNumber() {
        auto result = pop();
        if (result.success && result.type == ObjectType::T_NUMBER) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoNumber*>(*(&opt->value())->get());
                return std::make_unique<_NekoNumberType_>(s->get());
            }
            errorln("popNumber: no value");
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
            errorln("popString: no value");
        }
        return nullptr;
    }

    std::unique_ptr<bool> NekoStack::popBool() {
        auto result = pop();
        if (result.success && result.type == ObjectType::T_BOOL) {
            auto opt = &result.obj;
            if (opt->has_value()) {
                auto s = dynamic_cast<NekoBool*>(*(&opt->value())->get());
                return std::make_unique<bool>(s->get());
            }
            errorln("popString: no value");
        }
        return nullptr;
    }

}