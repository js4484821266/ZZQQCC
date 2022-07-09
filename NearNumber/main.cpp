#include<iostream>
#include"iZ.h"
int main(void) {
	iZ x = 0x99900000;
	std::cout << (x << 3 + 4 * 3).hexadec(true) << std::endl;
	return 0;
}