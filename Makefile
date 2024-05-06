
CUR_DIR = .
INC_DIR = $(CUR_DIR)/../yinyang/frontend/Interfaces
BIN_DIR = $(CUR_DIR)/../yinyang/llvm/build/bin/
LD_FLAGS = -ljpeg -lpng -Wall
neo :	img_exa.cpp
	$(BIN_DIR)/clang++ -I$(INC_DIR) -DBUDDY_ENABLE_OPENCV `pkg-config --cflags --libs opencv4` $^ -o $@ $(LD_FLAGS)
c:
	rm neo 

