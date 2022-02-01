#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?intmax_t(-1):intmax_t(1))
#define ABS(x) ((x)*SGN(x))
class BigInteger {
	bool s = 0;
	typedef  uint8_t digitt;
	typedef std::vector<digitt> mantissat;
	mantissat m;

	void fit(void) {
		while (m.size() > 1)
			if (!m.back())
				m.pop_back();
			else
				break;
	}

public:

	/* Returns arithmetic sign: -1 if negative, and 1 otherwise. */
	const intmax_t sgn(void) const {
		return 1 - 2 * (intmax_t)s;
	}

	/* Returns boolean sign: true if negative, and false otherwise. */
	const bool& boolsgn(void) const{
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
	digitt& operator[](const size_t& index) {
		return m[index];
	}

	/* Returns a bit of the mantissa vector in boolean form. */
	const bool bit(const size_t& index) {
		return!!(operator[](index / (8 * sizeof(digitt))) & (1 << (index % (8 * sizeof(digitt)))));
	}

	/* Initialises this to a copy of an object. */
	BigInteger(const BigInteger& x) :s(x.boolsgn()), m(x.mantissa()) {}

	/* Initialises this to a general integer. */
	BigInteger(const intmax_t& x = 0) {
		s = (x < 0);
		m.clear();
		for (
			size_t t = 0;
			t < sizeof(intmax_t) / sizeof(digitt);
			t++
			)
			m.push_back(
				digitt(
					ABS(x) >> (sizeof(digitt) * 8 * t)
				)
			);
		fit();
	}

	/* Casts this to a boolean. */
	operator bool() {
		for (
			size_t t = 0;
			t < size();
			t++
			)
			if (operator[](t))
				return true;
		return false;
	}

	/* "ExEZ" means "there exists x, an integer."
	   Casts this to a general integer. */
	template<typename ExEZ>
	operator ExEZ() {
		ExEZ x = 0;
		for (
			size_t t = 0;
			t < MIN(size() * sizeof(digitt), sizeof(ExEZ)) / sizeof(digitt);
			t++
			)
			x |= (ExEZ(operator[](t)) << (sizeof(digitt) * 8 * t));
		return x * sgn();
	}

	/* Checks if 0. */
	const bool operator!() {
		return !operator bool();
	}

	/* Performs a logical AND comparison with an object. */
	const bool operator&&(BigInteger& x) {
		return operator bool() && (bool)x;
	}

	/* Performs a logical OR comparison with an object. */
	const bool operator||(BigInteger& x) {
		return operator bool() || (bool)x;
	}

	/* Checks if this has the value equal to that of an object. */
	const bool operator==(BigInteger& x)const {
		return s == x.boolsgn() && m == x.mantissa();
	}

	/* Checks if this has the value NOT equal to that of an object. */
	const bool operator!=(BigInteger& x)const {
		return!operator==(x);
	}

	/* Checks if this has a value greater than that of an object. */
	const bool operator>(BigInteger& x) {
		if (s != x.boolsgn())
			return x.boolsgn();
		else
			if (size() != x.size())
				return (size() > x.size()) != s;
			else {
				size_t t = size();
				while (t) {
					--t;
					if (operator[](t) > x[t])
						return!s;
				}
				return s;
			}
	}

	/* Checks if this has a value less than that of an object. */
	const bool operator<(BigInteger& x) {
		return !operator>(x) && !operator==(x);
	}

	/* Checks if this has a value greater than or equal to that of an object. */
	const bool operator>=(BigInteger& x) {
		return!operator<(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	const bool operator<=(BigInteger& x) {
		return !operator>(x);
	}

	/* Takes the value of bitwise AND operation. */
	BigInteger& operator&=(BigInteger& x) {
		s = s && x.boolsgn();
		for (
			size_t t = 0;
			t < MIN(size(), x.size());
			t++
			)
			m[t] &= x[t];
		if (size() > x.size())
			m.resize(x.size());
		return*this;
	}

	/* Returns the value of bitwise AND operation. */
	BigInteger operator&(BigInteger& x)  const {
		BigInteger t = *this;
		return t &= x;
	}

	/* Takes the value of bitwise OR operation. */
	BigInteger& operator|=(BigInteger& x) {
		s = s || x.boolsgn();
		for (
			size_t t = 0;
			t < MIN(size(), x.size());
			t++
			)
			m[t] |= x[t];
		if (size() < x.size())
			for (
				size_t t = MIN(size(), x.size());
				t < MAX(size(), x.size());
				t++
				)
				m.push_back(x[t]);
		return*this;
	}

	/* Returns the value of bitwise OR operation. */
	BigInteger operator|(BigInteger& x) const {
		BigInteger t = *this;
		return t |= x;
	}

	/* Takes the value of bitwise XOR operation. */
	BigInteger& operator^=(BigInteger& x) {
		s = s != x.boolsgn();
		for (
			size_t t = 0;
			t < MIN(size(), x.size());
			t++
			)
			m[t] ^= x[t];
		if (size() < x.size())
			for (
				size_t t = MIN(size(), x.size());
				t < MAX(size(), x.size());
				t++
				)
				m.push_back(x[t]);
		return*this;
	}

	/* Returns the value of bitwise XOR operation. */
	BigInteger operator^(BigInteger& x) const {
		BigInteger t = *this;
		return t ^= x;
	}

	/* Takes the value whose bits are shifted. */
	BigInteger& operator<<=(const intmax_t&x) {
		if (x < 0) {
			for (
				size_t t = 0;
				t < size() * 8 - x;
				t++
				) {
				// TODO
			}
		}
		else;
	}
	BigInteger& operator>>=(const intmax_t& x) {
		if (x < 0)
			return operator<<=(-x);
		else
			return operator<<=(x);
	}
};
typedef BigInteger __intn;