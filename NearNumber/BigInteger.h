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
	void fit(void) {
		while (m.size())
			if (!m.back())
				m.pop_back();
			else
				break;
	}
public:
	intmax_t sgn(void) const {
		return 1 - 2 * (intmax_t)s;
	}
	bool boolsgn(void)const {
		return s;
	}
	const mantissat& mantissa(void)const {
		return m;
	}
	size_t size(void)const {
		return m.size();
	}
	BigInteger& operator=(BigInteger& x) {
		s = x.boolsgn();
		m = x.mantissa();
		return x;
	}
	/* "Ex_xEZ" means "there exists x so that x is an integer." */
	template<typename Ex_xEZ>
	const Ex_xEZ& operator=(const Ex_xEZ& x) {
		s = (x < 0);
		m.clear();
		for (
			size_t t = 0;
			t < sizeof(Ex_xEZ);
			t++
			)
			m.push_back(
				uint8_t(ABS(x) >> (8 * t))
			);
		fit();
		return x;
	}
	BigInteger(void) {
		operator=(0);
	}
	BigInteger(BigInteger& x) {
		operator=(x);
	}
	/* "Ex_xEZ" means "there exists x so that x is an integer." */
	template<typename Ex_xEZ>
	BigInteger(Ex_xEZ& x) {
		operator=(x);
	}
	operator char() const {
		return(m.size() ? m[0] : 0);
	}
	operator bool() const {
		for (
			size_t t = 0;
			t < m.size();
			t++
			)
			if (m[t])
				return true;
		return false;
	}
	/* "Ex_xEZ" means "there exists x so that x is an integer." */
	template<typename Ex_xEZ>
	operator Ex_xEZ()const {
		Ex_xEZ x = 0;
		for (
			size_t t = 0;
			t < MIN(m.size(), sizeof(Ex_xEZ));
			t++
			)
			x |= (Ex_xEZ(m[t]) << (8 * t));
		return x * sgn();
	}
	bool operator!() const {
		return !operator bool();
	}
	bool operator&&(BigInteger x)const {
		return operator bool() && (bool)x;
	}
	/* "Ax" means "for all x so that x is an integer." */
	template<typename Ax>
	bool operator&&(Ax x) const {
		return operator bool() && !!x;
	}
	bool operator||(BigInteger x) const {
		return operator bool() || (bool)x;
	}
	/* "Ax" means "for all x so that x is an integer." */
	template<typename Ax>
	bool operator||(Ax x)const {
		return operator bool() || !!x;
	}
	bool operator==(BigInteger x)const;
	bool operator>(BigInteger x)const;
	bool operator<(BigInteger x)const;
	bool operator!=(BigInteger x)const;
	bool operator>=(BigInteger x)const;
	bool operator<=(BigInteger x)const;
	BigInteger operator+()const;
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