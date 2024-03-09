#include "NekoOp.h"

class ops::NekoOpOut : public NekoOp {

public:
    explicit NekoOpOut(Opcodes& ops)
            : NekoOp(OUT, ops) {}

    explicit NekoOpOut(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpOut>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpOut");
        auto size = s.count();
        auto a = s.pop();
        if (!a.success) {
            errorln("Error: NekoOpOut: Failed to pop from stack. (Size: ", size, ")");
            exit(1);
        }
        if (!a.obj.has_value()) {
            errorln("Error: NekoOpOut: Optional was empty");
            exit(1);
        }
        bool isErr = (opcode == ops[ERR] || opcode == ERR_ALL);
        bool doFlush = false;
        if (!args.empty()) {
            auto first = args[0];
            if (!first.has_value()) {
                errorln("Error: NekoOpOut args was empty");
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(bool)) {
                errorln("Error: NekoOpOut args[0] wasn't a bool, ",
                        "it was: '", type.name(), "'");
                exit(1);
            }
            doFlush = std::any_cast<bool>(first);
        }
        if (a.type == ObjectType::T_NUMBER) {
            auto num = dynamic_cast<NekoNumber*>(*a.obj->get())->get();
            if (!isErr) {
                println(num);
                if (doFlush) flushOut();
            } else {
                errorln(num);
                if (doFlush) flushErr();
            }
        } else if (a.type == ObjectType::T_STRING) {
            auto str = dynamic_cast<NekoString*>(*a.obj->get())->get();
            if (!isErr) {
                println(str);
                if (doFlush) flushOut();
            } else {
                errorln(str);
                if (doFlush) flushErr();
            }
        }
        return CONTINUE_EXECUTION;
    }

};
}