#include<iostream>
#include"NearNumber.h"
int main(void) {
	BigInteger x = 0xdeadbeef;
	BigInteger y = 0;
	std::cout << "x: " << (short)x << ", ";
	std::cout << "y: " << (short)y << std::endl << std::hex;
	std::cout << "x: " << (short)x << ", ";
	std::cout << "y: " << (short)y << std::endl;
	std::cout << "x.boolsgn: " << x.boolsgn() << ", ";
	std::cout << "y.boolsgn: " << y.boolsgn() << std::endl;
	std::cout << "x.size: " << x.size() << ", ";
	std::cout << "y.size: " << y.size() << std::endl;
	std::cout << "x[0]: " << (uintmax_t)x[0] << ", ";
	std::cout << "y[0]: " << (uintmax_t)y[0] << std::endl;
	std::cout << "x.bit(0): " << x.bit(0) << ", ";
	std::cout << "y.bit(0): " << y.bit(0) << std::endl;
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
	std::cout << "x<<5: " << (intmax_t)(x << 5) << std::endl;
	std::cout << "x<<-5: " << (intmax_t)(x << -5) << std::endl;
	std::cout << "x>>5: " << (intmax_t)(x >> 5) << std::endl;
	std::cout << "x>>-5: " << (intmax_t)(x >> -5) << std::endl;
	return 0;
}