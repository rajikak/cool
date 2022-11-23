default:
	clang++ -I/Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/include/c++/v1/ \
			-I/Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/include/ \
			-I/opt/homebrew/include \
			-L/Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/lib/ \
			-L/opt/homebrew/lib/ \
		-std=c++20 src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o cool
	./cool


f: # format
	clang-format -i src/*.cpp src/*.h

fall: # format all
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

debug:   
	clang++ -std=c++17 -g -03 src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o cool
