#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?intmax_t(-1):intmax_t(1))
#define ABS(x) ((x)*SGN(x))
class BigInteger {
	bool s = 0;
	typedef  uint8_t unitt;
	typedef std::vector<unitt> mantissat;
	mantissat m;

	void shorten(void) {
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

	/* Takes and returns the invert element of addition of this. */
	BigInteger& invert(void) {
		s = !s;
		return*this;
	}

	/* "ExEZ" means "there exists x, a general integer."
	   Returns a unit of the mantissa vector. */
	template<typename ExEZ>
	unitt& operator[](const ExEZ& index) {
		return m[index];
	}

	/* "ExEZ" means "there exists x, a general integer."
	   Returns a bit of the mantissa vector in boolean form. */
	template<typename ExEZ>
	const bool bit(const ExEZ& index) {
		return!!(operator[](index / (8 * sizeof(unitt))) & (1 << (index % (8 * sizeof(unitt)))));
	}

	/* Initialises this to a copy of an object. */
	BigInteger(const BigInteger& x) :s(x.boolsgn()), m(x.mantissa()) {}

	/* "ExEZ" means "there exists x, a general integer."
	   Initialises this to a general integer. */
	template<typename ExEZ>
	BigInteger(const ExEZ& x = 0) {
		s = (x < 0);
		m.clear();
		for (
			size_t t = 0;
			t < MAX(sizeof(ExEZ) / sizeof(unitt), 1);
			t++
			)
			m.push_back(
				unitt(
					ABS(x) >> (sizeof(unitt) * 8 * t)
				)
			);
		shorten();
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
			t < MIN(size() * sizeof(unitt), sizeof(ExEZ)) / sizeof(unitt);
			t++
			)
			x |= (ExEZ(operator[](t)) << (sizeof(unitt) * 8 * t));
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

	/* "ExEZ" means "there exists x, a general integer."
	   Takes the value whose bits are shifted. */
	template<typename ExEZ>
	BigInteger& operator<<=(const ExEZ& x) {
		size_t
			p = ABS(x),
			b = 8 * sizeof(unitt),
			t = 0;
		if (x < 0) {
			for (
				t = 0;
				t < size() * b - p;
				t++
				) {
				unitt& u = operator[]((t + p) / b),
					flag = 1 << ((t + p) % b);
				bool w = !!(u & flag);
				unitt& v = operator[](t / b),
					glag = 1 << (t % b);
				bool y = !!(v & glag);
				if (x < 0) {
					if (w)
						u ^= flag;
					if (w != y)
						v ^= glag;
				}
			}
		}
		else if (!x);
		else {
			size_t q = size();
			m.resize((q * b + p) / 8 + 1);
			for (
				t = 0;
				t < q * b;
				t++
				) {
				unitt& u = operator[]((q* b - 1 - t + p) / b),
					flag = 1 << ((q * b - 1 - t + p) % b);
				bool w = !!(u & flag);
				unitt& v = operator[]((q* b - 1 - t) / b),
					glag = 1 << ((q * b - 1 - t) % b);
				bool y = !!(v & glag);
				if (y) {
					v ^= glag;
					u ^= flag;
				}
			}
		}
		shorten();
		return*this;
	}
	template<typename ExEZ>
	BigInteger& operator>>=(const ExEZ& x) {
		return operator<<=(-x);
	}

	template<typename ExEZ>
	BigInteger operator<<(const ExEZ& x) {
		BigInteger t = *this;
		return t <<= x;
	}
	template<typename ExEZ>
	BigInteger operator>>(const ExEZ& x) {
		BigInteger t = *this;
		return t >>= x;
	}
};
typedef BigInteger __intn;