#pragma once
#include<cstdint>
#include<cstdlib>
#include<vector>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
typedef std::vector<uint8_t> mantissat;
class BigInteger {
	typedef BigInteger nnn;
	bool s = 0;
	mantissat m;
public:
	bool sgn(void) { return s; }
	mantissat mantissa(void) { return m; }
	operator bool() {
		bool u = false;
		for (size_t t = 0; t < m.size(); t++)u = (u || m[t]);
		return u;
	}
	operator char() { return(m.size() ? m[0] : 0); }
	template<typename tempt>operator tempt() {
		tempt x = 0;
		for (size_t t = 0; t < min(m.size(), sizeof(tempt)); t++)x |= (m[t] << (8 * t));
		return x;
	}
	bool operator!();
	bool operator&&(nnn x);
	bool operator||(nnn x);
	nnn operator+(nnn x);
	nnn operator-(nnn x);
	nnn operator*(nnn x);
	nnn operator/(nnn x);
	nnn operator%(nnn x);
	bool operator==(nnn x);
	bool operator!=(nnn x);
	bool operator>(nnn x);
	bool operator>=(nnn x);
	bool operator<(nnn x);
	bool operator<=(nnn x);
};
typedef BigInteger __intn;