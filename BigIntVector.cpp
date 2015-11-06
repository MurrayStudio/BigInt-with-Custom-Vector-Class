#include <iostream>
#include <stdlib.h> //for malloc()
#include "BigIntVector.h"

using namespace std;

BigIntVector::BigIntVector()
{
	vectorTotalSize = 1;

	vectorArray = (long *)malloc(10 * sizeof(long));
	for (long i = 0; i < 10; i++) vectorArray[i] = 0;

	nextValue = 0;
}

BigIntVector::BigIntVector(long initialSize)
{
	vectorTotalSize = initialSize;

	vectorArray = (long *)malloc(initialSize*sizeof(long));
	for (long i = 0; i < initialSize; i++) vectorArray[i] = 0;

	nextValue = 0;
}

long BigIntVector::getSize() const
{
	return vectorTotalSize;
}

void BigIntVector::resize() {

	long *oldArray = vectorArray;

	vectorArray = new long[vectorTotalSize + 1];
	//copy old array after new slot allocated in front
	for (int k = 1; k < vectorTotalSize + 1; k++) {
		vectorArray[k] = oldArray[k-1]; //k-1 because old array is behind one index
	}

	vectorTotalSize = vectorTotalSize + 1;

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
	for (long i = index; i < vectorTotalSize; i++)
	{
		vectorArray[i] = vectorArray[i + 1];
	}

	vectorArray[vectorTotalSize - 1] = 0;
}
