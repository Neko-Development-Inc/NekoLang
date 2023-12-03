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

    void addArg(any arg) {
        args.emplace_back(arg);
    }

    long double getArgNumber(int n = 0) {
        const auto& type = args[n].type();
        if (type == typeid(int))
            return std::any_cast<int>(args[n]);
        else if (type == typeid(long))
            return std::any_cast<long>(args[n]);
        else if (type == typeid(double))
            return std::any_cast<double>(args[n]);
        else if (type == typeid(long double))
            return std::any_cast<long double>(args[n]);
        else if (type == typeid(long long))
            return std::any_cast<long long>(args[n]);
        else if (type == typeid(long long int))
            return std::any_cast<long long int>(args[n]);
    }

    string getArgString(int n = 0) {
        return std::any_cast<string>(args[n]);
    }

    bool hasArg(int n = 0) {
        if (args.empty()) return false;
        return n < args.size();
    }

    bool argIsType(int n, const std::type_info& type) {
        const any& obj = args[n];
        return obj.type() == type;
    }

    virtual unique_ptr<NekoOp> clone() const = 0;

    virtual long int execute(Runtime&, NekoStack&, size_t&) = 0;

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