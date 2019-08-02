all:
	@gcc -o  ./build/main src/main.c

run:
	@./build/main

clean:
	@rm -rf ./build/*