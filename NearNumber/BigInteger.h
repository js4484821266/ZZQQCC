#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)>=0?intmax_t(1):-intmax_t(1))
#define BOOLSGN(x) ((x)<0)
#define ABS(x) ((x)>=0?(x):-(x))
typedef std::vector<uint8_t> mantissat;
class BigInteger {
	bool s = 0;
	mantissat m;
public:
	intmax_t sgn(void) const { return 1 - 2 * (intmax_t)s; }
	bool boolsgn(void)const { return s; }
	BigInteger& fit(void) {
		for (size_t t = 1; t < m.size(); t++)if (!m[m.size() - t])m.pop_back();
		return*this;
	}
	mantissat mantissa(void)const { return m; }
	BigInteger& operator=(BigInteger& x) { s = x.boolsgn(); m = x.mantissa(); return x; }
	intmax_t& operator=(intmax_t& x) {
		intmax_t t = ABS(x);
		s = BOOLSGN(x);
		m.clear();
		for (size_t u = 0; u < sizeof(intmax_t); u++)m.push_back((t >> (8 * u)) & 0xff);
		fit();
		return x;
	}
	BigInteger(BigInteger& x) { operator=(x); }
	BigInteger(intmax_t x = 0) { operator=(x); }
	operator int()const {
		int x = 0;
		for (size_t t = 0; t < MIN(m.size(), sizeof(int)); t++)x |= ((intmax_t)m[t] << (8 * t));
		return x;
	}
	operator bool() const {
		for (size_t t = 0; t < m.size(); t++)if (m[t])return true;
		return false;
	}
	operator char() const { return(m.size() ? m[0] : 0); }
	operator short()const {
		short x = 0;
		for (size_t t = 0; t < MIN(m.size(), 2); t++)x |= ((intmax_t)m[t] << (8 * t));
		return x;
	}
	operator long()const {
		long x = 0;
		for (size_t t = 0; t < MIN(m.size(), 4); t++)x |= ((intmax_t)m[t] << (8 * t));
		return x;
	}
	operator long long()const {
		long long x = 0;
		for (size_t t = 0; t < MIN(m.size(), 8); t++)x |= ((intmax_t)m[t] << (8 * t));
		return x;
	}
	operator unsigned int()const { return (unsigned int)(int)*this; }
	operator unsigned char()const { return (unsigned char)(char)*this; }
	operator unsigned short()const { return (unsigned short)(short)*this; }
	operator unsigned long()const { return(unsigned long)(long)*this; }
	operator unsigned long long()const { return(unsigned long long)(long long) * this; }
	bool operator!() const { return !operator bool(); }
	bool operator&&(BigInteger x)const { return operator bool() && (bool)x; }
	template<typename Ax>bool operator&&(Ax x) const { return operator bool() && !!x; }
	bool operator||(BigInteger x) const { return operator bool() || (bool)x; }
	template<typename Ax>bool operator||(Ax x)const { return operator bool() || !!x; }
	BigInteger operator+()const;
	bool operator==(BigInteger x)const;
	bool operator>(BigInteger x)const;
	bool operator<(BigInteger x)const;
	bool operator!=(BigInteger x)const;
	bool operator>=(BigInteger x)const;
	bool operator<=(BigInteger x)const;
	BigInteger operator~()const;
	BigInteger operator&(BigInteger x)const;
	BigInteger operator|(BigInteger x)const;
	BigInteger operator^(BigInteger x)const;
	BigInteger operator<<(BigInteger x)const;
	BigInteger operator>>(BigInteger x)const;
	BigInteger operator+(BigInteger x)const;
	BigInteger operator-(BigInteger x)const;
	BigInteger operator*(BigInteger x)const;
	BigInteger operator/(BigInteger x)const;
	BigInteger operator%(BigInteger x)const;
	BigInteger operator-()const;
};
typedef BigInteger __intn;