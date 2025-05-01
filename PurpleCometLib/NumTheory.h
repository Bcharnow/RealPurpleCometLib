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
    // Get nth digit from right (0-based index)
    inline int getNthDigit(long long num, int n) {
        num = std::abs(num);
        while (n > 0) {
            num /= 10;
            n--;
        }
        return num % 10;
    }

    // Reverse a number
    inline long long reverseNumber(long long num) {
        long long reversed = 0;
        bool negative = num < 0;
        num = std::abs(num);
        
        while (num > 0) {
            reversed = reversed * 10 + num % 10;
            num /= 10;
        }
        
        return negative ? -reversed : reversed;
    }

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
    int modInverse(int a, int m) {
        int m0 = m, t, q;
        int x0 = 0, x1 = 1;
        if (m == 1) return 0;
        while (a > 1) {
            q = a / m;
            t = m, m = a % m, a = t;
            t = x0, x0 = x1 - q * x0, x1 = t;
        }
        return (x1 < 0) ? x1 + m0 : x1;
    }

}