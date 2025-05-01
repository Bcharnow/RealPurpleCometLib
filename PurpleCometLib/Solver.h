
#pragma once
#include <vector>
#include <functional>
#include <cmath>

namespace Solver {
    const double EPS = 1e-9;
    
    // Get derivative of function using central difference
    inline std::function<double(double)> derivative(std::function<double(double)> f, double h = 1e-7) {
        return [f, h](double x) {
            return (f(x + h) - f(x - h)) / (2 * h);
        };
    }
    
    // Bisection method to find root in [a,b]
    inline double bisection(std::function<double(double)> f, double a, double b) {
        double fa = f(a), fb = f(b);
        if (std::abs(fa) < EPS) return a;
        if (std::abs(fb) < EPS) return b;
        
        for (int iter = 0; iter < 100; iter++) {
            double c = (a + b) / 2;
            double fc = f(c);
            
            if (std::abs(fc) < EPS) return c;
            if (fa * fc < 0) { b = c; fb = fc; }
            else { a = c; fa = fc; }
        }
        return (a + b) / 2;
    }

    
}
