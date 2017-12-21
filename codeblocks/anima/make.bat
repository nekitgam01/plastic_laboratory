del anima.exe
del obj\main.o
del obj\graph.o
#mingw32-g++.exe -Wall -O2 -IC:\Users\Любовь\plastic_laboratory\LIBS\SDL-1.2.15\include -c main.cpp -o obj\main.o
#mingw32-g++.exe -LC:\Users\Любовь\plastic_laboratory\LIBS\SDL-1.2.15\lib -o anima.exe obj\main.o  -s  -lmingw32 -lSDLmain -lSDL.dll -luser32 -lgdi32 -lwinmm -ldxguid

mingw32-g++.exe -Wall -O2 -IC:\SDL-1.2.15\include -c main.cpp -o obj\main.o
mingw32-g++.exe -Wall -O2 -IC:\SDL-1.2.15\include -c graph.cpp -o obj\graph.o
mingw32-g++.exe -LC:\SDL-1.2.15\lib -o anima.exe obj\main.o obj\graph.o  -s  -lmingw32 -lSDLmain -lSDL.dll -luser32 -lgdi32 -lwinmm -ldxguid

anima.exe
