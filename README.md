# ZZQQCC

A C++ library implementing `ZZ`, an arbitrary-precision integer class.

## Overview

`ZZ` represents integers of arbitrary size. The name is inspired by the blackboard bold **ℤ** (the set of all integers). Internally, digits are stored in a `base-2^(8·sizeof(unsigned int))` positional system using the helper class `i_digits`.

## Files

| File | Description |
|------|-------------|
| `NearNumber/ZZ.h` | `ZZ` class — arbitrary-precision integer |
| `NearNumber/i_digits.h` | `i_digits` helper — digit storage and carry arithmetic |
| `NearNumber/test.cpp` | Example / test program |
| `ZZQQCC.sln` | Visual Studio solution |

## Building

Open `ZZQQCC.sln` in **Visual Studio 2019 or later** (MSVC v145 toolset, Windows SDK 10.0) and build the `ZZQQCC` project.

Supported configurations: `Debug|Win32`, `Release|Win32`, `Debug|x64`, `Release|x64`.

## Usage

Include `ZZ.h` in your project:

```cpp
#include "ZZ.h"

// Construct from integer
ZZ a(42);

// Construct from decimal / hex / binary / octal string
ZZ b("0xFF00");
ZZ c("-12345");

// Arithmetic
ZZ sum  = a + b;
ZZ diff = b - a;
ZZ prod = a * b;

// Division and remainder (preferred)
ZZ quotient, remainder = b;
remainder.QR(a, quotient);   // remainder holds b % a, quotient holds b / a

// Bitwise
ZZ r = a & b;
ZZ s = a | b;
ZZ t = a ^ b;
ZZ u = a << 4;
ZZ v = a >> 4;

// Comparison
bool gt = a > b;
bool eq = a == b;

// Sign / absolute value
intmax_t s = a.sgn();   // -1, 0, or 1
ZZ       av = a.abs();

// Hexadecimal string
std::string hex = a.hexadec(true);   // "0x2A"
```

## API Summary

### Constructors

| Constructor | Description |
|-------------|-------------|
| `ZZ(intmax_t x = 0)` | Construct from a native integer |
| `ZZ(const std::string& x)` | Construct from a string (decimal, `0x…` hex, `0b…` binary, `0…` octal) |
| `ZZ(const ZZ& x)` | Copy constructor |

### Arithmetic operators

`+`, `-`, `*`, `/`, `%`, `+=`, `-=`, `*=`, `/=`, `%=`, `++`, `--`, unary `-`

> **Note:** `/` and `%` are functional but not optimised. Prefer `QR()` when both quotient and remainder are needed.

### Bitwise operators

`&`, `|`, `^`, `<<`, `>>`, `&=`, `|=`, `^=`, `<<=`, `>>=`

### Comparison operators

`==`, `!=`, `<`, `<=`, `>`, `>=`, `!` (zero-check), `&&`, `||`

### Other methods

| Method | Description |
|--------|-------------|
| `ZZ abs() const` | Absolute value |
| `intmax_t sgn() const` | Sign: −1, 0, or 1 |
| `std::string hexadec(bool prefix) const` | Hexadecimal string; `prefix=true` prepends `0x` |
| `ZZ& QR(const ZZ& divisor, ZZ& quotient)` | Euclidean division: `this` becomes remainder, `quotient` gets the quotient |
| `size_t size() const` | Number of internal digit units |

## Coding notes

See `NearNumber/memorandum.txt` for style guidelines followed in this project.
