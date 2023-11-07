cmake_minimum_required(VERSION 3.26)
project(NekoLang)

set(CMAKE_CXX_STANDARD 23)

add_executable(NekoLang main.cpp
        compiler/compiler.cpp
        compiler/compiler.h
        runtime/runtime.cpp
        runtime/runtime.h
        common/opcodes.cpp
        common/opcodes.h
        utils/utils.h
        runtime/ops/NekoOp.h
        runtime/ops/NekoOpNop.cpp)
