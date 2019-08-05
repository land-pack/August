all:
	@mkdir build
	@gcc -o  ./build/main src/main.c

debug:
	@gcc -g -o  ./build/main src/main.c

run:
	@./build/main

clean:
	@rm -rf ./build/*
