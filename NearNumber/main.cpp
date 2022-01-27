#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x;
	__intn y = x = (uintmax_t)1 << 63;
	std::cout << "x = " << (unsigned long long)x << std::endl;
	std::cout << "y = " << (unsigned long long)y << std::endl;
	return 0;
}