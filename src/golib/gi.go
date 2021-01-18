package main

/*
 #cgo LDFLAGS: -L${SRCDIR}/../.. -lci
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <dlfcn.h>
 extern char *capture(const char *input, int len);
*/
import "C"

//export Capture
func Capture(input *C.char, len C.int) *C.char {
	inputString := C.GoString(input)
	filePath := C.capture(C.CString(inputString), len)
	return filePath
}

func main() {}
