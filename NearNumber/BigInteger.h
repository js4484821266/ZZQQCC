#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
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
	auto size(void)const { return m.size(); }
	/* "Ex_xEZ" means "there exists x so that x is an integer." */
	template<typename Ex_xEZ>Ex_xEZ& operator=( Ex_xEZ& x) {
		s = (x < 0); m.clear();
		for (size_t t = 0; t < sizeof(Ex_xEZ); t++)m.push_back(uint8_t(ABS(x) >> (8 * t)));
		fit(); return x;
	}
	template<>BigInteger& operator=<BigInteger>( BigInteger& x) { s = x.boolsgn(); m = x.mantissa(); return x; }
	BigInteger(void) { operator=(0); }
	/* "Ex_xEZ" means "there exists x so that x is an integer." */
	template<typename Ex_xEZ>BigInteger(Ex_xEZ& x) { operator=(x); }
	/* "Ex_xEZ" means "there exists x so that x is an integer." */
	template<typename Ex_xEZ>operator Ex_xEZ()const {
		Ex_xEZ x = 0;
		for (size_t t = 0; t < MIN(m.size(), sizeof(Ex_xEZ)); t++)x |= (Ex_xEZ(m[t]) << (8 * t));
		return x * sgn();
	}
	operator char() const { return(m.size() ? m[0] : 0); }
	operator bool() const {
		for (size_t t = 0; t < m.size(); t++)if (m[t])return true;
		return false;
	}
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
	operator int()const {
		int x = 0;
		for (size_t t = 0; t < MIN(m.size(), sizeof(int)); t++)x |= ((intmax_t)m[t] << (8 * t));
		return x;
	}
	operator unsigned char()const { return (unsigned char)(char)*this; }
	operator unsigned short()const { return (unsigned short)(short)*this; }
	operator unsigned long()const { return(unsigned long)(long)*this; }
	operator unsigned long long()const { return(unsigned long long)(long long) * this; }
	operator unsigned int()const { return (unsigned int)(int)*this; }
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