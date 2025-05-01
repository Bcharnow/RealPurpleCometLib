#pragma once

#include "Vector2.h"
#include <cmath>
#include <utility>
#include <cstddef>
#include "Vector3.h"

namespace Spirals {

    inline v2::Coord2d intToSpiralXY(size_t n) {
        if (n == 0) return { 0, 0 };

        // k = “layer” index
        int k = static_cast<int>(std::ceil((std::sqrt((double)n) - 1.0) / 2.0));
        int t = 2 * k;                            // side length minus 1
        unsigned prev = (2 * k - 1) * (2 * k - 1);    // max index in previous layer
        unsigned idx = n - prev - 1;            // 0-based offset in this layer
        int  leg = idx / t;                      // which side (0…3)
        int  off = static_cast<int>(idx % t);    // position along that side

        switch (leg) {
        case 0:
            return v2::Coord2d(k, -k + 1 + off);   // right edge, going up
        case 1:
            return v2::Coord2d(k - 1 - off, k);   // top   edge, going left
        case 2:
            return v2::Coord2d(-k, k - 1 - off);   // left  edge, going down
        default: // leg == 3
            return v2::Coord2d(-k + 1 + off, -k);   // bottom edge, going right
        }
    }

    inline v2::Coord2d intToNonnegXY(std::size_t n) {
        // compute which “diagonal” we're on
        std::size_t w = static_cast<std::size_t>(
            std::floor((std::sqrt(8.0 * n + 1.0) - 1.0) / 2.0)
            );
        std::size_t t = w * (w + 1) / 2;     // total count up through all pairs with sum < w
        std::size_t y = n - t;              // position along diagonal
        std::size_t x = w - y;
        return v2::Coord2d(x, y);
    }

    inline v3::Coord intTo3DSpiral(size_t n) {
        if (n == 0) return v3::Coord{0, 0, 0};

        // 1) find shell k: smallest k so that (2k+1)^3 > n
        double dn = double(n);
        int k = int(std::ceil((std::cbrt(dn) - 1.0) / 2.0));

        // 2) how many points were before this shell?
        unsigned prevMax = (2 * k - 1) * (2 * k - 1) * (2 * k - 1);

        // 3) offset of n within this shell
        unsigned idx = n - prevMax - 1;

        // each face has m*m points, where m = side - 1 = 2*k
        unsigned m = 2 * k;
        unsigned faceSize = m * m;

        // which of the 6 faces?
        unsigned face = idx / faceSize;      // 0..5
        unsigned off = idx % faceSize;      // 0..faceSize-1

        // convert off into a grid coordinate (i,j) on the face:
        unsigned i = off / m;  // 0..m-1
        unsigned j = off % m;  // 0..m-1

        switch (face) {
        case 0: // bottom face  (y = -k)
            return v3::Coord{  k - int(i), -k, -k + 1 + int(j) };
        case 1: // right face   (x =  k)
            return v3::Coord{  k, int(-k + i), -k + 1 + int(j) };
        case 2: // top face     (y =  k)
            return v3::Coord{  k - int(i), k, k - 1 - int(j) };
        case 3: // left face    (x = -k)
            return v3::Coord{ -k, k - int(i), -k + 1 + int(j) };
        case 4: // front face   (z =  k)
            return v3::Coord{ -k + 1 + int(j), -k + int(i), k };
        default: // back face   (z = -k)
            return v3::Coord{ -k + 1 + int(j), k - int(i), -k };
        }
    }

    inline v3::Coord intTo3DSpiralPos(size_t n) {
        if (n == 0) return v3::Coord{0, 0, 0};

        double dn = double(n);
        int k = int(std::ceil((std::cbrt(dn) - 1.0) / 2.0));
        unsigned prevMax = (2 * k - 1) * (2 * k - 1) * (2 * k - 1);
        unsigned idx = n - prevMax - 1;
        unsigned m = 2 * k;
        unsigned faceSize = m * m;
        unsigned face = idx / faceSize;
        unsigned off = idx % faceSize;
        unsigned i = off / m;
        unsigned j = off % m;

        int x, y, z;
        switch (face) {
        case 0: x = k - int(i); y = -k;            z = -k + 1 + int(j); break;
        case 1: x = k;          y = -k + int(i);   z = -k + 1 + int(j); break;
        case 2: x = k - int(i); y = k;            z = k - 1 - int(j); break;
        case 3: x = -k;          y = k - int(i);   z = -k + 1 + int(j); break;
        case 4: x = -k + 1 + int(j); y = -k + int(i); z = k;          break;
        default:
            x = -k + 1 + int(j); y = k - int(i); z = -k;            break;
        }

        // shift into [0..2k]
        int shift = k;
        return v3::Coord{ x + shift, y + shift, z + shift };
    }

}