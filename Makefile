run: compile
	./test.ha

compile:
	g++ src/main.cpp src/actors/actor.cpp -o test.ha -lsfml-graphics -lsfml-window -lsfml-system

install:
	sudo apt-get install libsfml-dev