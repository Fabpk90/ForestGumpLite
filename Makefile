run: compile
	./test.ha

compile:
	g++ main.cpp -o test.ha -lsfml-graphics -lsfml-window -lsfml-system

install:
	sudo apt-get install libsfml-dev