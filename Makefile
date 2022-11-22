default:
	clang++ -std=c++17  src/*.cpp -o cool

f: # format
	clang-format -i src/*.cpp src/*.h

formatall:
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

debug:
	clang++ -std=c++17 -g -03 src/*.cpp -o cool

llvm:
	clang++ -std=c++17 -g -O3 src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o cool
