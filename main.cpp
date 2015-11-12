/*****************************************************************
* Defines main function containing some BigInt tests
*****************************************************************/
#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include "BigInt.h"
#include "BigIntVector.h"

using namespace std;

int main(void) {

	//****ADDING****

	// object with explicit constructor from long
	BigInt num1(9140);

	// object with implicit constructor from long
	BigInt num2 = 870;

	// binary addition BigInt+BigInt
	BigInt num3 = num1 + num2;

	cout << "num3 (10010): " << num3 << endl;

	BigInt numA = 99999;

	cout << "numA (99999): " << numA << endl;

	BigInt numB = 99999;

	cout << "numB (99999): " << numB << endl;

	BigInt numC = numA + numB;

	cout << "numC (199998): " << numC << endl;


	//****MULTIPLICATION****


	BigInt num4 = 5;
	BigInt num5 = 100;

	BigInt num6 = num4 * num5;

	cout << "num6 (500): " << num6 << endl;

	BigInt num7 = 1;

	for (int i = 0; i < 100; i++) {

		num7 *= num4;

	}

	cout << "num7 (5^100): " << num7 << endl;

	BigInt num8 = 1;


	for (BigInt i = 30; i > 0; i = i - 1) {

		num8 *= i;

	}

	cout << "num8 (30!): " << num8 << endl;

	//****SUBTRACTION****

	BigInt num9 = 199;
	BigInt num10 = 100;

	BigInt num11 = num9 - num10;

	cout << "num11 (99): " << num11 << endl;

	BigInt num12 = 2;
	
	num8 -= num12;

	cout << "num8 (30! - 1): " << num8 << endl;

	//****Boolean****

	BigInt boolNum = 10;
	BigInt boolNum2 = 11;
	BigInt boolNum3 = 10;
	BigInt boolNum4 = 79;
	BigInt boolNum5 = 81;

	// perform some equality tests where 1 = true and 0 = false
	bool bool1 = boolNum == boolNum3; 

	cout << "bool1 (0): " << bool1 << endl;

	bool bool2 = boolNum < boolNum2; 

	cout << "bool2 (1): " << bool2 << endl;

	bool bool3 = boolNum > boolNum2;

	cout << "bool3 (0): " << bool3 << endl;

	bool bool4 = boolNum >= boolNum3;

	cout << "bool4 (1): " << bool4 << endl;

	bool bool5 = boolNum4 < boolNum5;

	cout << "bool5 (1): " << bool5 << endl;

	bool bool6 = boolNum == 5; // BigInt == long

	cout << "bool6 (1): " << bool6 << endl;

	//bool bool7 = 9 < boolNum; // BigInt == long

	//cout << "bool7 (1): " << bool7 << endl;

	//bool bool2 = num6 == num1; // BigInt == BigInt
	//bool bool3 = num1 == 4; // BigInt == long
	//bool bool4 = num2 == 60; // BigInt == long
	//bool bool5 = 4 == num1; // long == BigInt
	//bool bool6 = 60 == num2; // long == BigInt

							 // print the values
	//cout << "Bool Values: " << bool1 << " " << bool2 << " " << bool3 << " " <<
	//	bool4 << " " << bool5 << " " << bool6 << " " << "\n" << endl;

	//cout << "Num Values: " << num1 << " " << num2 << " " << num3 << " " <<
	//	num4 << " " << num5 << " " << num6 << " " <<
	//	num7 << " " << num8 << "\n" << endl;

	// loop that computes a very large value
	//
	// with the dummied-up varsion, it overflows; in the completed
	// implementation, it should actually compute the correct value
	//BigInt bigVal = 1234;
	//cout << "Big Val: " << bigVal << "\n" << endl;
	//for (BigInt i = 0; !(i == 35); i++) {
	//	bigVal += bigVal;
	//	bigVal += bigVal;
	//	bigVal += 1;
	//	cout << "New Big Val: " << bigVal << endl;
	//}

	return EXIT_SUCCESS;
}