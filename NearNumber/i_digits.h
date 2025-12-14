#pragma once
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?-1:1)
#define ABS(x) ((x)<0?-(x):(x))
//An abbreviation of "integer-integer unit type."
using i_i_unit_t = unsigned int;

//A class for addition and its inverse in base 2**(sizeof(i_i_unit_t)*8)
class i_digits : public std::vector<i_i_unit_t>
{
public:
	//Reduces length of this so that save more space.
	void shorten(void)
	{
		while (size() > 1)
			if (!back())
				pop_back();
			else
				break;
	}

	//Adds x to this.
	i_digits& z_add(const i_digits&);
	//Checks if x is greater than this.
	bool operator<(const i_digits&) const;
	//Takes difference of this and x.
	i_digits& z_diff(i_digits);
};

i_digits& i_digits::z_add(const i_digits& x)
{
	constexpr auto
		nbits = sizeof(i_i_unit_t) * 8;
	const auto
		n = size(),
		xn = x.size();
	if (n < xn)
		resize(xn);
	for (
		size_t t = 0;
		t < xn;
		t++
	)
	{
		auto& pt = at(t);
		auto& xpt = x.at(t);
		const auto
			eaxn = pt & xpt,
			eaxo = pt | xpt;
		pt += xpt;
		for (
			size_t i = 0;
			i < nbits;
			i++
		)
		{
			if (!(eaxo & (1 << (nbits - 1 - i))))
				break;
			if (eaxn & (1 << (nbits - 1 - i)))
			{
				i_digits j;
				j.resize(t + 1);
				j.push_back(1);
				z_add(j);
				break;
			}
		}
	}
	return *this;
}

bool i_digits::operator<(const i_digits& x) const
{
	if (size() != x.size())
		return size() < x.size();
	for (
		auto it = rbegin();
		it < rend();
		++it
	)
	{
		if (*it < x.at(it - rbegin()))
			return true;
	}
	return false;
}

i_digits& i_digits::z_diff(i_digits x)
{
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
	)
	{
		auto att = at(t);
		at(t) -= x.at(t);
		if (att < x.at(t))
		{
			i_digits i;
			i.resize(t + 1);
			i.push_back(1);
			z_diff(i);
		}
	}
	return *this;
}
