#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x(-0);
	__intn y(-5000000001);
	std::cout <<
		"x: " << (intmax_t)x <<
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
		"y&&x: " << (y && x) << std::endl <<
		"y&&9: " << (y && 9) << std::endl <<
		"y||x: " << (y || x) << std::endl <<
		"x||0: " << (x || 0) << std::endl;
	return 0;
}