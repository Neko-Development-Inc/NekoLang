#pragma once

#ifndef HEADERS_H
#define HEADERS_H

// ALL HEADERS IN THE ENTIRE PROJECT

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
    class NekoOpConcat;
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
}
namespace vm {
    struct Result;
    class NekoStack;
    class NekoClass;
    class NekoFunction;
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