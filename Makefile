default:
	clang++ -std=c++17 -g -O3 src/*.cpp 

llvm:
	clang++ -std=c++17 -g -O3 src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` 
