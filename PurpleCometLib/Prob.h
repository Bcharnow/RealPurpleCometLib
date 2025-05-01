#include "Random.h"
#include "Rational.h"
#include <functional>
#pragma once
namespace Prob {
    struct ProbSum {
        int passes;
        int trials;

        ProbSum(std::function<bool(void)> func, int Trials) {
            trials = Trials;
            passes = 0;
            for (int i = 1; i <= Trials; i++) {
                if (func()) {
                    passes += 1;
                }
            }
        }
        void PrintRatio() { Ratio::Ratio(float(passes) / trials, 100).Print(); }

    };
}