#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x;
	__intn y = x = (uintmax_t)1 << 63;
	std::cout << "x = " << std::hex << std::showbase << (unsigned long long)x << std::endl;
	std::cout << "y = " << std::hex << std::showbase << (unsigned long long)y << std::endl;
	std::cout << uintmax_t(-5) * -1 << std::endl;
	return 0;
}