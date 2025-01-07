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