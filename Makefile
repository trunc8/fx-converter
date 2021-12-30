default: build

build: clean
	g++ -Wall -o fx main.cpp utils.cpp -lcurl

clean:
	rm -rf fx 

test: build
	./fx 
