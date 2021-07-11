cmake_minimum_required(VERSION 3.19)
project(libftl)

set(CMAKE_CXX_STANDARD 20)

add_executable(libftl main.cpp StrBuf.cpp StrBuf.h Vec.cpp Vec.h Str.cpp Str.h IntWrapper.cpp IntWrapper.h StrJoin.cpp StrJoin.h)