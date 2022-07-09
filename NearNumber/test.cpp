#include<iostream>
#include"iZ.h"
int main(void) {
	iZ x = -1;
	x <<= 15;
	std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	std::cout << x.hexadec(true) << ".sgn()==" << x.sgn() << std::endl;
	std::cout << "(bool)" << x.hexadec(true) << "==" << (bool)x << std::endl;
	std::cout << "!" << x.hexadec(true) << "==" << !x << std::endl;
	std::cout << x.hexadec(true) << "&&1==" << (x && iZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "&&0==" << (x && iZ(0)) << std::endl;
	std::cout << x.hexadec(true) << "||1==" << (x || iZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "||0==" << (x || iZ(0)) << std::endl;
	std::cout << "(short)" << x.hexadec(true) << "==" << (short)x << std::endl;
	std::cout << std::endl;

	x = 0;
	x <<= 100;
	std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	std::cout << x.hexadec(true) << ".sgn()==" << x.sgn() << std::endl;
	std::cout << "(bool)" << x.hexadec(true) << "==" << (bool)x << std::endl;
	std::cout << "!" << x.hexadec(true) << "==" << !x << std::endl ;
	std::cout << x.hexadec(true) << "&&1==" << (x && iZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "&&0==" << (x && iZ(0)) << std::endl;
	std::cout << x.hexadec(true) << "||1==" << (x || iZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "||0==" << (x || iZ(0)) << std::endl;
	std::cout << std::endl;

	x = 1;
	x <<= 15;
	std::cout << x.hexadec(true) << ".sign==" << x.sign << std::endl;
	std::cout << x.hexadec(true) << ".sgn()==" << x.sgn() << std::endl;
	std::cout << "(bool)" << x.hexadec(true) << "==" << (bool)x << std::endl;
	std::cout << "!" << x.hexadec(true) << "==" << !x << std::endl;
	std::cout << x.hexadec(true) << "&&1==" << (x && iZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "&&0==" << (x && iZ(0)) << std::endl;
	std::cout << x.hexadec(true) << "||1==" << (x || iZ(1)) << std::endl;
	std::cout << x.hexadec(true) << "||0==" << (x || iZ(0)) << std::endl;
	std::cout << "(short)" << x.hexadec(true) << "==" << (short)x << std::endl;
	std::cout << "(int)" << x.hexadec(true) << "==" << (int)x << std::endl;
	std::cout << std::endl;

	x =x<< 17;
	iZ s(x);
	std::cout <<"("<<x.hexadec() << "=="<<s.hexadec() << ")=="<<(x==s) << std::endl;
	std::cout << "(" << x.hexadec() << "!=" << s.hexadec() << ")==" << (x != s) << std::endl;
	s[0] = 1;
	std::cout << "(" << x.hexadec() << "==" << s.hexadec() << ")==" << (x == s) << std::endl;
	std::cout << "(" << x.hexadec() << "!=" << s.hexadec() << ")==" << (x != s) << std::endl;
	std::cout << "(" << x.hexadec() << ">" << s.hexadec() << ")==" << (x > s) << std::endl;
	std::cout << "(" << s.hexadec() << ">" << x.hexadec() << ")==" << (x < s) << std::endl;
	s=s << (int)sizeof(iiunitt)*8;
	std::cout << "(" << x.hexadec() << ">" << s.hexadec() << ")==" << (x > s) << std::endl;
	std::cout << "(" << s.hexadec() << ">" << x.hexadec() << ")==" << (x < s) << std::endl;
	std::cout <<std::endl;

	x = INT64_MAX;
	x <<= 100;
	std::cout << x.hexadec(true) << ".size()==" << x.size() << std::endl;
	auto t = x.size();
	for (t = 0; t < x.size(); t++)
		std::cout << x.hexadec(true) << "[" << x.size() - 1 - t << "]==" << x[x.size() - 1 - t] << std::endl;
	x >>= 104;
	t = x.size() * sizeof(iiunitt) * 8 - 1;
	std::cout << x.hexadec(true) << ".bit(" << 58 << ")==" << x.bit(58) << std::endl;
	return 0;
}