
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

    // Find roots recursively by finding critical points
    inline std::vector<double> findRoots(std::function<double(double)> f, double a, double b) {
        std::vector<double> roots;
        
        // First find roots using direct bisection
        if (f(a) * f(b) <= 0) {
            roots.push_back(bisection(f, a, b));
        }
        
        // Then find critical points using derivative
        auto df = derivative(f);
        auto ddf = derivative(df);
        
        // Find critical points recursively
        std::vector<double> critPoints = findRoots(df, a, b);
        
        // Add endpoints if they're critical
        if (std::abs(df(a)) < EPS) critPoints.push_back(a);
        if (std::abs(df(b)) < EPS) critPoints.push_back(b);
        
        // For each pair of critical points, check for roots
        for (size_t i = 0; i < critPoints.size(); i++) {
            for (size_t j = i + 1; j < critPoints.size(); j++) {
                double left = critPoints[i];
                double right = critPoints[j];
                
                if (f(left) * f(right) <= 0) {
                    roots.push_back(bisection(f, left, right));
                }
            }
        }
        
        return roots;
    }
}
