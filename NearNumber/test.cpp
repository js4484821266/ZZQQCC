#include<iostream>
#include"ZZ.h"
int main(void) {
	ZZ x = -1;
	x <<= 15;
	std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	std::cout << x.hexadec(true) << ".sgn()==" << x.sgn() << std::endl;
	std::cout << "!" << x.hexadec(true) << "==" << !x << std::endl;
	std::cout << x.hexadec(true) << "&&1==" << (x && ZZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "&&0==" << (x && ZZ(0)) << std::endl;
	std::cout << x.hexadec(true) << "||1==" << (x || ZZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "||0==" << (x || ZZ(0)) << std::endl;
	std::cout << std::endl;

	x = 0;
	x <<= 100;
	std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	std::cout << x.hexadec(true) << ".sgn()==" << x.sgn() << std::endl;
	std::cout << "!" << x.hexadec(true) << "==" << !x << std::endl;
	std::cout << x.hexadec(true) << "&&1==" << (x && ZZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "&&0==" << (x && ZZ(0)) << std::endl;
	std::cout << x.hexadec(true) << "||1==" << (x || ZZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "||0==" << (x || ZZ(0)) << std::endl;
	std::cout << std::endl;

	x = 0x1234567890abcdef;
	x <<= 16;
	std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	std::cout << x.hexadec(true) << ".sgn()==" << x.sgn() << std::endl;
	std::cout << "!" << x.hexadec(true) << "==" << !x << std::endl;
	std::cout << x.hexadec(true) << "&&1==" << (x && ZZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "&&0==" << (x && ZZ(0)) << std::endl;
	std::cout << x.hexadec(true) << "||1==" << (x || ZZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "||0==" << (x || ZZ(0)) << std::endl;
	std::cout << std::endl;

	x = x << (int)sizeof(iiunitt) * 8;
	ZZ s(x);
	std::cout << "(" << x.hexadec(true) << "==" << s.hexadec(true) << ")==" << (x == s) << std::endl;
	std::cout << "(" << x.hexadec(true) << "!=" << s.hexadec(true) << ")==" << (x != s) << std::endl;
	s[0] = 1;
	std::cout << "(" << x.hexadec(true) << "==" << s.hexadec(true) << ")==" << (x == s) << std::endl;
	std::cout << "(" << x.hexadec(true) << "!=" << s.hexadec(true) << ")==" << (x != s) << std::endl;
	std::cout << "(" << x.hexadec(true) << ">" << s.hexadec(true) << ")==" << (x > s) << std::endl;
	std::cout << "(" << s.hexadec(true) << ">" << x.hexadec(true) << ")==" << (x < s) << std::endl;
	s = s << (int)sizeof(iiunitt) * 8;
	std::cout << "(" << x.hexadec(true) << ">" << s.hexadec(true) << ")==" << (x > s) << std::endl;
	std::cout << "(" << s.hexadec(true) << ">" << x.hexadec(true) << ")==" << (x < s) << std::endl;
	std::cout << std::endl;

	x = INT64_MAX;
	x <<= 100 - 4;
	std::cout << x.hexadec(true) << ".size()==" << x.size() << std::endl;
	auto t = x.size();
	for (t = 0; t < x.size(); t++)
		std::cout << x.hexadec(true) << "[" << x.size() - 1 - t << "]==" << x[x.size() - 1 - t] << std::endl;
	x >>= 104;
	t = x.size() * sizeof(iiunitt) * 8 - 1;
	std::cout << x.hexadec(true) << ".bit(" << 58 << ")==" << x.bit(58) << std::endl;
	std::cout << std::endl;

	x = ZZ(100000000000000);
	std::cout << x.hexadec(true) << std::endl;
	std::cout << (x * (ZZ(100000000000000))).hexadec(true) << std::endl;
	return 0;
}