#pragma once

#include "../../headers.h"
#include "../../common/internal/NekoStack.h"

/**
 * NOP      - Done
 * POP      - Done
 * POP_N    - Done
 * 
 * DUP      - 
 * DUP_2    - 
 * DUP_3    - 
 * DUP_N    - 
 * DUP_ALL  - 
 * 
 * NDUP     - 
 * NDUP_2   - 
 * NDUP_3   - 
 * NDUP_N   - 
 * NDUP_ALL - 
 * 
 * CS       - 
 * 
 * LABEL    - 
 * RETURN   - 
 * JUMP     - 
 * 
 * CREATE   - 
 * TYPE     - 
 * CALL     - 
 * 
 * NUMBER   - 
 * STRING   - 
 * BOOL     - 
 * 
 * CONCAT   - 
 * CONCAT_N - 
 * CONCAT_ALL - 
 * 
 * REPEAT      - 
 * REPEAT_N    - 
 * REPEAT_LL   - 
 * REPEAT_LL_N - 
 * 
 * NREPEAT     - 
 * NREPEAT_N   - 
 * 
 * OUT       - 
 * OUT_ALL   - 
 * ERR       - 
 * ERR_ALL   - 
 * 
 */

class ops::NekoOp {
public:
    static const long long CONTINUE_EXECUTION = 0;
    static const long long HALT_EXECUTION = -1;

    const short opcode;
    vector<any> args;
    Opcodes& ops;

    explicit NekoOp(const short opcode, Opcodes& ops)
            : opcode(opcode),
              ops(ops) { }

    explicit NekoOp(const NekoOp& op)
            : opcode(op.opcode),
              ops(op.ops) { }

    virtual ~NekoOp() = default;

    void addArg(any arg) {
        args.emplace_back(arg);
    }

#define toLd(x) static_cast<_NekoNumberType_>(x)

    _NekoNumberType_ getArgNumber(int n = 0) {
        any arg = args[n];
        const auto& type = arg.type();
        if (type == typeid(int))
            return toLd(std::any_cast<int>(arg));
        else if (type == typeid(long))
            return toLd(std::any_cast<long>(arg));
        else if (type == typeid(double))
            return toLd(std::any_cast<double>(arg));
        else if (type == typeid(long double))
            return toLd(std::any_cast<long double>(arg));
        else if (type == typeid(long long))
            return toLd(std::any_cast<long long>(arg));
        else if (type == typeid(long int))
            return toLd(std::any_cast<long int>(arg));
        throw std::runtime_error("Unknown number type");
    }

    string getArgString(int n = 0) {
        return std::any_cast<string>(args[n]);
    }

    bool getArgBool(int n = 0) {
        return std::any_cast<bool>(args[n]);
    }

    bool hasArg(int n = 0) {
        if (args.empty()) return false;
        return n < (int)args.size();
    }

    bool argIsType(int n, const std::type_info& type) {
        const any& obj = args[n];
        return obj.type() == type;
    }

    // TODO: Test if cloning also clones the custom opcode (if changed)
    virtual unique_ptr<NekoOp> clone() const = 0;

    virtual _OpsNumberIndexType_ execute(Runtime&, NekoStack&, size_t&) = 0;

    void debugArguments() {
        println("\targs count: ", args.size());
        for (auto arg: args) {
            if (!arg.has_value()) {
                println("\t", "null");
                continue;
            }
            const auto& argType = arg.type();
            if (argType == typeid(int))
                println("\t", std::any_cast<int>(arg), " (int)");
            else if (argType == typeid(string))
                println("\t`", std::any_cast<string>(arg), "` (string)");
            else if (argType == typeid(const char*))
                println("\t`", std::any_cast<const char*>(arg), "` (const char *)");
            else if (argType == typeid(bool))
                println("\t", (std::any_cast<bool>(arg) ? "true" : "false"), " (bool)");
            else
                println("\t", "unknown");
        }
    }

};