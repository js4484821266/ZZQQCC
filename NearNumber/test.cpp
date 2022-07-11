#include<iostream>
#include"ZZ.h"
int main(void) {
	ZZ x = 1;
	while (x + 1 >= 0) {
		std::cout << x.hexadec() << ".sgn()==" << x.sgn() << std::endl;
		std::cout << "!" << x.hexadec() << "==" << !x << std::endl;
		std::cout << x.hexadec() << "&&false==" << (x && false) << std::endl;
		std::cout << x.hexadec() << "&&true==" << (x && true) << std::endl;
		std::cout << x.hexadec() << "||false==" << (x || false) << std::endl;
		std::cout << x.hexadec() << "||true==" << (x || true) << std::endl;
		std::cout << x.hexadec() << "==1==" << (x == 1) << std::endl;
		std::cout << x.hexadec() << "==0==" << (x == 0) << std::endl;
		std::cout << x.hexadec() << "==-1==" << (x == -1) << std::endl;
		std::cout << x.hexadec() << "!=1==" << (x != 1) << std::endl;
		std::cout << x.hexadec() << "!=0==" << (x != 0) << std::endl;
		std::cout << x.hexadec() << "!=-1==" << (x != -1) << std::endl;
		std::cout << x.hexadec() << ">1==" << (x > 1) << std::endl;
		std::cout << x.hexadec() << ">=1==" << (x >= 1) << std::endl;
		std::cout << x.hexadec() << "<1==" << (x < 1) << std::endl;
		std::cout << x.hexadec() << "<=1==" << (x <= 1) << std::endl;
		std::cout << std::endl;
		x -= 1;
	}
	return 0;
}