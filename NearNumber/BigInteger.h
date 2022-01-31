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
	intmax_t sgn(void) const {
		return 1 - 2 * (intmax_t)s;
	}

	/* Returns boolean sign: true if negative, and false otherwise. */
	bool boolsgn(void)const {
		return s;
	}

	/* Returns a reference to a vector (a flexible array) of mantissa. */
	const mantissat& mantissa(void)const {
		return m;
	}

	/* Returns size of the mantissa vector, a flexible array. */
	size_t size(void)const {
		return m.size();
	}

	/* Returns a unit of the mantissa vector. */
	const digitt& operator[](size_t index) const {
		return m[index];
	}

	/* Returns a bit of the mantissa vector in boolean form. */
	bool b(size_t index)const {
		return!!(operator[](index / (8 * sizeof(digitt))) & (1 << (index % (8 * sizeof(digitt)))));
	}

	/* Copies the object into this. */
	const BigInteger& operator=(const BigInteger& x) {
		s = x.boolsgn();
		m = x.mantissa();
		return x;
	}

	/* "ExEZ" means "there exists x, an integer."
	   Splits a general integer into units and puts them into this. */
	template<typename ExEZ>
	const ExEZ operator=(const ExEZ x) {
		s = (x < 0);
		m.clear();
		for (
			size_t t = 0;
			t < sizeof(ExEZ) / sizeof(digitt);
			t++
			)
			m.push_back(
				digitt(
					ABS(x) >> (sizeof(digitt) * 8 * t)
				)
			);
		fit();
		return x;
	}

	/* Initialises this to 0. */
	BigInteger(void) {
		operator=(0);
	}

	/* Initialises this to a copy of an object. */
	BigInteger(const BigInteger& x) {
		operator=(x);
	}

	/* "ExEZ" means "there exists x, an integer."
	   Initialises this to a general integer. */
	template<typename ExEZ>
	BigInteger(const ExEZ x) {
		operator=(x);
	}

	/* Casts this to a boolean. */
	operator bool() const {
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
	operator ExEZ()const {
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
	bool operator!() const {
		return !operator bool();
	}

	/* Performs a logical AND comparison with an object. */
	bool operator&&(const BigInteger& x)const {
		return operator bool() && (bool)x;
	}

	/* "Ax" means "for all x."
	   Performs a logical AND comparison with a general integer. */
	template<typename Ax>
	bool operator&&(const Ax x) const {
		return operator bool() && x;
	}

	/* Performs a logical OR comparison with an object. */
	bool operator||(const BigInteger& x) const {
		return operator bool() || (bool)x;
	}

	/* "Ax" means "for all x."
	   Performs a logical OR comparison with a general integer. */
	template<typename Ax>
	bool operator||(const Ax x)const {
		return operator bool() || x;
	}

	/* Checks if this has the value equal to that of an object. */
	bool operator==(const BigInteger& x)const {
		return s == x.boolsgn() && m == x.mantissa();
	}

	/* Checks if this has the value NOT equal to that of an object. */
	bool operator!=(const BigInteger& x)const {
		return!operator==(x);
	}

	/* Checks if this has a value greater than that of an object. */
	bool operator>(const BigInteger& x)const {
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
	bool operator<(const BigInteger& x)const {
		return !operator>(x) && !operator==(x);
	}

	/* Checks if this has a value greater than or equal to that of an object. */
	bool operator>=(const BigInteger& x)const {
		return!operator<(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	bool operator<=(const BigInteger& x)const {
		return !operator>(x);
	}

	/* Takes the value of bitwise AND operation. */
	const BigInteger& operator&=(const BigInteger& x) {
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
	const BigInteger operator&(const BigInteger& x) {
		BigInteger t = *this;
		return t &= x;
	}

	/* Takes the value of bitwise OR operation. */
	const BigInteger& operator|=(const BigInteger& x) {
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
	const BigInteger operator|(const BigInteger& x) {
		BigInteger t = *this;
		return t |= x;
	}

	/* Takes the value of bitwise OR operation. */
	const BigInteger& operator^=(const BigInteger& x) {
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
	/* Returns the value of bitwise OR operation. */
	const BigInteger operator^(const BigInteger& x) {
		BigInteger t = *this;
		return t ^= x;
	}

	/* Takes the value whose bits are shifted. */
	const BigInteger& operator<<=(const BigInteger& x);
};
typedef BigInteger __intn;