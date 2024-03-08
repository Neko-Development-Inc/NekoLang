cmake_minimum_required(VERSION 3.22)
project(NekoLang)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wno-unused-parameter -Wno-unused-variable")
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
        runtime/ops/NekoOpLabel.cpp
        runtime/ops/NekoOpReturn.cpp

        runtime/types/NekoObject.h
        runtime/types/NekoNumber.cpp
        runtime/types/NekoNumber.h
        runtime/types/NekoString.cpp
        runtime/types/NekoString.h
        runtime/types/NekoBool.cpp
        runtime/types/NekoBool.h

        common/internal/NekoFunction.cpp
        common/internal/NekoFunction.h
        common/internal/NekoBox.cpp
        common/internal/NekoBox.h
        common/internal/NekoStack.cpp
        common/internal/NekoStack.h

        common/files/NekoWriter.cpp
        common/files/NekoWriter.h
        common/files/NekoReader.cpp
        common/files/NekoReader.h
        common/files/NekoFile.cpp
        common/files/NekoFile.h

        headers.h
        utils.h

        common/libs/miniz/miniz.c
        common/libs/miniz/miniz.h)
