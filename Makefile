.PHONY: dependencies build

dependencies:
	@echo No dependencies yet

build:
	gcc main.c -o main -g3 -Wall
	@echo Successfully built!

clean:
	rm main.c
	rm -rf headers/
	rm -rf src/
	rm -rf test/