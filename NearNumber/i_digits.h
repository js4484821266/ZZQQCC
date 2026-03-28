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
	//Shortens this.
	void shorten()
	{
		auto n = size() - 1;
		while (!operator[](n))--n;
		resize(n + 1);
	}

	//Adds x to this.
	i_digits& z_add(const i_digits&);

	//Checks if x is greater than this.
	bool operator<(const i_digits&) const;

	//Takes difference between this and x.
	i_digits& z_diff(i_digits);
};

inline i_digits& i_digits::z_add(const i_digits& x)
{
	constexpr auto
		n_bits = sizeof(i_i_unit_t) * 8;
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
		auto& l_digit = at(t);
		auto& r_digit = x.at(t);
		const auto
			l_and_r = l_digit & r_digit,
			l_or_r = l_digit | r_digit;
		l_digit += r_digit;
		for (
			size_t i = 0;
			i < n_bits;
			i++
		)
		{
			if (!(l_or_r & (1 << (n_bits - 1 - i))))
				break;
			if (l_and_r & (1 << (n_bits - 1 - i)))
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
