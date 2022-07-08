#pragma once
#include<cstdint>
#include<vector>
#include<string>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?-1:1)
#define ABS(x) ((x)<0?-(x):(x))
typedef unsigned int iiunitt;
class idigits :public std::vector<iiunitt> {
public:
	idigits& addz(idigits& x) {
		const auto 
			n = this->size(),
			xn = x.size(),
			minn=MIN(n,xn),
			b=sizeof(iiunitt)*8;
		if(n<xn)
			this->resize(xn);
		for (
			size_t t = 0;
			t < minn;
			t++
			) {
			const auto 
				eaxn = this->operator[](t) & x[t],
				eaxo = this->operator[](t) | x[t];
			bool carry = false;
			for (
				size_t i = 0;
				i < b;
				i++
				) {
				if (!(eaxo & (1 << (b - 1 - i))))
					break;
				if (eaxn & (1 << (b - 1 - i))) {
					carry = true;
					break;
				}
			}
			if (carry) {
				idigits i;
				i.resize(t + 1);
				i.push_back(1);
				addz(i);
			}
		}
		return*this;
	}
	idigits& subz(idigits& x) {
		return*this;
	}
};

class intbig {
	idigits mant;
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
	const idigits& mantissa(void) const {
		return mant;
	}

	/* Returns size of the mantissa vector. */
	const size_t size(void)const {
		return mant.size();
	}

	/* Returns a hexadecimal string of this. */
	const std::string hexadec(bool prefix = false)const {
		std::string out;
		const auto n = size();
		const size_t nx = sizeof(iiunitt) * 2;
		char temp[6], * tempp = new char[nx + 1 + 2 + 1];
		sprintf_s(tempp, nx + 1 + 2 + 1, "%s%s%X", sign ? "-" : "", prefix ? "0x" : "", mant.back());
		out += tempp;
		for (
			size_t t = 0;
			t < n - 1;
			t++
			) {
			sprintf_s(temp, 6, "%%0%zuX", nx);
			sprintf_s(tempp, nx + 1, temp, mant[n - 2 - t]);
			out += tempp;
		}
		delete[]tempp;
		return out;
	}

	/* Returns a unit of the mantissa vector. */
	const iiunitt& operator[](const size_t& index) const {
		return mant[index];
	}
	iiunitt& operator[](const size_t& index) {
		return mant[index];
	}

	/* Returns a bit of the mantissa vector in boolean form. */
	const bool bit(const size_t& index) const {
		return!!(operator[](index / (8 * sizeof(iiunitt))) & (1 << (index % (8 * sizeof(iiunitt)))));
	}

	/* Initialises this to a copy of an object. */
	intbig& operator=(intbig& x) {
		sign = x.boolsgn();
		mant = x.mantissa();
		return x;
	}
	intbig(const intbig& x) :
		sign(x.boolsgn()),
		mant(x.mantissa()) {  }

	/* Initialises this to an integer. */
	const intmax_t& operator=(const intmax_t& x) {
		const size_t nbyte = MAX(sizeof(intmax_t) / sizeof(iiunitt), 1);
		const uintmax_t a = ABS(x);
		const auto b = sizeof(iiunitt) * 8;
		sign = x < 0;
		mant.clear();
		for (
			size_t t = 0;
			t < nbyte;
			t++
			)
			mant.push_back(
				iiunitt(
					a >> (b * t)
				)
			);
		shorten();
		return x;
	}
	intbig(const intmax_t& x = 0) { operator=(x); }

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
		const auto n = MAX(MIN(size() * sizeof(iiunitt), sizeof(xEZ)) / sizeof(iiunitt), 1),
			b = sizeof(iiunitt) * 8;
		for (
			size_t t = 0;
			t < n;
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
	const bool operator&&(const intbig& x)const {
		return operator bool() && (bool)x;
	}

	/* Performs a logical OR comparison with an object. */
	const bool operator||(const intbig& x) const {
		return operator bool() || (bool)x;
	}

	/* Checks if this has the value equal to that of an object. */
	const bool operator==(const intbig& x)const {
		return sign == x.boolsgn() && mant == x.mantissa();
	}

	/* Checks if this has the value NOT equal to that of an object. */
	const bool operator!=(const intbig& x)const {
		return!operator==(x);
	}

	/* Checks if this has a value greater than that of an object. */
	const bool operator>(const intbig& x) const {
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
	const bool operator>=(const intbig& x)const {
		return operator>(x) || operator==(x);
	}

	/* Checks if this has a value less than that of an object. */
	const bool operator<(const intbig& x) const {
		return !operator>=(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	const bool operator<=(const intbig& x)const {
		return !operator>(x);
	}

	/* Takes the value of bitwise AND operation. */
	intbig& operator&=(const intbig& x) {
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
	intbig operator&(const intbig& x)  const {
		intbig t = *this;
		return t &= x;
	}

	/* Takes the value of bitwise OR operation. */
	intbig& operator|=(const intbig& x) {
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
	intbig operator|(const intbig& x) const {
		intbig t = *this;
		return t |= x;
	}

	/* Takes the value of bitwise XOR operation. */
	intbig& operator^=(const intbig& x) {
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
	intbig operator^(const intbig& x) const {
		intbig t = *this;
		return t ^= x;
	}

	/* "xEZ" means "x is an arbitrary integer."
	   Takes the value whose bits are shifted. */
	template<typename xEZ>
	intbig& operator<<=(const xEZ& x) {
		const size_t
			a = ABS(x),
			b = sizeof(iiunitt) * 8,
			adb = a / b,
			n = size(),
			amb = a % b,
			bamb = b - amb;
		size_t t = 0;
		mant.resize(n + 1);
		if (x < 0) {
			if (amb) {
				for (t = 0; t < n - adb; t++) {
					iiunitt
						& madbt = mant[adb + t],
						& madbt1 = mant[adb + t + 1];
					mant[t] = (madbt1 << bamb) | ((madbt >> amb) & ((1 << bamb) - 1));
					madbt1 &= -(1 << amb);
					madbt &= ((1 << amb) - 1);
				}
			}
			else {
				for (t = 0; t < n - adb; t++) {
					iiunitt& madbt = mant[adb + t];
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
					iiunitt
						& mzadbt = mant[n - 1 + adb - t],
						& mzadbt1 = mant[n - 1 + adb - t + 1],
						& mzt = mant[n - 1 - t];
					const iiunitt temp = mzt;
					mzt = 0;
					mzadbt1 |= (temp >> bamb) & ((1 << amb) - 1);
					mzadbt |= temp << amb;
				}
			}
			else {
				for (t = 0; t < n; t++) {
					iiunitt& mzt = mant[n - 1 - t];
					mant[n - 1 - t + adb] = mzt;
					mzt = 0;
				}
			}
		}
		shorten();
		return*this;
	}
	template<typename xEZ>
	intbig& operator>>=(const xEZ& x) {
		return operator<<=(-x);
	}
	template<typename xEZ>
	intbig operator<<(const xEZ& x)const {
		intbig t = *this;
		return t <<= x;
	}
	template<typename xEZ>
	intbig operator>>(const xEZ& x) const {
		intbig t = *this;
		return t >>= x;
	}

	/* Takes the value of addition. */
	intbig& operator+=(intbig& x) {
		return*this;
	}
	intbig operator+(intbig& x)const {
		intbig t = *this;
		return t += x;
	}
};