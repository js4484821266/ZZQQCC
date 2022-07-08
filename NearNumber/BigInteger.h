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
template< typename unitt = unsigned int>
class idigits :public std::vector<unitt> {
public:
	idigits& addz(idigits& x) {
		const unitt msbf4rs = unitt(1) << (sizeof(unitt) * 8 - 1);
		const auto n = this->size();
		const auto xn = x.size();
		this->resize(MAX(n, xn) + 1);
		for (
			int t = 0;
			t < n;
			t++
			) {
			auto andz = this->operator[](t) & x[t];
			auto orz = this->operator[](t) | x[t];
		}
		return*this;
	}
	idigits& difz(idigits& x) {
		return*this;
	}
};

class BigInteger {
	typedef unsigned int unitt;
	typedef idigits<unitt> mantissat;
	mantissat mant;
	void shorten(void) {
		while (mant.size() > 1)
			if (!mant.back())
				mant.pop_back();
			else
				break;
	}
public:
	bool sign = 0;

	/* Returns boolean sign: true if negative, and false otherwise. */
	const bool& boolsgn(void) const {
		return sign;
	}

	/* Returns a reference to a vector (a flexible array) of mantissa. */
	const mantissat& mantissa(void) const {
		return mant;
	}

	/* Returns size of the mantissa vector, a flexible array. */
	const size_t size(void)const {
		return mant.size();
	}

	/* Returns a hexadecimal string of this. */
	const std::string hexadec(bool prefix = false)const {
		std::string out;
		const size_t nx = sizeof(unitt) * 2;
		char temp[6], * tempp = new char[nx + 1 + 2 + 1];
		sprintf_s(tempp, nx + 1 + 2 + 1, "%s%s%X", sign ? "-" : "", prefix ? "0x" : "", mant.back());
		out += tempp;
		for (
			intmax_t t = size() - 2;
			t >= 0;
			t--
			) {
			sprintf_s(temp, 6, "%%0%zuX", nx);
			sprintf_s(tempp, nx + 1, temp, mant[t]);
			out += tempp;
		}
		delete[]tempp;
		return out;
	}

	/* Returns a unit of the mantissa vector. */
	const unitt& operator[](const size_t& index) const {
		return mant[index];
	}
	unitt& operator[](const size_t& index) {
		return mant[index];
	}

	/* Returns a bit of the mantissa vector in boolean form. */
	const bool bit(const size_t& index) const {
		return!!(operator[](index / (8 * sizeof(unitt))) & (1 << (index % (8 * sizeof(unitt)))));
	}

	/* Initialises this to a copy of an object. */
	BigInteger& operator=(BigInteger& x) {
		sign = x.boolsgn();
		mant = x.mantissa();
		return x;
	}
	BigInteger(const BigInteger& x) :
		sign(x.boolsgn()),
		mant(x.mantissa()) {  }

	/* Initialises this to an integer. */
	const intmax_t& operator=(const intmax_t& x) {
		const size_t nbyte = MAX(sizeof(intmax_t) / sizeof(unitt), 1);
		const uintmax_t a = ABS(x);
		const auto b = sizeof(unitt) * 8;
		sign = x < 0;
		mant.clear();
		for (
			size_t t = 0;
			t < nbyte;
			t++
			)
			mant.push_back(
				unitt(
					a >> (b * t)
				)
			);
		shorten();
		return x;
	}
	BigInteger(const intmax_t& x = 0) { operator=(x); }

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
		if (operator bool())
			if (sign)
				return-1;
			else
				return 1;
		else
			return 0;
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Casts this to an integer. */
	template<typename xEZ>
	operator xEZ() const {
		xEZ x = 0;
		const auto minn = MAX(MIN(size() * sizeof(unitt), sizeof(xEZ)) / sizeof(unitt), 1),
			b = sizeof(unitt) * 8;
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			x |= (xEZ(operator[](t)) << (b * t));
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
		return sign == x.boolsgn() && mant == x.mantissa();
	}

	/* Checks if this has the value NOT equal to that of an object. */
	const bool operator!=(const BigInteger& x)const {
		return!operator==(x);
	}

