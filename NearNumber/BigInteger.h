#pragma once
#include<vector>
#include<cstdint>
typedef std::vector<uint8_t> mantissa_t;
class BigInteger {
	typedef BigInteger nnn;
	bool s = 0;
	mantissa_t m;
public:
	BigInteger(void) {
		m.push_back(0);
	}
	bool sgn(void) { return s; }
	mantissa_t mantissa(void) { return m; }
	operator bool() {
		bool u = false;
		for (size_t t = 0; t < m.size(); t++)u = (u || m[t]);
		return u;
	}
	nnn operator+() { s = false; return*this; }
	nnn operator+(nnn x) {
	}
	nnn operator-() { s = true; return*this; }
	nnn operator-(nnn x);
	nnn operator*(nnn x);
	nnn operator/(nnn x);
	nnn operator%(nnn x);
};
typedef BigInteger __intn;