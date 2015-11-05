#ifndef BIGINTVECTOR_H
#define BIGINTVECTOR_H

class BigIntVector
{
public:
	BigIntVector(); //
	BigIntVector(long initialSize); //
	BigIntVector(long initialSize, long incrementBy); //

	long getSize() const; //
	long getIncrementSize(); //
	long getElementAt(long value) const; //
	void resize(); 

	void add(long value); //
	void setElementAt(long index, long value);//
	void insertElementAt(long index, long value); //
	void removeElementAt(long index); //
	void removeElement(long value); //

	friend std::ostream& operator<<(std::ostream& os, const BigIntVector& vct);
	friend BigIntVector operator+(const BigIntVector& leftVector, const BigIntVector& rightVector);
	long operator [](long i);

	long *vectorArray;
	long vectorIncrementSize;
	long vectorTotalSize;
	long nextValue;
};

#endif