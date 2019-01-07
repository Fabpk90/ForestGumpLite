run: install
	cd cmake-build-debug && make clean && make
	cd cmake-build-debug && cp ForestGumpLite ../ForestGumpLite
	./ForestGumpLite

install:
	sudo apt-get install libsfml-dev
	cmake .&& make

	
