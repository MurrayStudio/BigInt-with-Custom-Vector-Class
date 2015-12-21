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
* All operators required for assignment successfully overloaded for
* the BigInt class.
*
*****************************************************************/

// copy constructor
BigInt::BigInt(BigInt const& orig)
	: isPositive(orig.isPositive)
	, base(orig.base)
{
	this->bigIntVector = new BigIntVector(*(orig.bigIntVector));
}

// constructor where operand is a long
BigInt::BigInt(long num) {
	base = 10; //base is always 10

	long sizeOfLong = 0; //holds size of num
	long tempNum = num; //copy of num

	//get size of num, if 0 size is just 1.
	if (tempNum == 0) {
		sizeOfLong = 1;
	}
	while (tempNum != 0)
	{
		tempNum /= 10;
		++sizeOfLong;
	}

	//resize vector to match size of long passed in
	this->bigIntVector = new BigIntVector(sizeOfLong);

	//if num is less than 0 then it's negative so 
	//set isPositive boolean to false then make
	//the number a positive.
	if (num < 0) {
		isPositive = false;
		num *= -1;
	}
	else {
		isPositive = true;
	}

	//take num and push a digit one by one into vector
	//by modding num by the base then dividing number
	//after setting element.
	long pushedNum;
	for (int i = sizeOfLong - 1; i >= 0; --i) {
		pushedNum = (long)(num%base);
		bigIntVector->setElementAt(i, pushedNum);
		num /= base;
	}
}

// destructor
BigInt::~BigInt() {
	//delete[] this->bigIntVector;
}

// binary addition
BigInt& BigInt::operator+(BigInt const& other) const {

	//copy of this and other BigInts passed into +.
	BigInt* tempThis = new BigInt(*this); //1st number
	BigInt* tempOther = new BigInt(other); //2nd number

	 //NEGATIVE CHECKING

	//ex: pos + neg
	if (tempThis->isPositive && !tempOther->isPositive) {
		tempOther->isPositive = true; //make other positive for now
		//ex: 10 + -20
		if ((*tempThis < *tempOther)) {
			*tempOther -= *tempThis; //reverse numbers and subtract
			tempOther->isPositive = false; //result is negated
			return *tempOther;
		}
		//ex: 20 + -10
		if ((*tempThis >= *tempOther)) {
			*tempThis -= *tempOther; //subtract numbers
			return *tempThis;
		}
	}
	//ex: neg + pos
	if (!tempThis->isPositive && tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
		//ex: -10 + 20 = 10
		if ((*tempThis <= *tempOther)) {
			*tempOther -= *tempThis; //reverse numbers and subtract
			return *tempOther;
		}
		//ex: -100 + 20 = -80
		if ((*tempThis > *tempOther)) {
			*tempThis -= *tempOther; //subtract numbers
			tempThis->isPositive = false; //negate answer
			return *tempThis;
		}
	}

	//ex: neg + neg	
	if (!tempThis->isPositive && !tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
		tempOther->isPositive = true; //make other positive for now
		*tempThis += *tempOther; //return normal pos + pos additon
		tempThis->isPositive = false; //negate answer
		return *tempThis;
	}

	*tempThis += *tempOther; //if no negative cases then move onto adding normally
	return *tempThis;

}