	/* Checks if this has a value greater than that of an object. */
	const bool operator>(const BigInteger& x) const {
		if (sign != x.boolsgn())
			return x.boolsgn();
		else if (size() != x.size())
			return (size() > x.size()) != sign;
		else {
			size_t t = size();
			while (t) {
				--t;
				if (operator[](t) > x[t])
					return!sign;
			}
			return false;
		}
	}

	/* Checks if this has a value greater than or equal to that of an object. */
	const bool operator>=(const BigInteger& x)const {
		return operator>(x) || operator==(x);
	}

	/* Checks if this has a value less than that of an object. */
	const bool operator<(const BigInteger& x) const {
		return !operator>=(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	const bool operator<=(const BigInteger& x)const {
		return !operator>(x);
	}

	/* Takes the value of bitwise AND operation. */
	BigInteger& operator&=(const BigInteger& x) {
		sign = sign && x.boolsgn();
		const size_t minn = MIN(size(), x.size());
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			mant[t] &= x[t];
		if (size() > x.size())
			mant.resize(x.size());
		return*this;
	}

	/* Returns the value of bitwise AND operation. */
	BigInteger operator&(const BigInteger& x)  const {
		BigInteger t = *this;
		return t &= x;
	}

	/* Takes the value of bitwise OR operation. */
	BigInteger& operator|=(const BigInteger& x) {
		sign = sign || x.boolsgn();
		const size_t minn = MIN(size(), x.size());
		const auto xn = x.size();
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			mant[t] |= x[t];
		if (size() < xn)
			for (
				size_t t = size();
				t < xn;
				t++
				)
				mant.push_back(x[t]);
		return*this;
	}

	/* Returns the value of bitwise OR operation. */
	BigInteger operator|(const BigInteger& x) const {
		BigInteger t = *this;
		return t |= x;
	}

	/* Takes the value of bitwise XOR operation. */
	BigInteger& operator^=(const BigInteger& x) {
		sign = sign != x.boolsgn();
		const size_t minn = MIN(size(), x.size());
		const auto xn = x.size();
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			mant[t] ^= x[t];
		if (size() < xn)
			for (
				size_t t = size();
				t < xn;
				t++
				)
				mant.push_back(x[t]);
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
			a = ABS(x),
			b = sizeof(unitt) * 8,
			adb = a / b,
			n = size(),
			amb = a % b,
			bamb = b - amb;
		size_t t = 0;
		mant.resize(n + 1);
		if (x < 0) {
			if (amb) {
				for (t = 0; t < n - adb; t++) {
					unitt
						& madbt = mant[adb + t],
						& madbt1 = mant[adb + t + 1];
					unitt temp = (madbt1 << bamb) | ((madbt >> amb) & ((1 << bamb) - 1));
					madbt1 &= -(1 << amb);
					madbt &= ((1 << amb) - 1);
					mant[t] = temp;
				}
			}
			else {
				for (t = 0; t < n - adb; t++) {
					unitt& madbt = mant[adb + t];
					mant[t] = madbt;
					madbt = 0;
				}
			}
			mant.resize(n - adb);
		}
		else if (!x);
		else {
			mant.resize(n + adb + 1);
			if (amb) {
				for (t = 0; t < n; t++) {
					unitt
						& mzadbt = mant[n - 1 + adb - t],
						& mzadbt1 = mant[n - 1 + adb - t + 1],
						& mzt = mant[n - 1 - t];
					const unitt temp = mzt;
					mzt = 0;
					mzadbt1 |= (temp >> bamb) & ((1 << amb) - 1);
					mzadbt |= temp << amb;
				}
			}
			else {
				for (t = 0; t < n; t++) {
					unitt& mzt = mant[n - 1 - t];
					mant[n - 1 - t + adb] = mzt;
					mzt = 0;
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

	BigInteger& operator+=(BigInteger& x) {
		x;
		return*this;
	}
	BigInteger operator+(BigInteger& x)const {
		BigInteger t = *this;
		return t += x;
	}
};