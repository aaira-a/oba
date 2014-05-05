#include <iostream>
#include <stdio.h>

using namespace std;


bool getOddParityBit(unsigned int x) {
	
	x = ((x >> 1) & 0x55555555) + (x & 0x55555555);
	x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
	x = ((x >> 4) & 0x0F0F0F0F) + (x & 0x0F0F0F0F);
	x = ((x >>  8 ) + x);
	x = ((x >>  16 ) + x);
	return !(x&0x01); //return odd parity bit
}


int main() {
	//cout << "unsigned:\t" << sizeof(unsigned int) << " bytes" << endl;

	int input;
	unsigned int output;  //implicit cast of bool return from fn to unsigned int

	for (;;) {
		cout << "Please input an unsigned int: \t";
		cin >> input;
		output = getOddParityBit(input);  
		cout << "The output is: \t" << output << endl;
	}
}