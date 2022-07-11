#include<iostream>
#include"ZZ.h"
int main(void) {
	ZZ x = -INT32_MAX;
	while (x - INT32_MAX <= 0) {
		std::cout << x.hexadec(true) << ".sgn()        ==        " << x.sgn() << std::endl;
		std::cout << "!" << x.hexadec(true) << "        ==        " << !x << std::endl;
		std::cout << x.hexadec(true) << "&&false        ==        " << (x && false) << std::endl;
		std::cout << x.hexadec(true) << "&&true        ==        " << (x && true) << std::endl;
		std::cout << x.hexadec(true) << "||false        ==        " << (x || false) << std::endl;
		std::cout << x.hexadec(true) << "||true        ==        " << (x || true) << std::endl;
		for (int t = -1; t <= 1; t++)
			std::cout << x.hexadec(true) << "==" << t << "        ==        " << (x == t) << std::endl;
		for (int t = -1; t <= 1; t++)
			std::cout << x.hexadec(true) << "!=" << t << "        ==        " << (x != t) << std::endl;
		for (int t = -1; t <= 1; t++) {
			std::cout << x.hexadec(true) << ">" << t << "        ==        " << (x > t) << std::endl;
			std::cout << x.hexadec(true) << ">=" << t << "        ==        " << (x >= t) << std::endl;
			std::cout << x.hexadec(true) << "<" << t << "        ==        " << (x < t) << std::endl;
			std::cout << x.hexadec(true) << "<=" << t << "        ==        " << (x <= t) << std::endl;
		}
		std::cout << std::endl;
		x += INT32_MAX;
	}
	return 0;
}