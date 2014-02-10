all:
	g++ -o raytracer -g main.cpp -lglut -lGL -lGLU
	
image:
	mogrify -flip -format ppm images/frame.ppm

clean:
	rm -rf raytracer
	rm -rf images/frame.ppm
