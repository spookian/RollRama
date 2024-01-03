set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

cmake_minimum_required(VERSION 3.17)
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
set(DKP_C_COMP ${DEVKITPATH}/devkitPPC/bin/powerpc-eabi-gcc)
set(DKP_AS_TOOL ${DEVKITPATH}/devkitPPC/bin/powerpc-eabi-as)
set(DKP_DOL_TOOL ${DEVKITPATH}/tools/bin/elf2dol)
set(DKP_OBJCOPY ${DEVKITPATH}/devkitPPC/bin/powerpc-eabi-objcopy)

set(C_FILES src/seq/SequenceTiltStart.cpp src/scn/SceneStart.cpp)

set(C_FLAGS -I- -i ./src -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0)
set(LD_FLAGS -g -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float -nodefaultlibs -nostartfiles -Wl,--no-check-sections -T ld/execute.ld -I ./)

add_custom_target(Roll ALL)
add_custom_command(
	TARGET Roll
	COMMAND ${DKP_AS_TOOL} asm/link.s -o link.o
	COMMAND ${DKP_AS_TOOL} asm/hook.s -o hook.o
	COMMAND ${DKP_C_COMP} ${LD_FLAGS} link.o hook.o -o ./build/RTDLBASE.elf
	COMMAND ${DKP_OBJCOPY} -O binary ./build/RTDLBASE.elf ./build/RTDLBASE.dol
)