#pragma once
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?-1:1)
#define ABS(x) ((x)<0?-(x):(x))
//An abbreviation of "integer-integer unit type."
typedef unsigned int iiunitt;
//A class for addition and its inverse in base 2**(sizeof(iiunitt)*8)
class idigits :public std::vector<iiunitt> {
public:
	//Reduces length of this so that save more space.
	void shorten(void) {
		while (size() > 1)
			if (!back())
				pop_back();
			else
				break;
	}
	//Adds x to this.
	idigits& addz(const idigits&);
	//Checks if x is greater than this.
	bool operator<(const idigits&)const;
	//Takes difference of this and x.
	idigits& difz(idigits);
};

idigits& idigits::addz(const idigits& x) {
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
bool idigits::operator<(const idigits& x)const {
	if (size() != x.size())
		return size() < x.size();
	else {
		for (
			idigits::const_reverse_iterator it = rbegin();
			it < rend();
			it++
			) {
			if (*it < x.at(it - rbegin()))
				return true;
		}
		return false;
	}
}
idigits& idigits::difz(idigits x) {
	const auto
		n = size(),
		xn = x.size();
	if (n < xn)
		resize(xn);
	if (operator<(x))
		swap(x);
	for (
		size_t t = 0;
		t < xn;
		t++
		) {
		auto att = at(t);
		at(t) -= x.at(t);
		if (att < x.at(t)) {
			idigits i;
			i.resize(t + 1);
			i.push_back(1);
			difz(i);
		}
	}
	return*this;
}