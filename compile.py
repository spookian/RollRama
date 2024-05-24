import os
import sys

CURRENT_PATH = os.path.split(__file__)[0]
print(CURRENT_PATH)
os.chdir(CURRENT_PATH)

DEFAULT_DKP_PATH = "C:\\devkitPro"
DEFAULT_CW_PATH = ".\\tools"
CW_CC 		    = "\\mwcceppc"
DKP_CC 		    = "\\devkitPPC\\bin\\powerpc-eabi-gcc"
DKP_AS 		    = "\\devkitPPC\\bin\\powerpc-eabi-as"
DKP_OBJCOPY     = "\\devkitPPC\\bin\\powerpc-eabi-objcopy"

CXX_FILES 	= " src\\seq\\SequenceTiltStart.cpp src\\scn\\SceneStart.cpp src\\scn\\Chowder.cpp src\\scn\\game\\PlayerController.cpp src\\scn\\game\\StageController.cpp src\\scn\\game\\SimpleRigidbody.cpp src\\g3d\\ResFileHelper.cpp src\\scn\\game\\SphereCollider.cpp src\\scn\\game\\PointStar.cpp src\\hid\\WPADReader.cpp src\\scn\\game\\StageLoader.cpp"
CXX_FLAGS 	= " -i .\\src -RTTI off -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -align mac68k4byte -c"
LD_FILES 	= " SequenceTiltStart.o SceneStart.o Chowder.o PlayerController.o StageController.o SimpleRigidbody.o ResFileHelper.o SphereCollider.o PointStar.o WPADReader.o StageLoader.o"
LD_FLAGS 	= " -g -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float -nodefaultlibs -nostartfiles -Wl,--no-check-sections -T ld\\main.ld -I .\\"

DKP_PATH 	= DEFAULT_DKP_PATH
CW_PATH 	= DEFAULT_CW_PATH

#execution
def parse_arguments():
	for n in sys.argv:
		if (n == "-dkp"):
			DKP_PATH = sys.argv[n+1]
		if (n == "-cw"):
			CW_PATH = sys.argv[n+1]
	return

parse_arguments()
print("Building...\n")
os.system(CW_PATH + CW_CC + CXX_FILES + CXX_FLAGS)
os.system(DKP_PATH + DKP_AS + " .\\asm\\link.s -o link.o")
os.system(DKP_PATH + DKP_AS + " .\\asm\\hook.s -o hook.o")
os.system(DKP_PATH + DKP_CC + LD_FLAGS + " link.o hook.o" + LD_FILES + " -o .\\build\\main.elf")
os.system("python .\\tools\\adjust_section_offsets.py .\\build\\main.elf")
os.system(DKP_PATH + DKP_OBJCOPY + " -O binary .\\build\\main.elf .\\build\\main.dol")
#cleanup
os.system("del *.o")