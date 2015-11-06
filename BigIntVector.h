#ifndef BIGINTVECTOR_H
#define BIGINTVECTOR_H

class BigIntVector
{
public:
	BigIntVector(); 
	BigIntVector(long initialSize); 

	long getSize() const; 
	long getElementAt(long value) const; 
	void resize();

	void setElementAt(long index, long value);
	void removeElementAt(long index); 

	long operator [](long i);

	long *vectorArray;
	long vectorTotalSize;
	long nextValue;
};

#endif