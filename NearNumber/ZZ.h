#pragma once
#include<cstdint>
#include<string>
#include"idigits.h"
/*
'ZZ' is an extended integer class.
This class has been named as 'ZZ' because it is to represent more integers,
and 'ZZ' seems like the blackboard bold letter of Z.
*/
class ZZ {
private:
	idigits mant;
public:
	//Boolean sign.
	bool sign = 0;

	//Returns a reference to the mantissa.
	const idigits& mantissa(void) const;

	//Returns the number of elements to represent the integer.
	const size_t size(void)const;

	//Returns a constant reference to a specified element of the mantissa.
	const iiunitt& operator[](const size_t&) const;
	//Returns a reference to a specified element of the mantissa.
	iiunitt& operator[](const size_t&);

	//Returns SGN function.
	const intmax_t sgn(void) const;

	//Checks if this is 0.
	const bool operator!()const;

	//Checks if this and x are both non-zero.
	const bool operator&&(const ZZ&)const;
	//Checks if this or x is non-zero.
	const bool operator||(const ZZ&) const;

	//Checks if this is equal to x.
	const bool operator==(const ZZ&)const;
	//Checks if this differs from x.
	const bool operator!=(const ZZ&)const;

	//Returns a string representing this in base 16.
	const std::string hexadec(bool)const;

	//Checks if this is greater than x.
	const bool operator>(const ZZ&) const;
	//Checks if this is greater than or equal to x.
	const bool operator>=(const ZZ&)const;
	//Checks if this is less than x.
	const bool operator<(const ZZ&) const;
	//Checks if this is less than or equal to x.
	const bool operator<=(const ZZ&)const;

	//Takes a copy of x.
	const ZZ& operator=(const ZZ&);
	//Constructor when x is a variable of this class.
	ZZ(const ZZ&);

	//Assigns x to this, where x is a common integer.
	const intmax_t& operator=(const intmax_t&);
	//Default constructor
	ZZ(const intmax_t&);

	//Returns absolute value of this.
	ZZ abs(void)const;

	//Returns additive inverse of this.
	ZZ operator-()const;

	//Adds x to this.
	ZZ& operator+=(const ZZ&);
	//Returns total of this and x.
	ZZ operator+(const ZZ&)const;
	//Subtracts x from this.
	ZZ& operator-=(const ZZ&);
	//Returns the result of subtraction of x from this.
	ZZ operator-(const ZZ&)const;
	//Increases this by 1.
	ZZ& operator++();
	//Decreases this by 1.
	ZZ& operator--();

	/* This takes the value of bitwise AND operation. */
	ZZ& operator&=(const ZZ&);
	/* Returns the value of bitwise AND operation. */
	ZZ operator&(const ZZ&)  const;

	/* This takes the value of bitwise OR operation. */
	ZZ& operator|=(const ZZ&);
	/* Returns the value of bitwise OR operation. */
	ZZ operator|(const ZZ&) const;

	/* This takes the value of bitwise XOR operation. */
	ZZ& operator^=(const ZZ&);
	/* Returns the value of bitwise XOR operation. */
	ZZ operator^(const ZZ&) const;

	/* This takes the value whose bits have been shifted to the left. */
	ZZ& operator<<=(const intmax_t&);
	/* This takes the value whose bits have been shifted to the right. */
	ZZ& operator>>=(const intmax_t&);
	/* Returns the value whose bits have been shifted to the left. */
	ZZ operator<<(const intmax_t&)const;
	/* Returns the value whose bits have been shifted to the right. */
	ZZ operator>>(const intmax_t&) const;

	//Multiplicates this by x.
	ZZ& operator*=(const ZZ&);
	//Returns the result of multiplication of this and x.
	ZZ operator*(const ZZ&)const;
	ZZ& operator=(const std::string& x);
	ZZ(const std::string& x);

	/* Performs division by x.
	   This takes the remainder and quotient_here takes the quotient. */
	ZZ& QR(const ZZ&, ZZ&);
	/* Not recommended.
	   Takes and returns the result of division of this and x. */
	ZZ operator/=(const ZZ& x);
	/* Not recommended.
	   Returns the result of division of this and x. */
	ZZ operator/(const ZZ& x) const;
	/* Not recommended.
	   Takes and returns the remainder of division of this and x. */
	ZZ operator%=(const ZZ& x);
	/* Not recommended.
	   Returns the remainder of division of this and x. */
	ZZ operator%(const ZZ& x) const;
};

