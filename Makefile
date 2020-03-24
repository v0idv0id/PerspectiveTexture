
# A very NAIVE Makefile

CFLAGS=-Iinclude/ -std=c++11 -Wall -pedantic -Werror
LDFLAGS=-lglfw -ldl 

all:
	mkdir -p build/
	g++ glad/glad.c ${CFLAGS} -c -o build/glad.o
	g++ PerspectiveTexture.cpp ${CFLAGS} -c -o build/PerspectiveTexture.o
	g++ -o PerspectiveTexture build/*.o ${LDFLAGS}


clean:
	rm -f build/*.o
	rm -f PerspectiveTexture
