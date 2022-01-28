#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x;
	x = (uintmax_t)1 << 63;
	__intn y = +x;
	std::cout << x.size() << std::endl;
	std::cout << y.size() << std::endl;
	return 0;
}