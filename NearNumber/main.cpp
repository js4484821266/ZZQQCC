#include<iostream>
#include"NearNumber.h"
int main(void) {
	BigInteger x=0x1234567890;
	BigInteger y=0;
	std::cout << "sizeof(int): " << sizeof(int) << std::endl;
	std::cout << "x._16(): " << x._16() << ", ";
	std::cout << "y._16(): " << y._16() << std::endl;
	std::cout << "(short)x: " << (short)x << ", ";
	std::cout << "(short)y: " << (short)y << std::endl << std::hex;
	std::cout << "(short)x: 0x" << (short)x << ", ";
	std::cout << "(short)y: 0x" << (short)y << std::endl;
	std::cout << "x.boolsgn: " << x.boolsgn() << ", ";
	std::cout << "y.boolsgn: " << y.boolsgn() << std::endl;
	std::cout << "x.size: " << x.size() << ", ";
	std::cout << "y.size: " << y.size() << std::endl;
	std::cout << "x[0]: " << (uintmax_t)x[0] << ", ";
	std::cout << "y[0]: " << (uintmax_t)y[0] << std::endl;
	std::cout << "x.bit(18): " << x.bit(18) << ", ";
	std::cout << "y.bit(18): " << y.bit(18) << std::endl;
	std::cout << "(bool)x: " << (bool)x << ", ";
	std::cout << "(bool)y: " << (bool)y << std::endl;
	std::cout << "x.sgn: " << x.sgn() << ", ";
	std::cout << "y.sgn: " << y.sgn() << std::endl;
	std::cout << "!x: " << !x << ", ";
	std::cout << "!y: " << !y << std::endl;
	std::cout << "y&&x: " << (y && x) << std::endl;
	std::cout << "x||y: " << (x || y) << std::endl;
	std::cout << "x==y: " << (x == y) << ", ";
	std::cout << "x!=y: " << (x != y) << std::endl;
	std::cout << "x>y: " << (x > y) << ", ";
	std::cout << "x<y: " << (x < y) << ", ";
	std::cout << "x>=y: " << (x >= y) << ", ";
	std::cout << "x<=y: " << (x <= y) << std::endl;
	std::cout << "x&y: " << (intmax_t)(x & y) << ", ";
	std::cout << "x|y: " << (intmax_t)(x | y) << ", ";
	std::cout << "x^y: " << (intmax_t)(x ^ y) << std::endl;
	return 0;
}