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

set(CXX_FILES src/seq/SequenceTiltStart.cpp src/scn/SceneStart.cpp src/scn/Chowder.cpp src/scn/game/PlayerController.cpp src/scn/game/StageController.cpp)
set(OBJ_FILES SequenceTiltStart.o SceneStart.o Chowder.o PlayerController.o StageController.o)

set(CXX_FLAGS -i ./src -RTTI off -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c)
set(LD_FLAGS -g -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float -nodefaultlibs -nostartfiles -Wl,--no-check-sections -T ld/main.ld -I ./)

add_custom_target(Roll ALL)
add_custom_command(
	TARGET Roll
	COMMAND ${CW_CC} ${CXX_FLAGS} ${CXX_FILES}
	COMMAND ${DKP_AS_TOOL} asm/link.s -o link.o
	COMMAND ${DKP_AS_TOOL} asm/hook.s -o hook.o
	COMMAND ${DKP_C_COMP} ${LD_FLAGS} link.o hook.o ${OBJ_FILES} -o ./build/main.elf
	COMMAND python tools/adjust_section_offsets.py build/main.elf
	COMMAND ${DKP_OBJCOPY} -O binary build/main.elf ./build/main.dol
)