// compound addition-assignment operator
BigInt& BigInt::operator+=(BigInt const& other) {

	//copy of this and other BigInts passed into +.
	BigInt* tempThis = new BigInt(*this); //1st number
	BigInt* tempOther = new BigInt(other); //2nd number

	//NEGATIVE CHECKING

	//ex: pos + neg
	if (tempThis->isPositive && !tempOther->isPositive) {
		tempOther->isPositive = true; //make other positive for now
		//ex: 10 + -20
		if ((*tempThis < *tempOther)) {
			*tempOther -= *tempThis; //reverse numbers and subtract
			tempOther->isPositive = false; //result is negated
			*this = *tempOther;
			return *this;
		}
		//ex: 20 + -10
		if ((*tempThis >= *tempOther)) {
			*tempThis -= *tempOther; //subtract numbers
			*this = *tempThis;
			return *this;
		}
	}
	//ex: neg + pos
	if (!tempThis->isPositive && tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
		//ex: -10 + 20 = 10
		if ((*tempThis <= *tempOther)) {
			*tempOther -= *tempThis; //reverse numbers and subtract
			*this = *tempOther;
			return *this;
		}
		//ex: -100 + 20 = -80
		if ((*tempThis > *tempOther)) {
			*tempThis -= *tempOther; //subtract numbers
			tempThis->isPositive = false; //negate answer
			*this = *tempThis;
			return *this;
		}
	}

	//ex: neg + neg	
	if (!tempThis->isPositive && !tempOther->isPositive) {
		tempThis->isPositive = true;
		tempOther->isPositive = true;
		*tempThis += *tempOther; //return normal pos + pos additon
		tempThis->isPositive = false; //negate answer
		*this = *tempThis;
		return *this;
	}

	//****Addition logic****

	int sum = 0; //holds the sum of the current digit place in both vectors
	int maxSize = 0; //holds size of biggest BigInt
	int carry = 0; //holds carry over value
	int sizeDifference = 0; //holds size difference between this and other vector

	//calculate size difference
	if (bigIntVector->getSize() > other.bigIntVector->getSize()) {
		sizeDifference = bigIntVector->getSize() - other.bigIntVector->getSize();
	}

	//increase size of first big int vector until it matches size of second with new slots added in front of number
	while (bigIntVector->getSize() < other.bigIntVector->getSize()) {
		bigIntVector->resizePlusOne();
	}

	//get size of this big int (it is max size because it will
	//at least be as big as other vector
	maxSize = bigIntVector->getSize();

	//keeps track if we are done getting digits from smaller (other) array
	int otherCounter = other.bigIntVector->getSize() - 1;

	//loop through each digit in both vectors
	for (int i = maxSize - 1; i >= 0; i--) {
		sum += bigIntVector->getElementAt(i); //sum is equal to element in this
		sum += carry; //add any carry

		//if any other digits remain, then proceed something those digits
		if (otherCounter >= 0) {
			sum += other.bigIntVector->getElementAt(i - sizeDifference); //shift index if size is different
			carry = 0; //reset carry

			//do we need to carry
			if (sum > 9) {
				++carry; //add 1 to carry
				bigIntVector->setElementAt(i, sum%base); //mod sum and set element
			}
			else {
				carry = 0; //carry still 0
				bigIntVector->setElementAt(i, sum%base); //mod sum and set element
			}

			--otherCounter; //we are done looking at 1 more digit in other so decrement spaces left
		}
		//no more of digits in other
		else {
			carry = 0; //carry is 0

			if (sum > 9) {
				++carry; //add 1 to carry
				bigIntVector->setElementAt(i, sum%base); //mod sum and set element
			}
			else {
				bigIntVector->setElementAt(i, sum%base); //mod sum and set element
			}
		}
		//if we are at beginning of vector (end of loop) and there's still a carry
		//then we need to expand vector to make room for extra number.
		if (otherCounter < 0 && carry > 0 && i == 0) {
			bigIntVector->resizePlusOne(); //increase size of big int
			bigIntVector->setElementAt(i, carry); //set carry in front of sum spot
		}
		sum = 0; //reset sum count for next loop
	}


	return *this;

}

// prefix '++' operator
BigInt& BigInt::operator++() {

	BigInt* tempThis = new BigInt(*this);  //copy of this
	return *tempThis += 1; //add 1 and return
}

// postfix '++' operator
BigInt& BigInt::operator++(int dummy) {
	BigInt* tempThis = new BigInt(*this); //copy of this
	return *tempThis += 1; //add 1
}

// unary '+' operator
BigInt& BigInt::operator+() const {
	BigInt* tempThis = new BigInt(*this); //copy of this
	return *tempThis; //return
}

// binary subtraction
BigInt& BigInt::operator-(BigInt const& other) const {

	//copy of this and other
	BigInt* tempThis = new BigInt(*this); //1st number
	BigInt* tempOther = new BigInt(other); //2nd number

										   //NEGATIVE CHECKING

										   //ex: pos - pos
	if (tempThis->isPositive && tempOther->isPositive) {
		//ex: 10 - 20
		if (*tempThis < *tempOther) {
			*tempOther -= *tempThis; //reverse then subract
			tempOther->isPositive = false; //negate answer
			return *tempOther;
		}
	}

	//ex: pos - neg
	if (tempThis->isPositive && !tempOther->isPositive) {
		tempOther->isPositive = true; //make other positive for now
									  //ex: 10 - (-20) || 30 - (-20)
		*tempThis += *tempOther; //add normally
		return *tempThis;
	}
	//ex: neg - pos
	if (!tempThis->isPositive && tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
									 //ex: -10 - 20 = -30 || -20 - 10 = -30
		*tempThis += *tempOther; //add normally
		tempThis->isPositive = false; //negate answer
		return *tempThis;
	}

	//ex: neg + neg	
	if (!tempThis->isPositive && !tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
		tempOther->isPositive = true; //make other positive for now
		if (*tempThis <= *tempOther) {
			*tempOther -= *tempThis; //reverse numbers and subtract
			return *tempOther;
		}
		if (*tempThis > *tempOther) {
			*tempThis -= *tempOther; //subtract normally
			tempThis->isPositive = false; //negate answer
			return *tempThis;
		}
	}

	*tempThis -= *tempOther; //subtract normally if no negative cases found
	return *tempThis;
}

