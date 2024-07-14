all:
	clang++ main.cpp -std=c++20 -o prog -L/opt/homebrew/lib -lSDL2 -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
