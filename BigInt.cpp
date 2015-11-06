//Author: Shamus Murray

/****************************************************************
* BigInt.cpp -- big integer package for C++
****************************************************************/
#include <iostream>
#include "BigInt.h"

using namespace std;

/*****************************************************************
* member functions for BigInt class
*
* Presently dummied up:
* - does not implement integer values larger than the 'long' data
*   type
* - only operations related to '+' and '==' operator are defined
*
*****************************************************************/

// copy constructor
BigInt::BigInt(BigInt const& orig) {
	//this->data = orig.data;
	
	//orig = bigIntVector;

	*this = orig;
}

// constructor where operand is a long
BigInt::BigInt(long num) {
	//this->data = num;

	base = 10;

	long sizeOfLong = 0; //holds size of num
	long tempNum = num; 

	//get size of num
	if (tempNum == 0) {
		sizeOfLong = 1;
	}
	while (tempNum != 0)
	{
		tempNum /= 10;
		++sizeOfLong;
	}

	//resize vector to match size of long
	bigIntVector = BigIntVector(sizeOfLong);
	//cout << "sizeVec: " << bigIntVector.getSize() << endl;

	if (num < 0) {
		isPositive = false;
		num *= -1;
	}
	else {
		isPositive = true;
	}
	long pushedNum;
	//cout << "num: " << num << endl;
	for (int i = sizeOfLong - 1; i >= 0; --i) {
		pushedNum = (long)(num%base);
		//cout << "pushedNum: " << pushedNum << endl;
		//cout << "i: " << i << endl;
		bigIntVector.setElementAt(i, pushedNum);
		num /= base;
	}
}

// destructor
BigInt::~BigInt() {
	//delete *this;
}

// binary addition
BigInt BigInt::operator+(BigInt const& other) const {
	//BigInt rtnVal(this->data + other.data);

	BigInt thisBigInt = *this;
	thisBigInt += other;

	return thisBigInt; //return a BigInt
}

// compound addition-assignment operator
BigInt BigInt::operator+=(BigInt const& other) {
	//return this->data = this->data + other.data;

	//BigInt thisBigInt = *this;

	if (!other.isPositive) {
		//return thisBigInt -= other;
	}
	//possible check for both negative???


	int sum = 0; //holds the sum of the value in both vectors
	int maxSize = 0; //holds size of biggest BigInt
	int carry = 0; //holds carry over value
	int sizeDifference = 0; //holds size difference between b and a if b is bigger

	//check size
	while (bigIntVector.getSize() < other.bigIntVector.getSize()) {
		bigIntVector.resize(); //increase size of first big int until it matches size of second
	}

	if (bigIntVector.getSize() > other.bigIntVector.getSize()) {
		sizeDifference = bigIntVector.getSize() - other.bigIntVector.getSize();
		cout << "sizeDiff: " << sizeDifference << endl;
	}

	maxSize = bigIntVector.getSize();

	int otherCounter = other.bigIntVector.getSize() - 1; //keeps track if we are done getting digits from other array
	cout << "otherCounter: " << otherCounter << endl;

	for (int i = maxSize - 1; i >= 0; i--) {
		cout << "element1: " << bigIntVector.getElementAt(i) << endl;
		cout << "element2: " << other.bigIntVector.getElementAt(i) << endl;
		sum += bigIntVector.getElementAt(i);
		if (otherCounter >= 0) {
			sum += other.bigIntVector.getElementAt(i - sizeDifference); //move index if size is different
			sum += carry;
			carry = 0;
			cout << "sum: " << sum << endl;
			if (sum > 9) {
				++carry;
				bigIntVector.setElementAt(i, sum%base);
			}
			else {
				carry = 0;
				bigIntVector.setElementAt(i, sum%base);
			}

			--otherCounter; //only decrement otherCounter if we have reached 2nd vector elements
		}
		if (otherCounter < 0 && carry > 0) {
			bigIntVector.resize(); //increase size of big int
			bigIntVector.setElementAt(i, carry); //set carry in front of sum spot
		}
		sum = 0;
	}

	return *this;

}

// prefix '++' operator
BigInt BigInt::operator++() {
	//return this->data = this->data + 1;

	BigInt thisBigInt = *this;
	thisBigInt += 1;

	return thisBigInt; //return a BigInt

	//int otherCounter = 0; //if counter goes negative we have added the 1
	//int sum = 0; //holds sum of digits
	//int carry = 0; //holds any carry values

	//for (int i = bigIntVector.getSize() - 1; i >= 0; i--) {
	//	cout << "element1: " << bigIntVector.getElementAt(i) << endl;
	//	sum += bigIntVector.getElementAt(i);
	//	if (otherCounter == 0) { //if counter goes negative we have added the 1
	//		sum += 1; //add the 1
	//		sum += carry;
	//		carry = 0;
	//		cout << "sum: " << sum << endl;
	//		if (sum > 9) {
	//			++carry;
	//			bigIntVector.setElementAt(i, sum%base);
	//		}
	//		else {
	//			carry = 0;
	//			bigIntVector.setElementAt(i, sum%base);
	//		}

	//		--otherCounter; //only decrement otherCounter if we have reached 2nd vector elements
	//	}
	//	if (otherCounter < 0 && carry > 0) {
	//		bigIntVector.resize(); //increase size of big int
	//		bigIntVector.setElementAt(i, carry); //set carry in front of sum spot
	//	}
	//	sum = 0;
	//}

	//return *this;
}

// postfix '++' operator
BigInt BigInt::operator++(int dummy) {
	BigInt temp = *this;
	this->data = this->data + 1;
	return temp;
}


// unary '+' operator
BigInt BigInt::operator+() const {
	return *this;
}

// equality operator
bool BigInt::operator==(BigInt const& other) const {
	return this->data == other.data;
}

// output-stream operator for BigInt (non-member function)
ostream & operator<<(ostream& os, BigInt& num) {
	//os << num.data;

	//while (num.bigIntVector.size() && num.bigIntVector.back() == 0) {
	//	//num.bigIntVector.pop_back();
	//}

	if (!num.isPositive) os << '-';

	for (int i = 0; i < num.bigIntVector.getSize(); i++) {
		os << num.bigIntVector[i];
		//num.bigIntVector.pop_back();
	}

	return os;
}