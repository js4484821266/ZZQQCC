#pragma once
#include<cstdint>
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
	nnn& clean(void) {
		for (size_t t = 1; t < m.size(); t++)if (!m[m.size() - t])m.pop_back();
		return*this;
	}
	nnn& operator=(nnn x) { s = x.sgn(); m = x.mantissa(); return x; }
	/* "Ex_xEZ" means "there exists x so that x is an element of Z." */
	template<typename Ex_xEZ>Ex_xEZ& operator=(Ex_xEZ x);
	operator bool() {
		bool u = false;
		for (size_t t = 0; t < m.size(); t++)u = (u || m[t]);
		return u;
	}
	operator char() { return(m.size() ? m[0] : 0); }
	template<typename Ex_xEZ>operator Ex_xEZ() {
		Ex_xEZ x = 0;
		for (size_t t = 0; t < min(m.size(), sizeof(Ex_xEZ)); t++)x |= (m[t] << (8 * t));
		return x;
	}
	bool operator!() { return !operator bool(); }
	bool operator&&(nnn x) { return operator bool() && (bool)x; }
	template<typename Ax>bool operator&&(Ax x) { return operator bool() && !!x; }
	bool operator||(nnn x) { return operator bool() || (bool)x; }
	template<typename Ax>bool operator||(Ax x) { return operator bool() || !!x; }
	nnn operator+() { return*this; }
	bool operator==(nnn x) {

	}
	bool operator>(nnn x);
	bool operator<(nnn x);
	bool operator!=(nnn x);
	bool operator>=(nnn x);
	bool operator<=(nnn x);
	nnn operator~();
	nnn operator&(nnn x);
	nnn operator|(nnn x);
	nnn operator^(nnn x);
	nnn operator<<(nnn x);
	nnn operator>>(nnn x);
	nnn operator+(nnn x);
	nnn operator-(nnn x);
	nnn operator*(nnn x);
	nnn operator/(nnn x);
	nnn operator%(nnn x);
	nnn operator-();
};
typedef BigInteger __intn;