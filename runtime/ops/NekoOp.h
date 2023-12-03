#pragma once

#include "../../headers.h"
#include "../vm/NekoStack.h"

namespace ops {
class NekoOp {
public:
    const short opcode;
    vector<any> args;
    explicit NekoOp(const short op) : opcode(op) { }
    explicit NekoOp(const NekoOp& op) : opcode(op.opcode) { }
    void addArg(any arg) { args.emplace_back(arg); }
    virtual unique_ptr<NekoOp> clone() const = 0;
    virtual void execute(Runtime&, NekoStack&) = 0;
    void debugArguments() {
        cout << "\targs count: " << args.size() << "\n";
        for (auto arg: args) {
            if (arg.has_value()) {
                const auto& argType = arg.type();
                if (argType == typeid(int))
                    cout << "\t" << std::any_cast<int>(arg) << " (int)\n";
                else if (argType == typeid(string))
                    cout << "\t" << std::any_cast<string>(arg) << " (string)\n";
                else if (argType == typeid(const char*))
                    cout << "\t" << std::any_cast<const char*>(arg) << " (const char *)\n";
                else if (argType == typeid(bool))
                    cout << "\t" << (std::any_cast<bool>(arg) ? "true" : "false") << " (bool)\n";
                else
                    cout << "\t" << "unknown" << "\n";
            } else
                cout << "\t" << "null" << "\n";
        }
    }
    virtual ~NekoOp() = default;
};
}