assemble: main.o readMips.o
	g++ main.o readMips.o -o assemble

main.o: main.cpp
	g++ -c main.cpp

readMips.o: readMips.cpp readMips.h
	g++ -c readMips.cpp

clean:
	rm *.o assemble