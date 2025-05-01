
#pragma once
#i
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
    
    // Newton's method for finding roots
    inline double newton(std::function<double(double)> f, double x0, int maxIter = 100) {
        auto df = derivative(f);
        double x = x0;
        
        for (int i = 0; i < maxIter; i++) {
            double fx = f(x);
            if (std::abs(fx) < EPS) return x;
            
            double dfx = df(x);
            if (std::abs(dfx) < EPS) break;  // Avoid division by zero
            
            x = x - fx / dfx;
        }
        return x;
    }
    
    // Numerical integration using Simpson's rule
    inline double integrate(std::function<double(double)> f, double a, double b, int n = 1000) {
        if (n % 2 == 1) n++;  // Ensure n is even
        double h = (b - a) / n;
        double sum = f(a) + f(b);
        
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            sum += f(x) * (i % 2 == 0 ? 2 : 4);
        }
        
        return sum * h / 3;
    }
    
    // Bisection method
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

    // Find roots using hybrid approach (Newton + Bisection)
    inline std::vector<double> findAllRoots(std::function<double(double)> f, double a, double b, int samples = 50) {
        std::vector<double> roots;
        auto df = derivative(f);
        double step = (b - a) / samples;
        
        // Sample points and use Newton's method
        for (int i = 0; i <= samples; i++) {
            double x0 = a + i * step;
            double fx0 = f(x0);
            
            // If we're already close to a root
            if (std::abs(fx0) < EPS) {
                roots.push_back(x0);
                continue;
            }
            
            // Try Newton's method
            double root = newton(f, x0, 20);
            
            // Check if root is valid and new
            if (root >= a && root <= b && std::abs(f(root)) < EPS) {
                bool isNew = true;
                for (double existingRoot : roots) {
                    if (std::abs(existingRoot - root) < EPS) {
                        isNew = false;
                        break;
                    }
                }
                if (isNew) roots.push_back(root);
            }
        }
        
        return roots;
    }
}
