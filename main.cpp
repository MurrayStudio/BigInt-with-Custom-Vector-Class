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

	// object with explicit constructor from long
	BigInt num1(12);

	cout << "num1 (12): " << num1 << endl;

	// object with implicit constructor from long
	BigInt num2 = 19;

	cout << "num2 (19): " << num2 << endl;

	// binary addition BigInt+BigInt
	BigInt num3 = num1 + num2;

	cout << "num3 (31): " << num3 << endl;

	BigInt numA = 99999;

	cout << "numA (99999): " << numA << endl;

	BigInt numB = 99999;

	cout << "numB (99999): " << numB << endl;
	
	BigInt numC = numA + numB;

	cout << "numC (199998): " << numC << endl;

	// binary addition BigInt+long
	BigInt num4 = num3 + 2;

	cout << "num4 (33): " << num4 << endl;

	// unary +
	BigInt num5 = +num2;

	cout << "num5 (19): " << num5 << endl;


	// prefix increment
	BigInt num6 = ++num1;

	cout << "num6 (13): " << num6 << endl;

	//binary subtraction
	BigInt num7 = num2 - num1;

	cout << "num7 (7): " << num7 << endl;

	BigInt numD = 102001112;

	cout << "numD (102001112): " << numD << endl;

	BigInt numE = 998;

	cout << "numE (998): " << numE << endl;

	//binary subtraction
	BigInt numF = numD - numE;

	cout << "numF (102000114): " << numF << endl;

	// postfix increment
	BigInt num8 = num3++;

	cout << "num8 (32): " << num8 << endl;

	// direct initialization
	BigInt num9 = num3;

	cout << "num9 (31): " << num9 << endl;

	// increment PROBLEM HERE!!!
	num3++;

	cout << "num3 (32): " << num3 << endl;

	// compound assignment addition with BigInt
	num4 += num5;

	cout << "num4 (52): " << num4 << endl;

	// compund assignment addition with long
	num5 += 34;

	cout << "num5 (53): " << num5 << endl;

	// assignment with long
	num8 = 23;

	cout << "num8 (23): " << num8 << endl;

	// binary addition: long + BigInt
	num3 = 28 + num8;

	cout << "num3 (51): " << num3 << endl;

	BigInt num10 = 100;

	cout << "num10 (100): " << num10 << endl;

	//prefix --
	num10 = --num10;

	cout << "num10 (99): " << num10 << endl;

	BigInt num11 = -30;

	cout << "num11 (-30): " << num11 << endl;

	//num11 = -num11;

	//cout << "num11 (-30): " << num11 << endl;

	BigInt num12 = 40;

	cout << "num12 (40): " << num12 << endl;

	BigInt num13 = num12 + num11;

	cout << "num13 (10): " << num13 << endl;

	BigInt num14 = -40;

	cout << "num14 (-40): " << num14 << endl;

	BigInt num15 = 30;

	cout << "num15 (30): " << num15 << endl;

	BigInt num16 = num14 + num15;

	cout << "num16 (-10): " << num16 << endl;

	BigInt num17 = 5;

	cout << "num17 (5): " << num17 << endl;

	BigInt num18 = 81;

	cout << "num18 (81): " << num18 << endl;

	BigInt num19 = 5 * 81;

	cout << "num19 (405): " << num19 << endl;

	BigInt num20 = 5;

	cout << "num20 (10): " << num20 << endl;

	BigInt num21 = 1;

	for (int i = 0; i < 20; i++) {
		//cout << "num21 (BigInt): " << num21 << endl;
		num21 *= num20;
	}

	cout << "num21 (BigInt): " << num21 << endl;


	BigInt boolNum = 10;
	BigInt boolNum2 = 11;
	BigInt boolNum3 = 10;

	// perform some equality tests where 1 = true and 0 = false
	bool bool1 = boolNum == boolNum2; 

	cout << "bool1 (1): " << bool1 << endl;

	bool bool2 = boolNum < boolNum2; 

	cout << "bool2 (1): " << bool2 << endl;

	bool bool3 = boolNum > boolNum2;

	cout << "bool3 (0): " << bool3 << endl;

	bool bool4 = boolNum >= boolNum3;

	cout << "bool4 (1): " << bool4 << endl;

	//cout << "bool2 (0): " << bool1 << endl;

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