# MIT License
#
# Copyright (c) 2023 Matthias Rozanski
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.24)
project(vaatv)

set(CMAKE_CXX_STANDARD 23)

add_executable(vaatv
    main.cpp
    src/concepts.h
    src/type_traits.h
    src/devices.h
    src/device_manager.h
    src/device_manager_base.h
)

target_compile_options(vaatv PRIVATE
    # CXX Warnings
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Wpedantic>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-Wshadow>
    $<$<COMPILE_LANGUAGE:CXX>:-Wpointer-arith>
    $<$<COMPILE_LANGUAGE:CXX>:-Wconversion>
    $<$<COMPILE_LANGUAGE:CXX>:-Wsign-conversion>
    $<$<COMPILE_LANGUAGE:CXX>:-Wformat-security>
    # CXX Debug
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>:-g3>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>:-Og>
    # CXX Release
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>:-O3>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>:-DNDEBUG>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>:-ffast-math>
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>:-funroll-loops>
    # CXX Release - Clang
    $<$<AND:$<COMPILE_LANG_AND_ID:CXX,Clang>,$<CONFIG:RELEASE>>:-fforce-emit-vtables>
    $<$<AND:$<COMPILE_LANG_AND_ID:CXX,Clang>,$<CONFIG:RELEASE>>:-fstrict-vtable-pointers>
    # CXX Release - G++/GNU
    $<$<AND:$<COMPILE_LANG_AND_ID:CXX,GNU>,$<CONFIG:RELEASE>>:-fdevirtualize>
    $<$<AND:$<COMPILE_LANG_AND_ID:CXX,GNU>,$<CONFIG:RELEASE>>:-fdevirtualize-speculatively>
)
