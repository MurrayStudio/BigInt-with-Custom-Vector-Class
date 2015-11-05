#include <iostream>
#include <stdlib.h> //for malloc()
#include "BigIntVector.h"

using namespace std;

BigIntVector::BigIntVector()
{
	vectorTotalSize = 1;
	//Default:10
	vectorIncrementSize = 1;

	vectorArray = (long *)malloc(10 * sizeof(long));
	for (long i = 0; i < 10; i++) vectorArray[i] = 0;

	nextValue = 0;
}

BigIntVector::BigIntVector(long initialSize)
{
	vectorTotalSize = initialSize;
	vectorIncrementSize = initialSize;

	vectorArray = (long *)malloc(initialSize*sizeof(long));
	for (long i = 0; i < initialSize; i++) vectorArray[i] = 0;

	nextValue = 0;
}

BigIntVector::BigIntVector(long initialSize, long incrementBy)
{
	vectorTotalSize = initialSize;
	vectorIncrementSize = initialSize;

	vectorArray = (long *)malloc(initialSize*sizeof(long));
	for (long i = 0; i < initialSize; i++) vectorArray[i] = 0;

	nextValue = 0;
	vectorArray[nextValue] = incrementBy;
	nextValue++;
}

long BigIntVector::getSize() const
{
	return vectorTotalSize;
}

long BigIntVector::getIncrementSize()
{
	return vectorIncrementSize;
}

void BigIntVector::add(long value)
{
	vectorArray[nextValue] = value;
	nextValue++;
}

ostream& operator<<(std::ostream& os, const BigIntVector& vct)
{
	for (long i = 0; i < vct.vectorTotalSize; i++)
		os << vct.vectorArray[i] << "-";
	return os;
}

BigIntVector operator +(const BigIntVector& leftVector, const BigIntVector& rightVector)

{
	BigIntVector returnVector = BigIntVector(leftVector.vectorTotalSize + rightVector.vectorTotalSize);

	for (long i = 0; i < leftVector.vectorTotalSize; i++)
	{
		returnVector.vectorArray[i] = leftVector.vectorArray[i];
	}

	for (long i = 0; i < rightVector.vectorTotalSize; i++)
	{
		returnVector.vectorArray[leftVector.vectorTotalSize + i] = rightVector.vectorArray[i];
	}

	return returnVector;
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

void BigIntVector::insertElementAt(long index, long value)
{
	long temp, temp2;
	for (long i = index; i < vectorTotalSize - 1; i++)
	{
		if ((i - index) % 2 == 0)
		{
			if (i == index) temp2 = vectorArray[i];
			temp = vectorArray[i + 1];
			vectorArray[i + 1] = temp2;
		}
		else if ((i - index) % 2 == 1)
		{
			temp2 = vectorArray[i + 1];
			vectorArray[i + 1] = temp;
		}
	}
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

void BigIntVector::removeElement(long value)
{
	for (long i = 0; i < vectorTotalSize; i++)
		if (vectorArray[i] == value)
			removeElementAt(i);
}