.PHIONY:
all: cpp_print test myshell 
myshell: myshell.c
	gcc $^ -o $@ 
cpp_print: cpp_print.cpp
	g++ $^ -o $@
test: test.c
	gcc $^ -o $@
.PHIONY:
clean:
	rm -rf test cpp_print myshell
