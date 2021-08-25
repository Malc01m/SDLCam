#Build directory
dir:
	mkdir -p ./build

#Main
main.o: main.cpp
	g++ -c -Wall -Wextra main.cpp -o ./build/main.o

#Shaders
shader.o: shader/shader.cpp
	g++ -c -Wall -Werror -Wextra shader/shader.cpp -o ./build/shader.o

shaderprogram.o: shader/shaderprogram.cpp
	g++ -c -Wall -Werror -Wextra shader/shaderprogram.cpp -o ./build/shaderprogram.o

source.o: shader/source.cpp
	g++ -c -Wall -Werror -Wextra shader/source.cpp -o ./build/source.o

#Polys
poly.o: poly/poly.cpp
	g++ -c -Wall -Werror -Wextra poly/poly.cpp -o ./build/poly.o

#Compile
compile: dir main.o shader.o shaderprogram.o source.o poly.o
	g++ -Wall -Werror -Wextra ./build/main.o ./build/shader.o ./build/shaderprogram.o ./build/source.o ./build/poly.o -o ./build/Traveller -lSDL2 -lGLEW -lGLU -lGL

clean:
	rm ./build/*