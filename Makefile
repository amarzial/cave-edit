all:
	g++ --std=c++14 -o libcaveedit.so src/*.cpp -shared -fPIC
