#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x(0xaaaaaaaa);
	__intn y(0x55555555);
	std::cout <<
		"x: " << (intmax_t)x <<
		", y: " << (intmax_t)y << std::endl <<
		"x: " << std::hex << std::showbase << (intmax_t)x <<
		", y: " << (intmax_t)y << std::endl <<
		"x.sgn: " << x.sgn() <<
		", y.sgn: " << y.sgn() << std::endl <<
		"x.boolsgn: " << x.boolsgn() <<
		", y.boolsgn: " << y.boolsgn() << std::endl <<
		"x.size: " << x.size() <<
		", y.size: " << y.size() << std::endl <<
		"x.b(0): " << x.b(0) <<
		", y.b(0): " << y.b(0) << std::endl <<
		"(bool)x: " << (bool)x <<
		", (bool)y: " << (bool)y << std::endl <<
		"!x: " << !x <<
		", !y: " << !y << std::endl <<
		"y&&x: " << (y && x) <<
		", y&&9: " << (y && 9) << std::endl <<
		"y||x: " << (y || x) <<
		", x||0: " << (x || 0) << std::endl <<
		"x==y: " << (x == y) <<
		", x!=y: " << (x != y) << std::endl <<
		"x>y: " << (x > y) <<
		", x<y: " << (x < y) <<
		", x>=y: " << (x >= y) <<
		", x<=y: " << (x <= y) << std::endl <<
		"x&y: " << (intmax_t)(x & y) <<
		", x|y: " << (intmax_t)(x | y) <<
		", x^y: " << (intmax_t)(x ^ y) << std::endl;
	return 0;
}