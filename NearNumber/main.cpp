#include<iostream>
#include"NearNumber.h"
int main(void) {
	__intn x;
	__intn y=x = 0x123456789abcdef0;
	std::cout << (unsigned long long)x;
	return 0;
}