// compound subtraction-assignment operator
BigInt& BigInt::operator-=(BigInt const& other) {

	//copy of this and other
	BigInt* tempThis = new BigInt(*this); //1st number
	BigInt* tempOther = new BigInt(other); //2nd number

										   //NEGATIVE CHECKING

										   //ex: pos - pos
	if (tempThis->isPositive && tempOther->isPositive) {
		//ex: 10 - 20
		if (*tempThis < *tempOther) {
			*tempOther -= *tempThis; //reverse then subract
			tempOther->isPositive = false; //negate answer
			*this = *tempOther;
			return *this;
		}
	}

	//ex: pos - neg
	if (tempThis->isPositive && !tempOther->isPositive) {
		tempOther->isPositive = true; //make other positive for now
									  //ex: 10 - (-20) || 30 - (-20)
		*tempThis += *tempOther; //add numbers
		*this = *tempThis;
		return *this;
	}
	//ex: neg - pos
	if (!tempThis->isPositive && tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
									 //ex: -10 - 20 = -30 || -20 - 10 = -30
		*tempThis += *tempOther; //add numbers
		tempThis->isPositive = false; //negate answer
		*this = *tempThis;
		return *this;
	}

	//ex: neg + neg	
	if (!tempThis->isPositive && !tempOther->isPositive) {
		tempThis->isPositive = true;
		tempOther->isPositive = true;
		if (*tempThis <= *tempOther) {
			*tempOther -= *tempThis; //reverse then subract
			*this = *tempOther;
			return *this;
		}
		if (*tempThis > *tempOther) {
			*tempThis -= *tempOther; //subtract
			tempThis->isPositive = false; //negate answer
			*this = *tempThis;
			return *this;
		}
	}

	//****subtraction logic****

	int difference = 0; //holds the difference of the values in the i th place in both vectors
	int maxSize = 0; //holds size of biggest BigInt
	int sizeDifference = 0; //holds size difference between this and other

							//calculate size difference
	if (bigIntVector->getSize() > other.bigIntVector->getSize()) {
		sizeDifference = bigIntVector->getSize() - other.bigIntVector->getSize();
	}

	//increase size of first big int vector until it matches size of second with new slots added in front of number
	maxSize = bigIntVector->getSize();

	//keeps track if we are done getting digits from smaller (other) array
	int otherCounter = other.bigIntVector->getSize() - 1;

	//loops through both vectors doing digit subtraction
	for (int i = maxSize - 1; i >= 0; i--) {
		difference += bigIntVector->getElementAt(i); //add the top vector digit that will be subtracted from

													 //if any other digits remain, then proceed something those digits
		if (otherCounter >= 0) {
			difference -= other.bigIntVector->getElementAt(i - sizeDifference); //shift index if size is different

																				//if difference is negative we need to find a 1
			if (difference < 0) {

				//begin looking for a 1 or higher to use in this bigIntVector
				for (int y = i - 1; y >= 0; y--) {
					int newElement = bigIntVector->getElementAt(y); //test for non-zero

																	//if we have found a 1 or higher
					if (newElement > 0) {
						newElement -= 1; //take one off newElement
						bigIntVector->setElementAt(y, (newElement)); //apply the new newElement value at spot we found it
																	 //loop through any 0's in between newElement and i and change to 9s
						for (int z = y + 1; z <= i - 1; z++) {
							int addToElement = bigIntVector->getElementAt(z);
							addToElement += 9;
							bigIntVector->setElementAt(z, addToElement); //add 9 to space
						}
						difference += 10; //add 10 to the difference because we subtracted 1
						break;
					}
				}
			}
		}
		bigIntVector->setElementAt(i, difference); //set element at current position


		--otherCounter; //move up to next digit in other vector

		difference = 0; //reset difference
	}

	//all 0's in front of this bigIntVector should be sized down until non-zero is reached
	//ex: 0000067 -> 67
	int i = 0; //counter
	while (bigIntVector->getElementAt(i) == 0) {
		if (bigIntVector->getSize() == 1) {
			//don't resize because only 0 is there.
		}
		else {
			bigIntVector->resizeMinusOne(); //shrink vector
			i--; //we lost a spot so go back to beginning of index to look at new 0 index.
		}
		i++;
	}

	return *this;

}

