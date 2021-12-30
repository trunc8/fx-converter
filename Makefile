default: build

build: clean
	g++ -Wall -o fx main.cpp utils.cpp -lcurl

debug: clean
	g++ -Wall -g -o fx main.cpp utils.cpp -lcurl
	gdb -tui fx

clean:
	rm -rf fx 

test: build
	./fx 
