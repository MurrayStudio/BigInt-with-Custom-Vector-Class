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
* Presently dummied up:
* - does not implement integer values larger than the 'long' data
*   type
* - only operations related to '+' and '==' operator are defined
*
*****************************************************************/
class BigInt {
private:
	BigIntVector *bigIntVector;
	bool isPositive;
	int base;

	long data; // our numeric data, for now

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
	BigInt operator+() const;

	// prefix '++' operator
	BigInt operator++();

	// postfix '++' operator
	BigInt operator++(int dummy);

	// compound addition-assignment operator
	BigInt& operator+=(BigInt const& other);

	// binary subtraction
	BigInt& operator-(BigInt const& other) const;

	// unary '-' operator
	BigInt operator-();

	// prefix '--' operator
	BigInt operator--();

	// postfix '--' operator
	BigInt operator--(int dummy);

	// compound subtraction-assignment operator
	BigInt& BigInt::operator-=(BigInt const& other);

	// binary '*' operator
	BigInt& operator*(BigInt const& other) const;

	// compound multiple-assignment operator
	BigInt& operator*=(BigInt const& other);

	int BigInt::compare(BigInt const& other) const;

	// left hand side is long compare
	int BigInt::compare(BigInt const& numBigInt, BigInt const& other) const;

	bool operator<(BigInt const& other) const;

	bool operator<=(BigInt const& other) const;

	bool operator>(BigInt const& other) const;

	bool operator>=(BigInt const& other) const;

	// equality operation
	bool operator==(BigInt const& other) const;

	//****Long Operations****

	bool operator==(long num) const;

	// output-stream operator for BigInt (non-member function)
	friend std::ostream & operator<<(std::ostream& os, BigInt& num);
};

// addition operator where left operand is a long
inline BigInt operator+(long num, BigInt const& val) { //IMPORTANT
	return val + num;
}
// equality operator where left operand is a long
inline bool operator==(long num, BigInt const& val) {

	BigInt numBigInt = num;
	
	return val.compare(numBigInt, val) == 0;
	
	//return val == num;
}

#endif

