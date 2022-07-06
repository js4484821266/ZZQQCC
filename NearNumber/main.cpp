#include<iostream>
#include"NearNumber.h"
int main(void) {
	BigInteger x = 0x0123456789abcdef;
	std::cout << (x >>20)._16(true) << std::endl;
	return 0;
}