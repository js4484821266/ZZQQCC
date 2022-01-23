#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)>=0?intmax_t(1):~intmax_t(0))
#define BOOLSGN(x) ((x)<0)
#define ABS(x) ((x)>=0?(x):-(x))
typedef std::vector<uint8_t> mantissat;
class BigInteger {
	bool s = 0;
	mantissat m;
public:
	intmax_t sgn(void) const { return 1 - 2 * (intmax_t)s; }
	bool boolsgn(void)const { return s; }
	BigInteger& clean(void) {
		for (size_t t = 1; t < m.size(); t++)if (!m[m.size() - t])m.pop_back();
		return*this;
	}
	mantissat mantissa(void) { clean(); return m; }
	BigInteger& operator=(BigInteger& x) { s = x.boolsgn(); m = x.mantissa(); return x; }
	template<typename Ex_xEZ>Ex_xEZ& operator=(Ex_xEZ& x) {
		Ex_xEZ t = ABS(x);
		s = BOOLSGN(x);
		m.clear();
		for (size_t u = 0; u < sizeof(Ex_xEZ); u++)m.push_back((t >> (8 * u)) & 0xff);
		clean();
		return x;
	}
	operator bool() {
		for (size_t t = 0; t < m.size(); t++)if (m[t])return true;
		return false;
	}
	operator char() { return(m.size() ? m[0] : 0); }
	operator intmax_t() {
		intmax_t x = 0;
		for (size_t t = 0; t < MIN(m.size(), sizeof(intmax_t)); t++)x |= (m[t] << (8 * t));
		return x;
	}
	bool operator!() { return !operator bool(); }
	bool operator&&(BigInteger x) { return operator bool() && (bool)x; }
	template<typename Ax>bool operator&&(Ax x) { return operator bool() && !!x; }
	bool operator||(BigInteger x) { return operator bool() || (bool)x; }
	template<typename Ax>bool operator||(Ax x) { return operator bool() || !!x; }
	BigInteger operator+() { return*this; }
	bool operator==(BigInteger x) {
	}
	bool operator>(BigInteger x);
	bool operator<(BigInteger x);
	bool operator!=(BigInteger x);
	bool operator>=(BigInteger x);
	bool operator<=(BigInteger x);
	BigInteger operator~();
	BigInteger operator&(BigInteger x);
	BigInteger operator|(BigInteger x);
	BigInteger operator^(BigInteger x);
	BigInteger operator<<(BigInteger x);
	BigInteger operator>>(BigInteger x);
	BigInteger operator+(BigInteger x);
	BigInteger operator-(BigInteger x);
	BigInteger operator*(BigInteger x);
	BigInteger operator/(BigInteger x);
	BigInteger operator%(BigInteger x);
	BigInteger operator-();
};
typedef BigInteger __intn;