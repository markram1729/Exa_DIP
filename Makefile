
CUR_DIR = .
INC_DIR = $(CUR_DIR)/../yinyang/frontend/Interfaces
CXX_DIR = $(CUR_DIR)/../yinyang/llvm/build/bin/
LD_FLAGS = -ljpeg -lpng -Wall
neo :	img_exa.cpp
	$(CXX_DIR)/clang++ -I$(INC_DIR)  $^ -o $@ $(LD_FLAGS)
c:
	rm neo 

