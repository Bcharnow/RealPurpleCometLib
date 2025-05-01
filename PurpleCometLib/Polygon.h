#pragma once
#include "DynamicArray.h"
#include <cmath>
#include <stdexcept>
#include <numeric>
#include "Vector2.h"

namespace Polygon {

    class Polygon {
        dynamicarray::array<v2::Vector2> pointlist;

    public:
        Polygon() = default;
        Polygon(std::initializer_list<v2::Vector2> pts) : pointlist(pts) {}
        Polygon(const dynamicarray::array<v2::Vector2>& pts) : pointlist(pts) {}
        void destroy() {

            pointlist.destroy();
        }
        // allow indexing
        v2::Vector2& operator[](int i) {
            return pointlist.at(i);   // throws if out‐of‐bounds
        }
        const v2::Vector2& operator[](int i) const  {
            return pointlist.at(i);
        }

        void addPoint(const v2::Vector2& pt) {
            pointlist.append(pt);
        }

        double area()  {
            double a = 0;
            int n = pointlist.length;
            for (int i = 0; i < n; ++i) {
                a += v2::cross(pointlist[i], pointlist[(i + 1) % n]);
            }
            return std::abs(a) * 0.5;
        }

        double perimeter()  {
            double p = 0;
            int n = pointlist.length;
            for (int i = 0; i < n; ++i) {
                p += v2::distance(pointlist[i], pointlist[(i + 1) % n]);
            }
            return p;
        }

        v2::Vector2 centroid()  {
            double cx = 0, cy = 0;
            double factor = 0;
            int n = pointlist.length;
            for (int i = 0; i < n; ++i) {
                const auto& p1 = pointlist[i];
                const auto& p2 = pointlist[(i + 1) % n];
                double crossProd = v2::cross(p1, p2);
                cx += (p1.x + p2.x) * crossProd;
                cy += (p1.y + p2.y) * crossProd;
                factor += crossProd;
            }
            factor *= 3.0;
            if (factor == 0) throw std::runtime_error("Degenerate polygon");
            return { cx / factor, cy / factor };
        }
    };

}