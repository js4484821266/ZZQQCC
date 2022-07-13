#include<ctime>
#include<iostream>
#include"ZZ.h"
int main(void) {
	ZZ
		x(std::string(
			"2519590847565789349402718324004839857142928212620403202777713783604366202070"
			"7595556264018525880784406918290641249515082189298559149176184502808489120072"
			"8449926873928072877767359714183472702618963750149718246911650776133798590957"
			"0009733045974880842840179742910064245869181719511874612151517265463228221686"
			"9987549182422433637259085141865462043576798423387184774447920739934236584823"
			"8242811981638150106748104516603773060562016196762561338441436038339044149526"
			"3443219011465754445417842402092461651572335077870774981712577246796292638635"
			"6373289912154831438167899885040445364023527381951378636564391212010397122822"
			"120720357"
		));
	const ZZ
		y(x);
	while (x + y >= 0) {
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
		x -= y;
	}
	return 0;
}