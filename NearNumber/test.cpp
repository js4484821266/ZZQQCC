#include<iostream>
#include"iZ.h"
int main(void) {
	iZ x = -1; std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	x = 0; std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	x = 1; std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	x = UINT64_MAX; std::cout << x.hexadec(true) << ".size()==" << x.size() << std::endl;
	std::cout <<x.hexadec()<<"[0]==" << x[0] << std::endl;
	return 0;
}