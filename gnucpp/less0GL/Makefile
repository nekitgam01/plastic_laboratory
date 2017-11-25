all:
	g++ -o bin/uix src/main.cpp -lSDL2 -lGL -lGLU -lglut -lSDL2_image
	./bin/uix
install:
	sudo apt-get install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
	g++ -o bin/uix src/main.cpp -lSDL2 -lGL -lGLU -lglut -lSDL2_image