cmake_minimum_required(VERSION 3.16)
project(RollRama)

if(UNIX)
message(STATUS "WARNING: This project cannot be compiled on Unix systems at the moment.")
return()
endif(UNIX)

if(WIN32)
set(DEVKITPATH C:/devkitPro)
set(CODEWARRIOR ./tools)
endif(WIN32)

set(CW_CC ${CODEWARRIOR}/mwcceppc.exe)
set(C_FLAGS -I- -i ./src -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0)