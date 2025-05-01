#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <vector>

namespace Ntheory
{

    inline int gcd(int a, int b) {
        while (b) { int t = b; b = a % b; a = t; }
        return a;
    }
    inline int lcm(int a, int b) {
        return a / gcd(a, b) * b;
    }

 
   long long mod_pow(long long base, long long exp, long long mod) {
        long long result = 1;
        base = base % mod;  // In case base is larger than mod

        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }

        return result;
    }
}