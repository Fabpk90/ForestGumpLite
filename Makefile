run: install
	./ForestGumpLite

install:
	sudo apt-get install libsfml-dev
	cmake .&& make
