FLAGS=-fconcepts
MINGW=-static -static-libgcc -static-libstdc++

linux: FORCE
	g++ main.cpp $(FLAGS) -o build/uverilog2cnf

windows: FORCE
	x86_64-w64-mingw32-g++ main.cpp $(FLAGS) $(MINGW) -o build/uverilog2cnf.exe

unmapper: utils/unmapper.cpp
	g++ utils/unmapper.cpp -o unmapper

docs: FORCE
	cd doc && make
	mv doc/*.pdf build/docs/

FORCE: