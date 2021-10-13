FLAGS=-fconcepts
MINGW=-static -static-libgcc -static-libstdc++

linux: FORCE
	g++ main.cpp $(FLAGS) -o build/uverilog2cnf

windows: FORCE
	x86_64-w64-mingw32-g++ main.cpp $(FLAGS) $(MINGW) -o build/uverilog2cnf.exe

unmapper_linux: unmapper/unmapper.cpp
	g++ unmapper/unmapper.cpp -o build/unmapper

unmapper_windows: unmapper/unmapper.cpp
	x86_64-w64-mingw32-g++ unmapper/unmapper.cpp $(MINGW) -o build/unmapper.exe

docs: FORCE
	cd doc && make
	mv doc/*.pdf build/docs/

FORCE: