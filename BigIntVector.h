#ifndef BIGINTVECTOR_H
#define BIGINTVECTOR_H

class BigIntVector
{
public:
	BigIntVector(BigIntVector const& orig);
	BigIntVector(); 
	BigIntVector(long initialSize); 
	~BigIntVector(); //destructor 

	long getSize() const; 
	long getElementAt(long value) const; 
	void resize();

	void setElementAt(long index, long value);
	void removeElementAt(long index); 

	long operator [](long i);
	//friend std::ostream& operator<<(std::ostream& os, const BigIntVector& vct);

	long *vectorArray;
	long vectorSize;
};

#endif