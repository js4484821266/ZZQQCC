#pragma once
#include<cstdint>
#include<vector>
#include<string>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?-1:1)
#define ABS(x) ((x)<0?-(x):(x))
/*
1. Declare a variable so that a loop takes not much time.
2. Values be constants as many as possible.
3. Use their reference to save more space.
*/
class BigInteger {
	bool s = 0;
	typedef unsigned int unitt;
	typedef std::vector<unitt> mantissat;
	mantissat m;
	const size_t ubitn;

	void shorten(void) {
		while (m.size() > 1)
			if (!m.back())
				m.pop_back();
			else
				break;
	}

public:

	/* Returns boolean sign: true if negative, and false otherwise. */
	const bool& boolsgn(void) const {
		return s;
	}

	/* Returns a reference to a vector (a flexible array) of mantissa. */
	const mantissat& mantissa(void) const {
		return m;
	}

	/* Returns size of the mantissa vector, a flexible array. */
	const size_t size(void)const {
		return m.size();
	}

	/* Returns a unit of the mantissa vector. */
	const unitt& operator[](const size_t& index) const {
		return m[index];
	}
	unitt& operator[](const size_t& index) {
		return m[index];
	}

	/* Returns a bit of the mantissa vector in boolean form. */
	const bool bit(const size_t& index) const {
		return!!(operator[](index / (8 * sizeof(unitt))) & (1 << (index % (8 * sizeof(unitt)))));
	}

	/* Initialises this to a copy of an object. */
	BigInteger& operator=(BigInteger& x) {
		s = x.boolsgn();
		m = x.mantissa();
		return x;
	}
	BigInteger(const BigInteger& x) :
		ubitn(sizeof(unitt) * 8),
		s(x.boolsgn()),
		m(x.mantissa()) {}

	/* Initialises this to an integer. */
	const intmax_t& operator=(const intmax_t& x) {
		const size_t nbyte = MAX(sizeof(intmax_t) / sizeof(unitt), 1);
		const intmax_t a = ABS(x);
		m.clear();
		for (
			size_t t = 0;
			t < nbyte;
			t++
			)
			m.push_back(
				unitt(
					a >> (ubitn * t)
				)
			);
		shorten();
		return x;
	}
	BigInteger(const intmax_t& x = 0) :
		ubitn(sizeof(unitt) * 8),
		s(x < 0) {
		operator=(x);
	}

	/* Casts this to a boolean. */
	operator bool() const {
		const size_t n = size();
		for (
			size_t t = 0;
			t < n;
			t++
			)
			if (operator[](t))
				return true;
		return false;
	}

	/* Returns arithmetic sign: -1 if negative, 1 if positive, and 0 otherwise. */
	const intmax_t sgn(void) const {
		return (1 - 2 * (intmax_t)s) * operator bool();
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Casts this to an integer. */
	template<typename xEZ>
	operator xEZ() const {
		xEZ x = 0;
		const auto minn = MAX(MIN(size() * sizeof(unitt), sizeof(xEZ)) / sizeof(unitt), 1);
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			x |= (xEZ(operator[](t)) << (ubitn * t));
		return xEZ(x * sgn());
	}

	/* Checks if 0. */
	const bool operator!()const {
		return !operator bool();
	}

	/* Performs a logical AND comparison with an object. */
	const bool operator&&(const BigInteger& x)const {
		return operator bool() && (bool)x;
	}

	/* Performs a logical OR comparison with an object. */
	const bool operator||(const BigInteger& x) const {
		return operator bool() || (bool)x;
	}

	/* Checks if this has the value equal to that of an object. */
	const bool operator==(const BigInteger& x)const {
		return s == x.boolsgn() && m == x.mantissa();
	}

	/* Checks if this has the value NOT equal to that of an object. */
	const bool operator!=(const BigInteger& x)const {
		return!operator==(x);
	}

	/* Checks if this has a value greater than that of an object. */
	const bool operator>(const BigInteger& x) const {
		if (s != x.boolsgn())
			return x.boolsgn();
		else if (size() != x.size())
			return (size() > x.size()) != s;
		else {
			size_t t = size();
			while (t) {
				--t;
				if (operator[](t) > x[t])
					return!s;
			}
			return false;
		}
	}

	/* Checks if this has a value less than that of an object. */
	const bool operator<(const BigInteger& x) const {
		return !operator>(x) && !operator==(x);
	}

	/* Checks if this has a value greater than or equal to that of an object. */
	const bool operator>=(const BigInteger& x)const {
		return!operator<(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	const bool operator<=(const BigInteger& x)const {
		return !operator>(x);
	}

	/* Takes the value of bitwise AND operation. */
	BigInteger& operator&=(const BigInteger& x) {
		s = s && x.boolsgn();
		const size_t minn = MIN(size(), x.size());
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			m[t] &= x[t];
		if (size() > x.size())
			m.resize(x.size());
		return*this;
	}

	/* Returns the value of bitwise AND operation. */
	BigInteger operator&(const BigInteger& x)  const {
		BigInteger t = *this;
		return t &= x;
	}

	/* Takes the value of bitwise OR operation. */
	BigInteger& operator|=(const BigInteger& x) {
		s = s || x.boolsgn();
		const size_t minn = MIN(size(), x.size());
		const auto xn = x.size();
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			m[t] |= x[t];
		if (size() < xn)
			for (
				size_t t = size();
				t < xn;
				t++
				)
				m.push_back(x[t]);
		return*this;
	}

	/* Returns the value of bitwise OR operation. */
	BigInteger operator|(const BigInteger& x) const {
		BigInteger t = *this;
		return t |= x;
	}

	/* Takes the value of bitwise XOR operation. */
	BigInteger& operator^=(const BigInteger& x) {
		s = s != x.boolsgn();
		const size_t minn = MIN(size(), x.size());
		const auto xn = x.size();
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			m[t] ^= x[t];
		if (size() < xn)
			for (
				size_t t = size();
				t < xn;
				t++
				)
				m.push_back(x[t]);
		return*this;
	}

	/* Returns the value of bitwise XOR operation. */
	BigInteger operator^(const BigInteger& x) const {
		BigInteger t = *this;
		return t ^= x;
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Takes the value whose bits are shifted. */
	template<typename xEZ>
	BigInteger& operator<<=(const xEZ& x) {
		const size_t
			p = ABS(x),
			d = p / ubitn,
			n = size();
		if (x < 0) {
			//TODO
		}
		else if (!x);
		else {
			//TODO
		}
		shorten();
		return*this;
	}
	template<typename xEZ>
	BigInteger& operator>>=(const xEZ& x) {
		return operator<<=(-x);
	}
	template<typename xEZ>
	BigInteger operator<<(const xEZ& x)const {
		BigInteger t = *this;
		return t <<= x;
	}
	template<typename xEZ>
	BigInteger operator>>(const xEZ& x) const {
		BigInteger t = *this;
		return t >>= x;
	}

	/* Returns a hexadecimal string of this. */
	const std::string _16(bool specified = false)const {
		std::string out;
		const size_t nx = sizeof(unitt) * 2;
		char temp[6], * tempp = new char[nx + 1 + 2 + 1];
		sprintf_s(tempp, nx + 1 + 2 + 1, "%s%s%X", s ? "-" : "", specified ? "0x" : "", m.back());
		out += tempp;
		for (
			intmax_t t = size() - 2;
			t >= 0;
			t--
			) {
			sprintf_s(temp, 6, "%%0%zuX", nx);
			sprintf_s(tempp, nx + 1, temp, m[t]);
			out += tempp;
		}
		delete[]tempp;
		return out;
	}
};