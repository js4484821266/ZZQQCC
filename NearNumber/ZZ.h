#pragma once
#include<cstdint>
#include<vector>
#include<string>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?-1:1)
#define ABS(x) ((x)<0?-(x):(x))
//An abbreviation of "integer-integer unit type."
typedef unsigned int iiunitt;
class idigits :public std::vector<iiunitt> {
public:
	idigits& addz(const idigits& x) {
		const auto
			b = sizeof(iiunitt) * 8,
			n = size(),
			xn = x.size();
		if (n < xn)
			resize(xn);
		for (
			size_t t = 0;
			t < xn;
			t++
			) {
			auto& pt = at(t);
			auto& xpt = x.at(t);
			const auto
				eaxn = pt & xpt,
				eaxo = pt | xpt;
			pt += xpt;
			for (
				size_t i = 0;
				i < b;
				i++
				) {
				if (!(eaxo & (1 << (b - 1 - i))))
					break;
				if (eaxn & (1 << (b - 1 - i))) {
					idigits j;
					j.resize(t + 1);
					j.push_back(1);
					addz(j);
					break;
				}
			}
		}
		return*this;
	}
	bool operator>(const idigits& x)const {
		if (size() != x.size())
			return size() > x.size();
		else {
			for (
				idigits::const_reverse_iterator it = rbegin();
				it < rend();
				it++
				) {
				if (*it > x.at(it - rbegin()))
					return true;
			}
			return false;
		}
	}
	idigits& subz(idigits x) {
		const auto
			n = size(),
			xn = x.size();
		if (n < xn)
			resize(xn);
		if (operator>(x))
			swap(x);
		for (
			size_t t = 0;
			t < xn;
			t++
			) {
			if (at(t) < x.at(t)) {
				idigits i;
				i.resize(t + 1);
				i.push_back(1);
				subz(i);
			}
			at(t) -= x.at(t);
		}
		return*this;
	}
};

class ZZ {
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

	ZZ operator-()const {
		ZZ t = *this;
		t.sign = !t.sign;
		return t;
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
		return mant.at(index);
	}
	iiunitt& operator[](const size_t& index) {
		return mant.at(index);
	}

	/* Returns a bit of the mantissa vector in boolean form. */
	const bool bit(const size_t& index) const {
		return!!(mant.at(index / (8 * sizeof(iiunitt))) & (1 << (index % (8 * sizeof(iiunitt)))));
	}

	/* Initialises this to a copy of an object. */
	const ZZ& operator=(const ZZ& x) {
		sign = x.sign;
		mant = x.mantissa();
		return x;
	}
	ZZ(const ZZ& x) :
		sign(x.sign),
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
	ZZ(const intmax_t& x = 0) { operator=(x); }

	/* Returns arithmetic sign: -1 if negative, 1 if positive, and 0 otherwise. */
	const intmax_t sgn(void) const {
		if (size() == 1 && !mant.at(0))
			return 0;
		else
			if (sign)
				return-1;
			else
				return 1;
	}

	/* Checks if 0. */
	const bool operator!()const {
		return (size() == 1 && !mant.at(0));
	}

	/* Performs a logical AND comparison with an object. */
	const bool operator&&(const ZZ& x)const {
		return!(operator!() || !x);
	}

	/* Performs a logical OR comparison with an object. */
	const bool operator||(const ZZ& x) const {
		return!(operator!() && !x);
	}

	/* Checks if this has the value equal to that of an object. */
	const bool operator==(const ZZ& x)const {
		return sign == x.sign && mant == x.mantissa();
	}

	/* Checks if this has the value NOT equal to that of an object. */
	const bool operator!=(const ZZ& x)const {
		return!operator==(x);
	}

	/* Checks if this has a value greater than that of an object. */
	const bool operator>(const ZZ& x) const {
		if (sign != x.sign)
			return x.sign;
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
	const bool operator>=(const ZZ& x)const {
		return operator>(x) || operator==(x);
	}

	/* Checks if this has a value less than that of an object. */
	const bool operator<(const ZZ& x) const {
		return !operator>=(x);
	}

	/* Checks if this has a value less than or equal to that of an object. */
	const bool operator<=(const ZZ& x)const {
		return !operator>(x);
	}

	/* Takes the value of bitwise AND operation. */
	ZZ& operator&=(const ZZ& x) {
		sign = sign && x.sign;
		const size_t minn = MIN(size(), x.size());
		for (
			size_t t = 0;
			t < minn;
			t++
			)
			mant[t] &= x[t];
		if (size() > x.size())
			mant.resize(x.size());
		shorten();
		return*this;
	}

	/* Returns the value of bitwise AND operation. */
	ZZ operator&(const ZZ& x)  const {
		ZZ t = *this;
		return t &= x;
	}

	/* Takes the value of bitwise OR operation. */
	ZZ& operator|=(const ZZ& x) {
		sign = sign || x.sign;
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
		shorten();
		return*this;
	}

	/* Returns the value of bitwise OR operation. */
	ZZ operator|(const ZZ& x) const {
		ZZ t = *this;
		return t |= x;
	}

	/* Takes the value of bitwise XOR operation. */
	ZZ& operator^=(const ZZ& x) {
		sign = sign != x.sign;
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
		shorten();
		return*this;
	}

	/* Returns the value of bitwise XOR operation. */
	ZZ operator^(const ZZ& x) const {
		ZZ t = *this;
		return t ^= x;
	}

	/* Takes the value whose bits are shifted. */
	ZZ& operator<<=(const int& x) {
		const size_t
			a = ABS(x),
			b = sizeof(iiunitt) * 8,
			adb = a / b,
			n = size(),
			amb = a % b,
			bamb = b - amb;
		size_t t = 0;
		mant.push_back(0);
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
	ZZ& operator>>=(const int& x) {
		return operator<<=(-x);
	}
	ZZ operator<<(const int& x)const {
		ZZ t = *this;
		return t <<= x;
	}
	ZZ operator>>(const int& x) const {
		ZZ t = *this;
		return t >>= x;
	}

	/* Takes the value of addition. */
	ZZ& operator+=(ZZ x) {
		bool xsgn = x.sign;
		if (sign == xsgn)
			mant.addz(x.mantissa());
		else {
			mant.subz(x.mantissa());
			x.sign = 0;
			if (operator<(x))
				sign = xsgn;
		}
		shorten();
		return*this;
	}
	ZZ operator+(const ZZ& x)const {
		ZZ t = *this;
		return t += x;
	}
	ZZ& operator-=(const ZZ& x) {
		return operator+=(-x);
	}
	ZZ operator-(const ZZ& x)const {
		ZZ t = *this;
		return t -= x;
	}

	ZZ& operator*=(const ZZ& x) {
		idigits::const_iterator
			it = x.mantissa().begin(),
			ii = it,
			jt = x.mantissa().end();
		idigits::iterator
			iitt = mant.begin(),
			iiii = iitt,
			jjtt = mant.end();
		const auto b = sizeof(*it) * 8;
		ZZ temp = *this;
		while (iitt < jjtt)
			*(iitt++) = 0;
		while (it < jt) {
			for (
				size_t q = 0;
				q < b;
				q++
				)
				if (*it & (1 << q))
					operator+=(temp<<int((it - ii) * b + q));
			it++;
		}
		sign = sign != x.sign;
		shorten();
		return*this;
	}
	ZZ operator*(const ZZ& x)const {
		ZZ t = *this;
		return t *= x;
	}
};