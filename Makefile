flags=-Wall -std=c++11
comp=g++
prog=problema1

comp:$(prog)

exe:$(prog)
	./$(prog)

$(prog): main.o People.o
	$(comp) main.o People.o -o $(prog) $(flags)

main.o: main.cpp People.h
	$(comp) -c main.cpp $(flags)

People.o: People.cpp People.h includes.h
	$(comp) -c People.cpp $(flags)

clean:
	rm -f *~
	rm -f *.o
	rm -f $(prog)
	rm -f core*