// prefix '--' operator
BigInt& BigInt::operator--() {

	BigInt* tempThis = new BigInt(*this); //copy of ths
	return *tempThis -= 1; //subtract 1
}

// postfix '--' operator
BigInt& BigInt::operator--(int dummy) {
	BigInt* tempThis = new BigInt(*this); //copy of this
	return *tempThis -= 1; //subtract 1
}

// unary '-' operator
BigInt& BigInt::operator-() {

	this->isPositive = false; //negate BigInt

	return *this;
}

// binary multiplication
BigInt& BigInt::operator*(BigInt const& other) const {

	//copy of this and other
	BigInt* tempThis = new BigInt(*this); //1st number
	BigInt* tempOther = new BigInt(other); //2nd number

	//NEGATIVE CHECKING

	//ex: pos * neg
	if (tempThis->isPositive && !tempOther->isPositive) {
		tempOther->isPositive = true; //make other positive for now
		*tempThis *= *tempOther; //multiply normally
		tempThis->isPositive = false; //negate answer
		return *tempThis;
	}

	//ex: neg * pos
	if (!tempThis->isPositive && tempOther->isPositive) {
		tempThis->isPositive = true; //make this positive for now
		*tempThis *= *tempOther; //multiply normally
		tempThis->isPositive = false; //negate answer
		return *tempThis;
	}

	//ex: neg * neg	
	if (!tempThis->isPositive && !tempOther->isPositive) {
		tempThis->isPositive = true; //make other positive for now
		tempOther->isPositive = true; //make other positive for now
		*tempThis *= *tempOther; //multiply normally
		return *tempThis;
	}

	//if negative cases apply then multiply normally 
	*tempThis *= other;
	return *tempThis;

}

// compound multiplication-assignment operator
BigInt& BigInt::operator*=(BigInt const& other) {

	//copy of this and other
	BigInt* tempThis = new BigInt(*this); //1st number
	BigInt* tempOther = new BigInt(other); //2nd number

	//NEGATIVE CHECKING

	//ex: pos * neg
	if (tempThis->isPositive && !tempOther->isPositive) {
		tempOther->isPositive = true; //make other positive for now
		*tempThis *= *tempOther;  //multiply normally
		tempThis->isPositive = false; //negate answer
		*this = *tempThis;
		return *this;
	}

	//ex: neg * pos
	if (!tempThis->isPositive && tempOther->isPositive) {
		tempThis->isPositive = true; //make this positive for now
		*tempThis *= *tempOther; //multiply normally
		tempThis->isPositive = false; //negate answer
		*this = *tempThis;
		return *this;
	}

	//ex: neg * neg	
	if (!tempThis->isPositive && !tempOther->isPositive) {
		tempThis->isPositive = true; //make this positive for now
		tempOther->isPositive = true; //make this positive for now
		*tempThis *= *tempOther; //multiply normally
		*this = *tempThis;
		return *this;
	}

	//create temps so we can use value of BigInt before it is changed
	BigInt otherTemp = BigInt(other); //copy of other
	BigInt sum = 0; //holds the eventual answer

	//add *this BigInt to sum otherTemp amount of times
	//this will yield multiplication answer.
	for (BigInt i = 0; i < otherTemp; i = i + 1) {
		sum += *this;
	}

	*this = sum;

	return *this;

}

