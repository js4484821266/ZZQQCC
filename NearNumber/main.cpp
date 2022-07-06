#include<iostream>
#include"NearNumber.h"
int main(void) {
	BigInteger x, y;
	x = 0x0fedcba987654321;
	y = 0x7015bc17293abd80;
	y[1] = 0;
	std::cout << (y.size()) << std::endl;
	return 0;
}