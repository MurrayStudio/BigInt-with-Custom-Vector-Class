//Author: Shamus Murray

/****************************************************************
* BigIntVector.cpp -- custom vector class for BigInt
****************************************************************/

#include <iostream>
#include "BigIntVector.h"

using namespace std;

// copy constructor
BigIntVector::BigIntVector(BigIntVector const& orig)
	: vectorSize(orig.vectorSize)
{
	vectorArray = new int[orig.vectorSize];

	//copy orig array into copy array
	for (int i = 0; i < vectorSize; i++) {
		vectorArray[i] = orig.vectorArray[i];
	}
}

//destructor 
BigIntVector::~BigIntVector() {
	delete[] vectorArray;
}

//default constructor
BigIntVector::BigIntVector()
{
	vectorSize = 1; //only have one slot available upon initilization

	vectorArray = new int[vectorSize];
	for (int i = 0; i < vectorSize; i++) {
		vectorArray[i] = 0; //assign 0 to slot
	}
}

//constructor that initializes a custom size for vector
BigIntVector::BigIntVector(int initialSize)
{
	vectorSize = initialSize;

	vectorArray = new int[vectorSize];
	for (int i = 0; i < initialSize; i++) {
		vectorArray[i] = 0;
	}
}

//get current size of vector
int BigIntVector::getSize() const
{
	return vectorSize;
}

//increases vector capacity by 1
void BigIntVector::resizePlusOne() {

	int *oldArray = vectorArray;

	vectorArray = new int[vectorSize + 1];
	//copy old array after new slot allocated in front
	for (int k = 1; k < vectorSize + 1; k++) {
		vectorArray[k] = oldArray[k - 1]; //k-1 because old array is behind one index
	}

	vectorArray[0] = 0; //init first spot to 0 instead of garbage memory

	vectorSize = vectorSize + 1; //new size is + 1

	delete[] oldArray; //delete old array
}

//decreases vector capacity by 1
void BigIntVector::resizeMinusOne() {

	int *oldArray = vectorArray;

	vectorArray = new int[vectorSize - 1];
	//copy old array minus one at end
	for (int k = 1; k < vectorSize; k++) {
		vectorArray[k - 1] = oldArray[k]; //end will be popped off
	}

	vectorSize = vectorSize - 1; //new size is - 1

	delete[] oldArray; //delete old array
}

//allows use of [] on vectors
int BigIntVector::operator [](int index)
{
	return vectorArray[index];
}

//return element at index provided
int BigIntVector::getElementAt(int index) const
{
	return vectorArray[index];
}

//set element value at index provided
void BigIntVector::setElementAt(int index, int value)
{
	vectorArray[index] = value;
}

//print contents of vector
ostream& operator<<(std::ostream& os, const BigIntVector& vct)
{
	for (int i = 0; i < vct.vectorSize; i++)
		os << vct.vectorArray[i];
	return os;
}
