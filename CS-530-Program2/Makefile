xed: main.o xed.o opcode.o
	g++ main.o xed.o opcode.o -o xed 

main.o: main.cpp xed.h
	g++ -c main.cpp

xed.o:	xed.cpp xed.h opcode.h
	g++ -c xed.cpp

opcode.o: opcode.cpp opcode.h
	g++ -c opcode.cpp

clean: 
	rm *.o xed
