---
title:  "Mastering the Basics of Floating-Point"
categories:
  - blog
tags:
  - cs
use_math: true
toc: true
toc_label: "Table of Content"
toc_icon: "heart"
---

## Introduction

Floating-point numbers enables us to represent a wide dynamic range of numeric values in a compact form (float32, float64). However, compared with fixed-point numbers, their behavior can sometimes be unintuitive, which could lead to subtle bugs.

This blog serves as a quick reference and refresher on the essential basics of floating-point, with a focus on the IEEE 754 standard.

We’ll cover the IEEE 754 standard for the single precision floating-point format, the representation of special numbers including subnormal numbers, NaN, Infinity and zero. I'll share a simple and handy function for safely converting double to float with overflow and underflow handled.


## IEEE 754 Standard
Floating point is a method of representing a real number by mantissa and exponent.

![eigenvector](/images/2025-01-05-floatingpoint-basics/mantissa-exponent.png)

IEEE 754, the technical standard for floating-point arithmetic, specifies the formats of floating-point (PF) representations. Single precision and double precision are two most used FP types in SW development.

### Single Precision

- Mantissa: 24 bits
    - Normal numbers: "1." + 23 fraction bits
    - Subnormal numbers: "0." + 23 faction bits (special numbers)
- Exponent: 8 bits
    - With an offset $ 127 $. $ \ (exponents)_{10} = (exponent)_2 - 127 $
    - Range: [-126, +127], all 0s (-127) and all 1s (+128) are reserved for special numbers.
- Sign: 1 bit
    - 0 - positive
    - 1 - negative

![eigenvector](/images/2025-01-05-floatingpoint-basics/single-precision.png)

Conversion for a normal number: 

$$ (value)_{10} \ =\ (-1)^{sign} * (1 + fraction)_2 * 2^{(exponent)_2 - 127} $$

| Property                          | Value                    | C++                               |
|-----------------------------------|--------------------------|-----------------------------------|
| Minimum normalized positive value | $ (1.0...0) * 2^{-126} $ | std::numeric_limits<float>::min() |
| Maximum finite value              | $ (1.1...1) * 2^{+127} $ | std::numeric_limits<float>::max() |
| Minimum finite value              | $ -(1.1...1) * 2^{+127}$ | -std::numeric_limits<float>::max() or lowest()|
| Smallest positive subnormal value | $ (0.0...1) * 2^{-126} $ | std::numeric_limits<float>::denorm_min()|
| Largest negative subnormal value  | $ -(0.0...1) * 2^{-126}$ | -std::numeric_limits<float>::denorm_min()|

```bash
Minimum normalized positive value: 1.17549e-38
Maximum finite value: 3.40282e+38
Minimum finite value: -3.40282e+38
Smallest positive subnormal value: 1.4013e-45
Largest negative subnormal value: -1.4013e-45
```

### Double Precision

- Mantissa: 53 bits
    - Normal numbers: "1." + 52 fraction bits
    - Subnormal numbers: "0." + 52 fraction bits
- Exponent: 11 bits
    - With an offset $ 1023 $. $ \ (exponents)_{10} = (exponent)_2 - 1023 $
    - Range: [−1022, +1023], all 0s (-1023) and all 1s (1024) are reserved for special numbers.
- Sign: 1 bit
    - 0 - positive
    - 1 - negative

![eigenvector](/images/2025-01-05-floatingpoint-basics/double-precision.png)

Conversion for a normal number: 

$$ (value)_{10} \ =\ (-1)^{sign} * (1 + fraction)_2 * 2^{(exponent)_2 - 1023} $$

| Property                          | Value                     | C++                               |
|-----------------------------------|---------------------------|-----------------------------------|
| Minimum normalized positive value | $ (1.0...0) * 2^{-1022} $ | std::numeric_limits<double>::min() |
| Maximum finite value              | $ (1.1...1) * 2^{+1023} $ | std::numeric_limits<double>::max() |
| Minimum finite value              | $ -(1.1...1) * 2^{+1023}$ | -std::numeric_limits<double>::max() or lowest()|
| Smallest positive subnormal value | $ (0.0...1) * 2^{-1022} $ | std::numeric_limits<double>::denorm_min()|
| Largest negative subnormal value  | $ -(0.0...1) * 2^{-1022}$ | -std::numeric_limits<double>::denorm_min()|

