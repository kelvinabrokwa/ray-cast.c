all:
	make build
build:
	gcc rc.c vec.c -lm -o rc
example:
	make build && ./rc < example/sample_in.txt > sample_out.ppm

