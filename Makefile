all:
	g++ -o raytracer -g main.cpp -lglut -lGL -lGLU
clean:
	rm -rf raytracer
