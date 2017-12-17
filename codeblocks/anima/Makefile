all:
	g++ -o anima main.cpp -lSDL
	./anima
win:
	mingw32-g++.exe -Wall -O2 -IC:\Users\Любовь\plastic_laboratory\LIBS\SDL-1.2.15\include -c main.cpp -o main.o
	mingw32-g++.exe -LC:\Users\Любовь\plastic_laboratory\LIBS\SDL-1.2.15\lib -o main.exe main.o  -s  -lmingw32 -lSDLmain -lSDL.dll -luser32 -lgdi32 -lwinmm -ldxguid