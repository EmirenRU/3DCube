make: 
	cd build && cmake .. && make

execute: 
	build/opengl-proj

.all:
	make && execute

.PHONY: make execute