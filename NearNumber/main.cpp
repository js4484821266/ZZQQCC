#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x;
	x = 5000000000;
	auto y = (uintmax_t)x;
	std::cout << x.size() << std::endl;
	std::cout << y << std::endl;
	return 0;
}