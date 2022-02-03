#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x(4294967304);
	__intn y('5' * '5');
	std::cout << "x: " << (intmax_t)x << ", ";
	std::cout << "y: " << (intmax_t)y << std::endl << std::hex;
	std::cout << "x: " << (intmax_t)x << ", ";
	std::cout << "y: " << (intmax_t)y << std::endl;
	std::cout << "x.sgn: " << x.sgn() << ", ";
	std::cout << "y.sgn: " << y.sgn() << std::endl;
	std::cout << "x.boolsgn: " << x.boolsgn() << ", ";
	std::cout << "y.boolsgn: " << y.boolsgn() << std::endl;
	std::cout << "x.size: " << x.size() << ", ";
	std::cout << "y.size: " << y.size() << std::endl;
	std::cout << "x.invert: " << (intmax_t)x.invert() << ", ";
	std::cout << "x.invert.invert: " << (intmax_t)x.invert() << std::endl;
	std::cout << "x[0]: " << (uintmax_t)x[1] << ", ";
	std::cout << "y[0]: " << (uintmax_t)y[1] << std::endl;
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