const idigits& ZZ::mantissa(void) const {
	return mant;
}
const size_t ZZ::size(void)const {
	return mant.size();
}
const iiunitt& ZZ::operator[](const size_t& index) const {
	return mant.at(index);
}
iiunitt& ZZ::operator[](const size_t& index) {
	return mant.at(index);
}
const intmax_t ZZ::sgn(void) const {
	if (this->operator!())
		return 0;
	else
		if (sign)
			return-1;
		else
			return 1;
}
const bool ZZ::operator!()const {
	return (size() == 1 && !mant.at(0));
}
const bool ZZ::operator&&(const ZZ& x)const {
	return!(operator!() || !x);
}
const bool ZZ::operator||(const ZZ& x) const {
	return!(operator!() && !x);
}
const bool ZZ::operator==(const ZZ& x)const {
	return sign == x.sign && mant == x.mantissa();
}
const bool ZZ::operator!=(const ZZ& x)const {
	return!operator==(x);
}
const std::string ZZ::hexadec(bool prefix = false)const {
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
const bool ZZ:: operator>(const ZZ& x) const {
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
const bool ZZ::operator>=(const ZZ& x)const {
	return operator>(x) || operator==(x);
}
const bool ZZ::operator<(const ZZ& x) const {
	return !operator>=(x);
}
const bool ZZ::operator<=(const ZZ& x)const {
	return !operator>(x);
}
const ZZ& ZZ::operator=(const ZZ& x) {
	sign = x.sign;
	mant = x.mantissa();
	return x;
}
ZZ::ZZ(const ZZ& x) :
	sign(x.sign),
	mant(x.mantissa()) {  }
const intmax_t& ZZ::operator=(const intmax_t& x) {
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
	mant.shorten();
	return x;
}
ZZ::ZZ(const intmax_t& x = 0) { operator=(x); }
ZZ ZZ::abs(void)const {
	ZZ t = *this;
	t.sign = false;
	return t;
}
ZZ ZZ::operator-()const {
	ZZ t = *this;
	t.sign = !t.sign;
	return t;
}
ZZ& ZZ::operator+=(const ZZ& x) {
	if (sign == x.sign)
		mant.addz(x.mantissa());
	else {
		if (abs() < x.abs())
			sign = x.sign;
		mant.difz(x.mantissa());
	}
	mant.shorten();
	sign = sign && !operator!();
	return*this;
}
ZZ ZZ::operator+(const ZZ& x)const {
	ZZ t = *this;
	return t += x;
}
ZZ& ZZ::operator-=(const ZZ& x) {
	return operator+=(-x);
}
ZZ ZZ::operator-(const ZZ& x)const {
	ZZ t = *this;
	return t -= x;
}
ZZ& ZZ::operator++() {
	return operator+=(1);
}
ZZ& ZZ::operator--() {
	return operator-=(1);
}
ZZ& ZZ::operator&=(const ZZ& x) {
	sign = sign && x.sign;
	const size_t minn = MIN(size(), x.size());
	for (
		size_t t = 0;
		t < minn;
		t++
		)
		mant.at(t) &= x[t];
	if (size() > x.size())
		mant.resize(x.size());
	mant.shorten();
	return*this;
}
ZZ ZZ::operator&(const ZZ& x)  const {
	ZZ t = *this;
	return t &= x;
}
ZZ& ZZ:: operator|=(const ZZ& x) {
	sign = sign || x.sign;
	const size_t minn = MIN(size(), x.size());
	const auto xn = x.size();
	for (
		size_t t = 0;
		t < minn;
		t++
		)
		mant.at(t) |= x[t];
	if (size() < xn)
		for (
			size_t t = size();
			t < xn;
			t++
			)
			mant.push_back(x[t]);
	mant.shorten();
	return*this;
}
ZZ ZZ::operator|(const ZZ& x) const {
	ZZ t = *this;
	return t |= x;
}
ZZ& ZZ::operator^=(const ZZ& x) {
	sign = sign != x.sign;
	const size_t minn = MIN(size(), x.size());
	const auto xn = x.size();
	for (
		size_t t = 0;
		t < minn;
		t++
		)
		mant.at(t) ^= x[t];
	if (size() < xn)
		for (
			size_t t = size();
			t < xn;
			t++
			)
			mant.push_back(x[t]);
	mant.shorten();
	return*this;
}
ZZ ZZ::operator^(const ZZ& x) const {
	ZZ t = *this;
	return t ^= x;
}
ZZ& ZZ::operator<<=(const intmax_t& x) {
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
	mant.shorten();
	return*this;
}
ZZ& ZZ::operator>>=(const intmax_t& x) {
	return operator<<=(-x);
}
ZZ ZZ::operator<<(const intmax_t& x)const {
	ZZ t = *this;
	return t <<= x;
}
ZZ ZZ:: operator>>(const intmax_t& x) const {
	ZZ t = *this;
	return t >>= x;
}
ZZ& ZZ::operator*=(const ZZ& x) {
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
				operator+=(temp << (it - ii) * b + q);
		it++;
	}
	sign = sign != x.sign;
	mant.shorten();
	return*this;
}
ZZ ZZ::operator*(const ZZ& x)const {
	ZZ t = *this;
	return t *= x;
}
ZZ& ZZ::operator=(const std::string& x) {
	this->operator=(0);
	unsigned int base = 10;
	std::string::size_type found = x.find_first_of("0123456789");
	if (found == std::string::npos)
		return*this;
	std::string::const_iterator
		it = x.begin() + found,
		jt = x.end();
	if (!found)
		sign = false;
	else
		sign = *(it - 1) == '-';
	if (*it == '0')
		switch (*(it + 1)) {
		case 'X':case 'x':
			base = 16;
			it += 2;
			break;
		case'B':case'b':
			base = 2;
			it += 2;
			break;
		default:
			base = 8;
			it++;
		}
	std::string filler = " _";
	std::string digits = std::string("0123456789abcdef").substr(0, base) + filler;
	while (it < jt) {
		auto d = digits.find(*it | ('A' <= *it && *it <= 'F') << 5);
		if (d == std::string::npos)
			break;
		else if (filler.find(*it) != std::string::npos);
		else {
			this->operator*=(base);
			this->operator+=(d);
		}
		it++;
	}
	return*this;
}
ZZ::ZZ(const std::string& x) { operator=(x); }
ZZ& ZZ::QR(const ZZ& x, ZZ& quotient_here) {
	quotient_here = 0;
	const size_t b = sizeof(iiunitt) * 8;
	ZZ a = x.abs();
	while (abs() >= a) {
		size_t
			dn0 = b - 1,
			dnx = b - 1;
		while (!(mant.back() & (1 << dn0)))
			dn0--;
		while (!(a.mantissa().back() & (1 << dnx)))
			dnx--;
		dn0 += (size() - 1) * b;
		dnx += (a.size() - 1) * b;
		auto temp = dn0 - dnx;
		if (this->operator<(a << temp))
			temp--;
		quotient_here |= ZZ(1) << temp;
		mant.difz((a << temp).mantissa());
		mant.shorten();
	}
	// 10001/10000=1+1/10000
	// -10001/10000=-1-1/10000=-2+9999/10000
	// 10001/-10000=-1-1/10000=-2+9999/10000
	// -10001/-10000=1+1/10000
	sign = quotient_here.sign = sign != x.sign;
	if (sign) {
		quotient_here -= 1;
		operator+=(x);
	}
	mant.shorten();
	return*this;
}
ZZ ZZ::operator/=(const ZZ& x) {
	ZZ t = *this, u;
	t.QR(x, u);
	operator=(u);
	return u;
}
ZZ ZZ::operator/(const ZZ& x)const {
	ZZ t = *this;
	return t /= x;
}
ZZ ZZ::operator%=(const ZZ& x) {
	ZZ t = *this, u;
	t.QR(x, u);
	return t;
}
ZZ ZZ::operator%(const ZZ& x)const {
	ZZ t = *this;
	return t %= x;
}