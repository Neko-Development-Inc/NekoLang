cmake_minimum_required(VERSION 3.22)
project(NekoLang)

set(CMAKE_CXX_STANDARD 23)

add_executable(NekoLang main.cpp
        common/opcodes.cpp
        common/opcodes.h
        compiler/compiler.cpp
        compiler/compiler.h
        compiler/reader.cpp
        compiler/reader.h
        runtime/runtime.cpp
        runtime/runtime.h
        runtime/ops/NekoOp.h
        runtime/ops/NekoOpNop.cpp
        runtime/ops/NekoOpReturn.cpp
        runtime/types/NekoObject.h
        runtime/types/NekoNumber.cpp
        runtime/types/NekoNumber.h
        runtime/types/NekoString.cpp
        runtime/types/NekoString.h
        runtime/vm/NekoFunction.cpp
        runtime/vm/NekoFunction.h
        runtime/vm/NekoClass.cpp
        runtime/vm/NekoClass.h
        runtime/vm/NekoStack.cpp
        runtime/vm/NekoStack.h
        headers.h)
