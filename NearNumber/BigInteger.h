#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?-1:1)
#define ABS(x) ((x)<0?-(x):(x))
class BigInteger {
	bool s = 0;
	typedef unsigned int unitt;
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

	/* Returns boolean sign: true if negative, and false otherwise. */
	bool boolsgn(void) const {
		return s;
	}

	/* Returns a reference to a vector (a flexible array) of mantissa. */
	const mantissat& mantissa(void) const {
		return m;
	}

	/* Returns size of the mantissa vector, a flexible array. */
	size_t size(void)const {
		return m.size();
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Returns a unit of the mantissa vector. */
	template<typename xEZ>
	const unitt& operator[](const xEZ& index) const {
		return m[index];
	}
	template<typename xEZ>
	unitt& operator[](const xEZ& index) {
		return m[index];
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Returns a bit of the mantissa vector in boolean form. */
	template<typename xEZ>
	bool bit(const xEZ& index) const {
		return!!(operator[](index / (8 * sizeof(unitt))) & (1 << (index % (8 * sizeof(unitt)))));
	}

	/* Initialises this to a copy of an object. */
	BigInteger(const BigInteger& x) :s(x.boolsgn()), m(x.mantissa()) {}

	/* "xEZ" means "x is an arbitrary integer."
	   Initialises this to an arbitrary integer. */
	template<typename xEZ>
	BigInteger(const xEZ& x = 0) {
		s = (x < 0);
		m.clear();
		for (
			size_t t = 0;
			t < MAX(sizeof(xEZ) / sizeof(unitt), 1);
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

	/* Returns arithmetic sign: -1 if negative, 1 if positive, and 0 otherwise. */
	int sgn(void) const {
		return (1 - 2 * (int)s) * operator bool();
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Casts this to an integer. */
	template<typename xEZ>
	operator xEZ() const {
		xEZ x = 0;
		for (
			size_t t = 0;
			t < MIN(size() * sizeof(unitt), sizeof(xEZ)) / sizeof(unitt);
			t++
			)
			x |= (xEZ(operator[](t)) << (sizeof(unitt) * 8 * t));
		return x * sgn();
	}

	/* Checks if 0. */
	bool operator!()const {
		return !operator bool();
	}

	/* Performs a logical AND comparison with an object. */
	const bool operator&&(BigInteger& x)const {
		return operator bool() && (bool)x;
	}

	/* Performs a logical OR comparison with an object. */
	const bool operator||(BigInteger& x) const {
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
	const bool operator>(BigInteger& x) const {
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
				return false;
			}
	}

	/* Checks if this has a value less than that of an object. */
	const bool operator<(BigInteger& x) const {
		return !operator>(x) && !operator==(x);
	}

	/* Checks if this has a value greater than or equal to that of an object. */
	const bool operator>=(BigInteger& x)const {
		return!operator<(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	const bool operator<=(BigInteger& x)const {
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
				size_t t = size();
				t <  x.size();
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
				size_t t = size();
				t < x.size();
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

	/* "xEZ" means "x is an arbitrary integer."
	   Takes the value whose bits are shifted. */
	template<typename xEZ>
	BigInteger& operator<<=(const xEZ& x) {
		size_t
			p = ABS(x),
			b = 8 * sizeof(unitt);
		if (x < 0) {
			/*for (
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
					if (w)
						u ^= flag;
					if (w != y)
						v ^= glag;
			}*/
			if (!(p % b)) {
				for (
					size_t t = 0;
					t < p / b;
					t++
					) {

				}
			}
		}
		else if (!x);
		else {
			size_t q = size();
			m.resize((q * b + p) / 8 + 1);
			for (
				size_t t = 0;
				t < q * b;
				t++
				) {
				unitt& u = operator[]((q* b - 1 - t + p) / b),
					flag = 1 << ((q * b - 1 - t + p) % b);
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
	const std::string _16(void)const {
		std::string out;
		for (
			size_t t = 0;
			t < size();
			t++
			) {
			// TODO
		}
	}
};