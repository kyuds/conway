.PHONY: all build clean

build:
	mkdir -p build
	cd build && cmake .. && cmake --build .

all: clean build

clean:
	rm -rf build
