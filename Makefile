flags=-Wall -std=c++11
comp=g++
prog=fobias

comp:$(prog)

exe:$(prog)
	./$(prog)

$(prog): main.o
	$(comp) main.o -o $(prog) $(flags)

main.o: main.cpp
	$(comp) -c main.cpp $(flags)

clean:
	rm -f *~
	rm -f *.o
	rm -f $(prog)
	rm -f core*