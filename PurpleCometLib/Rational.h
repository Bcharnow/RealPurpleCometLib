#include <cmath>
#include <iostream>
#pragma once
namespace Ratio {

    struct Ratio {
        int num;
        int dem;
        Ratio(float val, int Search) {
            float err = -1;
            num = 0;
            dem = 1;
            for (int PntDem = 1; PntDem <= Search; PntDem++) {
                int PntNum = round(val * PntDem);
                float PntErr = std::fabs(val - float(PntNum) / PntDem);
                if (err == -1 || PntErr < err) {
                    num = PntNum;
                    dem = PntDem;
                    err = PntErr;
                }
            }
        }
        void Print() { std::cout << num << "/" << dem << "\n"; }
    };
}