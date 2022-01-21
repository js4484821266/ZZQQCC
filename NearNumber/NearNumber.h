#pragma once
#include<vector>
#include<cstdint>
class BigInteger {
	bool sign = 0;
	std::vector<uint8_t>mantissa;
public:
	BigInteger(void) {
		mantissa.push_back(0);
	}
	bool sgn(void) { return sign; }
	const std::vector<uint8_t>& mantissa(void) { return mantissa; }
};
class NearNumber {
};
typedef BigInteger __intn;
typedef NearNumber ntuple;