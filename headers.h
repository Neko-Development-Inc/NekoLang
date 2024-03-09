#pragma once

#ifndef HEADERS_H
#define HEADERS_H

#define _NekoNumberType_ long double

// DEFAULT LIBS
#include <any>
#include <map>
#include <list>
#include <cmath>
#include <mutex>
#include <stack>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <utility>
#include <cstdlib>
#include <variant>
#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <unordered_map>

// < USING ===========
using std::unique_ptr,
      std::make_pair,
      std::to_string,
      std::vector,
      std::string,
      std::stack,
      std::list,
      std::map,
      std::any;
// USING =========== >

// < FORWARD DECLARATIONS
namespace files {
    class NekoFile;
    class NekoReader;
    class NekoWriter;
}
namespace ops {
    class Opcodes;
    class NekoOp;
    class NekoOpCs;
    class NekoOpDup;
    class NekoOpOut;
    class NekoOpNop;
    class NekoOpPop;
    class NekoOpNumber;
    class NekoOpString;
    class NekoOpBool;
    class NekoOpConcat;
    class NekoOpLabel;
    class NekoOpReturn;
}
namespace runtime {
    class Runtime;
}
namespace compiler {
    class Compiler;
    class Reader;
    struct WhatResult;
}
namespace types {
    class NekoBase;
    class NekoNumber;
    class NekoString;
    class NekoBool;
}
namespace vm {
    struct Result;
    class NekoStack;
    class NekoBox;
    class NekoFunction;
    class NekoVariable;
}
// FORWARD DECLARATIONS >

// < USING FORWARD DECLARATIONS
using namespace files;
using namespace ops;
using namespace runtime;
using namespace compiler;
using namespace types;
using namespace vm;
// USING FORWARD DECLARATIONS >

// < NORMAL HEADERS
#include "common/opcodes.h"
#include "utils.h"
// NORMAL HEADERS >

#endif //HEADERS_H