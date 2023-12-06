cmake_minimum_required(VERSION 3.22)
project(NekoLang)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

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
        runtime/ops/NekoOpCs.cpp
        runtime/ops/NekoOpNop.cpp
        runtime/ops/NekoOpPop.cpp
        runtime/ops/NekoOpDup.cpp
        runtime/ops/NekoOpOut.cpp
        runtime/ops/NekoOpNumber.cpp
        runtime/ops/NekoOpString.cpp
        runtime/ops/NekoOpConcat.cpp
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

        headers.h
        utils.h

        common/libs/miniz/miniz.c
        common/libs/miniz/miniz.h)
