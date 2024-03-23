run:
	@gcc -o main main.cpp `sdl2-config --cflags --libs`
#	@gcc -o main main.cpp -I /usr/include/SDL2/ -lSDL2
	@chmod +x main
	@./main
