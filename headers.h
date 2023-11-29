#pragma once

#ifndef HEADERS_H
#define HEADERS_H

// ALL HEADERS IN THE ENTIRE PROJECT

// DEFAULT LIBS
#include <any>
#include <map>
#include <cmath>
#include <mutex>
#include <stack>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <cstdlib>
#include <variant>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

// < USING ===========
using std::unique_ptr,
      std::make_pair,
      std::to_string,
      std::vector,
      std::string,
      std::stack,
      std::cout,
      std::map,
      std::any;
// USING =========== >

// < FORWARD DECLARATIONS
namespace runtime {
    class Runtime;
}
namespace ops {
    class Opcodes;
    class NekoOp;
    class NekoOpNop;
    class NekoOpReturn;
}
namespace compiler {
    class Compiler;
    class Reader;
    struct WhatResult;
}
namespace vm {
    struct Result;
    class NekoStack;
    class NekoClass;
    class NekoFunction;
}
namespace types {
    class NekoBase;
    class NekoNumber;
    class NekoString;
}
// FORWARD DECLARATIONS >

// < USING FORWARD DECLARATIONS
using namespace ops;
using namespace runtime;
using namespace compiler;
using namespace types;
using namespace vm;
// USING FORWARD DECLARATIONS >

// < NORMAL HEADERS
#include "common/opcodes.h"
// NORMAL HEADERS >

#endif //HEADERS_H