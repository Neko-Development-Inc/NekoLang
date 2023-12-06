#include "NekoOp.h"

namespace ops {
class NekoOpString : public NekoOp {

public:
    explicit NekoOpString()
            : NekoOp(STRING) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpString>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpString");
        if (args.empty()) {
            errorln("Error: NekoOpString args was empty");
            exit(1);
        }
        auto first = args[0];
        if (!first.has_value()) {
            errorln("Error: NekoOpString args was empty");
            exit(1);
        }
        const auto& type = first.type();
        if (type == typeid(const char *)) {
            s.add(std::any_cast<const char *>(first), T_STRING);
            return 0;
        } else if (type == typeid(string)) {
            s.add(any_cast<string>(first), T_STRING);
            return 0;
        }
        errorln("Error: NekoOpString args[0] wasn't a string, ",
                "it was: '", type.name(), "'");
        exit(1);
    }

};
}