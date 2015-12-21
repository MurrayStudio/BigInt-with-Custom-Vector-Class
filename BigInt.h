//Author: Shamus Murray

/****************************************************************
* BigInt.h -- include-file for big integer package
****************************************************************/
#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include "BigIntVector.h"

/*****************************************************************
* BigInt class
*
* All operators required for assignment successfully overloaded for
* the BigInt class.
*
*****************************************************************/
class BigInt {
private:
	BigIntVector *bigIntVector; //custom vector for BigInt
	bool isPositive; //is BigInt positive
	int base; //holds base (should always be 10)

public:
	// copy constructor
	BigInt(BigInt const& orig);

	// constructor where data value is passed as a long
	BigInt(long num);

	// destructor
	~BigInt();

	// binary '+' operator
	BigInt& operator+(BigInt const& other) const;

	// unary '+' operator
	BigInt& operator+() const;

	// prefix '++' operator
	BigInt& operator++();

	// postfix '++' operator
	BigInt& operator++(int dummy);

	// compound addition-assignment operator
	BigInt& operator+=(BigInt const& other);

	// binary subtraction
	BigInt& operator-(BigInt const& other) const;

	// unary '-' operator
	BigInt& operator-();

	// prefix '--' operator
	BigInt& operator--();

	// postfix '--' operator
	BigInt& operator--(int dummy);

	// compound subtraction-assignment operator
	BigInt& operator-=(BigInt const& other);

	// binary '*' operator
	BigInt& operator*(BigInt const& other) const;

	// compound multiple-assignment operator
	BigInt& operator*=(BigInt const& other);

	int compare(BigInt const& other) const;

	// left hand side is long compare
	int compare(BigInt const& numBigInt, BigInt const& other) const;

	//less than operator for BigInt
	bool operator<(BigInt const& other) const;

	//less than or equal to operator for BigInt
	bool operator<=(BigInt const& other) const;

	//greater than operator for BigInt
	bool operator>(BigInt const& other) const;

	//greater than or equal to operator for BigInt
	bool operator>=(BigInt const& other) const;

	//equality operator for BigInt
	bool operator==(BigInt const& other) const;

	//****Long Operations on right****

	//less than operator for BigInt and long
	bool operator<(long num) const;

	//less than or equal to operator for BigInt and long
	bool operator<=(long num) const;

	//greater than operator for BigInt and long
	bool operator>(long num) const;

	//greater than or equal to operator for BigInt for long
	bool operator>=(long num) const;

	//equality operator for BigInt and long
	bool operator==(long num) const;

	// output-stream operator for BigInt (non-member function)
	friend std::ostream & operator<<(std::ostream& os, BigInt& num);
};


//****LONG OPERATIONS ON LEFT****

//addition operator where left operand is a long
inline BigInt operator+(long num, BigInt const& val) {
	return val + num; //add normally
}

//subtraction operator where left operand is a long
inline BigInt operator-(long num, BigInt const& val) {
	BigInt* tempNum = new BigInt(num);

	return *tempNum - val; //add normally
}

//multiplication operator where left operand is a long
inline BigInt operator*(long num, BigInt const& val) {
	return val * num; //multiply normally
}

// equality operator where left operand is a long
inline bool operator==(long num, BigInt const& val) {

	BigInt numBigInt = num; //make copy

	return val.compare(numBigInt, val) == 0; //0 this == other || -1 this < other || 1 this > other
}

// < operator where left operand is a long
inline bool operator<(long num, BigInt const& val) {

	BigInt numBigInt = num; //make copy

	return val.compare(numBigInt, val) == -1; //0 this == other || -1 this < other || 1 this > other
}

// <= operator where left operand is a long
inline bool operator<=(long num, BigInt const& val) {

	BigInt numBigInt = num; //make copy

	int compareBigInt = val.compare(numBigInt, val);

	return compareBigInt == -1 || compareBigInt == 0; //0 this == other || -1 this < other || 1 this > other
}

// > operator where left operand is a long
inline bool operator>(long num, BigInt const& val) {

	BigInt numBigInt = num; //make copy

	return val.compare(numBigInt, val) == 1; //0 this == other || -1 this < other || 1 this > other
}

// >= operator where left operand is a long
inline bool operator>=(long num, BigInt const& val) {

	BigInt numBigInt = num;

	int compareBigInt = val.compare(numBigInt, val);

	return compareBigInt == 1 || compareBigInt == 0; //0 this == other || -1 this < other || 1 this > other
}


#endif

