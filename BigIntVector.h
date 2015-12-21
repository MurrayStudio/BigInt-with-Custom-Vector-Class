//Author: Shamus Murray

/****************************************************************
* BigInt.h -- include-file for big integer vector package
****************************************************************/

#ifndef BIGINTVECTOR_H
#define BIGINTVECTOR_H

class BigIntVector
{
public:
	int *vectorArray; //underlying array to custom vector class
	int vectorSize; //size of vector

	BigIntVector(BigIntVector const& orig); //copy constructor
	BigIntVector(); //default const
	BigIntVector(int initialSize); //init const
	~BigIntVector(); //destructor 

	//get current size of vector
	int getSize() const;
	//return element at index provided
	int getElementAt(int index) const;
	//increases vector capacity by 1
	void resizePlusOne();
	//decreases vector capacity by 1
	void resizeMinusOne();
	//set element value at index provided
	void setElementAt(int index, int value);
	//allows use of [] on vectors
	int operator [](int index);
	//print contents of vector
	friend std::ostream& operator<<(std::ostream& os, const BigIntVector& vct);
};

#endif