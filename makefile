all: test

test: main.o BigInt.o BigIntVector.o	
	g++ -o test main.o BigInt.o BigIntVector.o

main.o: main.cpp BigInt.h BigIntVector.h
	g++ -c main.cpp

BigInt.o: BigInt.cpp BigInt.h BigIntVector.h
	g++ -c BigInt.cpp
    
BigIntVector.o: BigIntVector.cpp BigIntVector.h
    g++ -c BigIntVector.cpp 

clean:
	rm -f main.o BigInt.o BigIntVector.o test
