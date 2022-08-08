show: test.o show.o
	g++ test.o show.o -o show
test.o: test.cpp
	g++ -c test.cpp 
show.o: show.cpp
	g++ -c show.cpp
.PHONY:
c:
	rm -rf *.o show