//Compare two BigInts
//0 this == other || -1 this < other || 1 this > other
int BigInt::compare(BigInt const& other) const
{
	//pos > neg
	if (isPositive && !other.isPositive) {
		return 1;
	}
	//neg < pos
	if (!isPositive && other.isPositive) {
		return -1;
	}

	//size: 10 < 20
	if (bigIntVector->getSize() < other.bigIntVector->getSize()) {
		return -1;
	}
	//size: 20 > 10
	if (bigIntVector->getSize() > other.bigIntVector->getSize()) {
		return 1;
	}

	int maxSize = 0; //holds size of the equaled size vectors
	maxSize = bigIntVector->getSize(); //get size and assign to maxSize

	//loop through both vectors from beginning until we find two different
	//digits where < or > can apply.
	for (int i = 0; i < maxSize; i++) {
		if (bigIntVector->getElementAt(i) < other.bigIntVector->getElementAt(i)) {
			return -1;
		}
		if (bigIntVector->getElementAt(i) > other.bigIntVector->getElementAt(i)) {
			return 1;
		}
	}

	return 0; //BigInts are equal
}


//****************************************************
//Compare two BigInts with no this (used with longs)

//*See function above for comments. This function is the same
//except 'this = numBigInt' parameter. 

//0 this == other || -1 this < other || 1 this > other
int BigInt::compare(BigInt const& numBigInt, BigInt const& other) const
{
	if (numBigInt.isPositive && !other.isPositive) {
		return 1;
	}
	if (!numBigInt.isPositive && other.isPositive) {
		return -1;
	}

	if (numBigInt.bigIntVector->getSize() < other.bigIntVector->getSize()) {
		return -1;
	}
	if (numBigInt.bigIntVector->getSize() > other.bigIntVector->getSize()) {
		return 1;
	}

	int maxSize = 0;

	maxSize = numBigInt.bigIntVector->getSize();

	for (int i = 0; i < maxSize; i++) {
		if (numBigInt.bigIntVector->getElementAt(i) < other.bigIntVector->getElementAt(i)) {
			return -1;
		}
		if (numBigInt.bigIntVector->getElementAt(i) > other.bigIntVector->getElementAt(i)) {
			return 1;
		}
	}

	return 0;
}

//less than operator for BigInt
bool BigInt::operator<(BigInt const& other) const
{
	return compare(other) == -1; //0 this == other || -1 this < other || 1 this > other
}

//less than or equal to operator for BigInt
bool BigInt::operator<=(BigInt const& other) const
{
	int compareBigInt = compare(other);

	return compareBigInt == 0 || compareBigInt == -1; //0 this == other || -1 this < other || 1 this > other
}

//greater than operator for BigInt
bool BigInt::operator>(BigInt const& other) const
{
	return compare(other) == 1; //0 this == other || -1 this < other || 1 this > other
}

//greater than or equal to operator for BigInt
bool BigInt::operator>=(BigInt const& other) const
{
	int compareBigInt = compare(other);

	return compareBigInt == 0 || compareBigInt == 1; //0 this == other || -1 this < other || 1 this > other
}

//equality operator for BigInt
bool BigInt::operator==(BigInt const& other) const {

	return compare(other) == 0; //0 this == other || -1 this < other || 1 this > other
}


//****LONG OPERATIONS ON RIGHT****

//less than operator for BigInt and long
bool BigInt::operator<(long num) const
{
	BigInt bigIntOther = BigInt(num); //copy of num

	return compare(bigIntOther) == -1; //0 this == other || -1 this < other || 1 this > other
}

//less than or equal to operator for BigInt and long
bool BigInt::operator<=(long num) const
{
	BigInt bigIntOther = BigInt(num); //copy of num

	int compareBigInt = compare(bigIntOther);

	return compareBigInt == 0 || compareBigInt == -1; //0 this == other || -1 this < other || 1 this > other
}

//greater than operator for BigInt and long
bool BigInt::operator>(long num) const
{
	BigInt bigIntOther = BigInt(num); //copy of num

	return compare(bigIntOther) == 1; //0 this == other || -1 this < other || 1 this > other
}

//greater than or equal to operator for BigInt for long
bool BigInt::operator>=(long num) const
{
	BigInt bigIntOther = BigInt(num); //copy of num

	int compareBigInt = compare(bigIntOther);

	return compareBigInt == 0 || compareBigInt == 1; //0 this == other || -1 this < other || 1 this > other
}

//equality operator for BigInt and long
bool BigInt::operator==(long num) const {

	BigInt bigIntOther = BigInt(num); //copy of num

	return compare(num) == 0; //0 this == other || -1 this < other || 1 this > other
}

// output-stream operator for BigInt (non-member function)
ostream & operator<<(ostream& os, BigInt& num) {

	if (!num.isPositive) os << '-'; //add negative in front if negative

	os << num.bigIntVector[0]; //use big int vector to print, syntax has to be like this

	return os;
}