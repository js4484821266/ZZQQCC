#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x = 0x44444;
	__intn y = 4294967296;
	std::cout << "x: " << (intmax_t)x << ", ";
	std::cout << "y: " << (intmax_t)y << std::endl << std::hex;
	std::cout << "x: " << (intmax_t)x << ", ";
	std::cout << "y: " << (intmax_t)y << std::endl;
	std::cout << "x.sgn: " << x.sgn() << ", ";
	std::cout << "y.sgn: " << y.sgn() << std::endl;
	std::cout << "x.boolsgn: " << x.boolsgn() << ", ";
	std::cout << "y.boolsgn: " << y.boolsgn() << std::endl;
	std::cout << "x.length: " << x.length() << ", ";
	std::cout << "y.length: " << y.length() << std::endl;
	std::cout << "x.invert: " << (intmax_t)x.invert() << ", ";
	std::cout << "x.invert.invert: " << (intmax_t)x.invert() << std::endl;
	std::cout << "x[0]: " << (uintmax_t)x[0] << ", ";
	std::cout << "y[0]: " << (uintmax_t)y[0] << std::endl;
	std::cout << "x.bit(0): " << x.bit(0) << ", ";
	std::cout << "y.bit(0): " << y.bit(0) << std::endl;
	std::cout << "(bool)x: " << (bool)x << ", ";
	std::cout << "(bool)y: " << (bool)y << std::endl;
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