```bash
Minimum normalized positive value: 2.22507e-308
Maximum finite value: 1.79769e+308
Minimum finite value: -1.79769e+308
Smallest positive subnormal value: 4.94066e-324
Largest negative subnormal value: -4.94066e-324
```

### Exponent Bias

Noticed that IEEE 754 uses a biased representation for exponents. For any FP types, we can compute the offset using the following fomula.

$ offset = 2^{ (number \ of \ \ exponent \ bits - 1) } - 1$

All 0s and all 1s of exponent bits are reserved for representing special numbers. Therefore, the exponent range is $ [ -(bais -1), +bais ] $

With this bias form, different exponents can be compared easily since they are in lexical ordering. This property can significantly simplify and speed up sorting for FP numbers.


### Special Numbers

All 0s and all 1s exponents are reserved to represent special numbers.

| Exponent | Mantissa | Special Numbers |
|----------|----------|----------|
| 1...11   | 0...00   | Infinity |
| 1...11   | Not all 0| NAN      |
| 0...00   | 0...00   | 0        |
| 0...00   | Not all 0| Subnormal|

Subnormal numbers fill the gap between the smallest normalized number and zero, prevent from rounding to zero for small number calculations.

## Converting Between Floating-Point Types

Conversion between different FP types, especially converting numbers in a type with more bits to numbers represented using fewer bits comes with challenges. The following code provides a simple implementation of double to float conversion with underflow, overflow and special numbers handled.

```c++
#include <iostream>
#include <limits>
#include <cmath>

static float double2float(double in) {
    
    // handle NAN
    if (std::isnan(in)) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    // handle Infinity
    if (!std::isfinite(in)) {
        return std::numeric_limits<float>::infinity();
    }
    
    // handle underflow: subnormal numbers
    if (!std::isnormal(in) && (in != 0.0)) {
        if (in > 0.0f) {
           return std::numeric_limits<float>::denorm_min();
        } else {
           return -std::numeric_limits<float>::denorm_min();
        }
    }
    
    // handle overflow
    if (in > std::numeric_limits<float>::max()) {
        return std::numeric_limits<float>::max();
    }
    
    if (in < std::numeric_limits<float>::lowest()) {
        return std::numeric_limits<float>::lowest();
    }
    
    return (float)in;
} 

int main()
{
    float out;
    double in_nan = std::numeric_limits<double>::quiet_NaN();
    out = double2float(in_nan);
    std::cout << "double = NAN, output float is NAN: " << std::isnan(out) << std::endl;
    
    double in_infinity = -std::numeric_limits<double>::infinity();
    out = double2float(in_infinity);
    std::cout << "double = -infinity, output float is infinity: " << !std::isfinite(out) << std::endl;
    in_infinity = std::numeric_limits<double>::infinity();
    out = double2float(in_infinity);
    std::cout << "double = infinity, output float is infinity: " << !std::isfinite(out) << std::endl;
    
    double in_max = std::numeric_limits<double>::max();
    out = double2float(in_max);
    std::cout << "double = max, output float: " << out << ", float max: " << std::numeric_limits<float>::max() << std::endl;
    
    double in_lowest = std::numeric_limits<double>::lowest();
    out = double2float(in_lowest);
    std::cout << "double = lowest, output float: " << out << ", float lowest: " << std::numeric_limits<float>::lowest() << std::endl;
  
    
    double in_denorm = std::numeric_limits<double>::min() / 2.0;
    out = double2float(in_denorm);
    std::cout << "double = denorm, output float: " << out << ", float smallest: " << std::numeric_limits<float>::denorm_min() << std::endl;
    
    double in_zero = 0.0;
    out = double2float(in_zero);
    std::cout << "double = 0.0, output float: " << out << std::endl;
    
    double in_norm = 2.11117;
    out = double2float(in_norm);
    std::cout << "double: " << in_norm << ", output float: " << out << std::endl;
    
    return 0;
}
```

## Key Takeaways

In this blog, we explored the IEEE 754 standard, examining the register layouts for float and double, discussing the biased exponent representation, presenting a lookup table for special numbers, and diving into floating-point number conversions.

## Resources and References

[1] : <https://en.wikipedia.org/wiki/Single-precision_floating-point_format>

[2] : <https://en.wikipedia.org/wiki/Double-precision_floating-point_format>

[3] : <https://en.wikipedia.org/wiki/IEEE_754>