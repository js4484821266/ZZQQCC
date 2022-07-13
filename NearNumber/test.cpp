#include<ctime>
#include<iostream>
#include"ZZ.h"
int main(void) {
	ZZ
		x(std::string(
			"2519590847 5657893494 0271832400 4839857142 9282126204 0320277771 3783604366 202070"
			"7595556264 0185258807 8440691829 0641249515 0821892985 5914917618 4502808489 120072"
			"8449926873 9280728777 6735971418 3472702618 9637501497 1824691165 0776133798 590957"
			"0009733045 9748808428 4017974291 0064245869 1817195118 7461215151 7265463228 221686"
			"9987549182 4224336372 5908514186 5462043576 7984233871 8477444792 0739934236 584823"
			"8242811981 6381501067 4810451660 3773060562 0161967625 6133844143 6038339044 149526"
			"3443219011 4657544454 1784240209 2461651572 3350778707 7498171257 7246796292 638635"
			"6373289912 1548314381 6789988504 0445364023 5273819513 7863656439 1212010397 122822"
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