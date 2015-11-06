#include <iostream>
#include <stdlib.h> //for malloc()
#include "BigIntVector.h"

using namespace std;

// copy constructor
BigIntVector::BigIntVector(BigIntVector const& orig)
	: vectorArray(orig.vectorArray)
	, vectorSize(orig.vectorSize)
{
	//this->data = orig.data;

	//orig = bigIntVector;

	//*this = orig;
	//cout << "vector copy called" << endl;
}

//default constructor
BigIntVector::BigIntVector()
{
	vectorSize = 1;

	vectorArray = (long *)malloc(10 * sizeof(long));
	for (long i = 0; i < 10; i++) vectorArray[i] = 0;
}

//constructor that initializes a custom size for vector
BigIntVector::BigIntVector(long initialSize)
{
	vectorSize = initialSize;

	vectorArray = (long *)malloc(initialSize*sizeof(long));
	for (long i = 0; i < initialSize; i++) vectorArray[i] = 0;
}

long BigIntVector::getSize() const
{
	return vectorSize;
}

void BigIntVector::resize() {

	long *oldArray = vectorArray;

	vectorArray = new long[vectorSize + 1];
	//copy old array after new slot allocated in front
	for (int k = 1; k < vectorSize + 1; k++) {
		vectorArray[k] = oldArray[k - 1]; //k-1 because old array is behind one index
	}

	vectorSize = vectorSize + 1;

	delete[] oldArray;
}


long BigIntVector::operator [](long i)
{
	return vectorArray[i];
}

long BigIntVector::getElementAt(long value) const
{
	return vectorArray[value];
}

void BigIntVector::setElementAt(long index, long value)
{
	vectorArray[index] = value;
}


void BigIntVector::removeElementAt(long index)
{
	for (long i = index; i < vectorSize; i++)
	{
		vectorArray[i] = vectorArray[i + 1];
	}

	vectorArray[vectorSize - 1] = 0;
}
