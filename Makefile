default: build

compile-c:
	gcc -c -Wall -Werror -fpic src/clib/ci.c
	gcc -shared -o libci.so ci.o

compile-go:
	go build -buildmode=c-shared -o libgi.so src/golib/gi.go

clean:
	-rm *.so *.o
	-rm -rf build

build: clean compile-c compile-go
	node-gyp configure build
