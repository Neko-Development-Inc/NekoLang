#include "NekoStack.h"

#include "../../utils/utils.h"

using std::get,
      types::ObjectType,
      types::NekoObject,
      types::NekoNumber;

namespace vm {

    void NekoStack::add(std::unique_ptr<types::NekoBase> obj, ObjectType type) {
        stackTypes.emplace(type);
        stack.emplace(std::move(obj));
    }

    constexpr bool NekoStack::has() {
        return !stack.empty();
    }

    int NekoStack::count() {
        return (int)stack.size();
    }

    Result NekoStack::pop() {
        if (!has())
            return Result { false,
               nullptr, ObjectType::NONE
            };

        auto type = std::move(stackTypes.top());
        auto item = std::move(stack.top());

        stackTypes.pop();
        stack.pop();

        return Result { true,
            std::move(item),
            std::move(type)
        };
    }

    void NekoStack::process() {
        while (true) {
            auto result = pop();
            if (!result.success) break;
            if (result.type == ObjectType::NUMBER) {
                auto num = reinterpret_cast<types::NekoNumber*>(result.obj.get());
                println(string("Number: ").append(to_string(num->get())));
            }
            else if (result.type == ObjectType::STRING) {
                auto str = reinterpret_cast<string*>(result.obj.get());
                println(string("String: '").append(*str).append("'"));
            }
        }
    }

    std::unique_ptr<long double> NekoStack::popNumber() {
        auto result = pop();
        if (result.success && result.type == types::NUMBER) {
            auto obj = dynamic_cast<types::NekoNumber*>(result.obj.get());
            if (obj != nullptr)
                return std::make_unique<long double>(obj->get());
        }
        return nullptr;
    }

    std::unique_ptr<string> NekoStack::popString() {
        auto result = pop();
        if (result.success && result.type == types::STRING) {
            auto obj = dynamic_cast<types::NekoString*>(result.obj.get());
            if (obj != nullptr)
                return std::make_unique<string>(obj->get());
        }
        return nullptr;
    }

}