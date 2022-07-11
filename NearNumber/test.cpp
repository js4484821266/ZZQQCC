#include<iostream>
#include"ZZ.h"
int main(void) {
	ZZ x = 1;
	x <<= 64;
	std::cout <<"x.size()==" << x.size() << std::endl;
	return 0;
}