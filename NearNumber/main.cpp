#include<iostream>
#include"intbig.h"
int main(void) {
	intbig x = 0x123456789abcdef0;
	std::cout << (x << 4).hexadec(true) << std::endl;
	return 0;
}