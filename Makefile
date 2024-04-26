
neo :	img_exa.cpp
	../yinyang/llvm/build/bin/clang++  -o neo -I/home/regaltos/dev/llvm_dev/yinyang/frontend/Interfaces img_exa.cpp -ljpeg -lpng -Wall
clean:
	rm neo 

