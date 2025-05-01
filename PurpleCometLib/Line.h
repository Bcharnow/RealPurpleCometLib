#include "Vector2.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace geometry {

    class Line {
    private:
        v2::Vector2 start;  // Start point of the line
        v2::Vector2 end;    // End point of the line

    public:
        // Constructor to create a line using two points
        Line(const v2::Vector2& start, const v2::Vector2& end)
            : start(start), end(end) {}

        // Getters for the start and end points
        v2::Vector2 getStart() const { return start; }
        v2::Vector2 getEnd() const { return end; }

        // Calculate the length of the line (distance between start and end points)
        double length() const {
            return v2::distance(start, end);
        }

        // Calculate the slope of the line
        double slope() const {
            if (end.x == start.x) {
                throw std::runtime_error("Vertical line: slope is undefined.");
            }
            return (end.y - start.y) / (end.x - start.x);
        }

        // Calculate the angle of the line with respect to the x-axis
        float angle() const {
            float dx = end.x - start.x;
            float dy = end.y - start.y;
            return toDegrees(std::atan2(dy, dx));  // Return angle in degrees
        }

        // Check if a point (px, py) is on the line
        bool containsPoint(const v2::Vector2& point) const {
            double crossProduct = (point.y - start.y) * (end.x - start.x) -
                (point.x - start.x) * (end.y - start.y);
            // If the cross product is 0, the point is collinear with the line
            return std::abs(crossProduct) < 1e-9;
        }

        // Check if two lines intersect
        bool intersect(const Line& other) const {
            float x1 = start.x, y1 = start.y, x2 = end.x, y2 = end.y;
            float x3 = other.getStart().x, y3 = other.getStart().y, x4 = other.getEnd().x, y4 = other.getEnd().y;

            // Calculate the determinant
            float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
            if (denom == 0) return false;  // Lines are parallel or coincident

            float intersectX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
            float intersectY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;

            // Check if the intersection point lies within the bounds of both line segments
            return (std::min(x1, x2) <= intersectX && intersectX <= std::max(x1, x2) &&
                std::min(y1, y2) <= intersectY && intersectY <= std::max(y1, y2) &&
                std::min(x3, x4) <= intersectX && intersectX <= std::max(x3, x4) &&
                std::min(y3, y4) <= intersectY && intersectY <= std::max(y3, y4));
        }

        // Print the line (for debugging or visualization)
        void print() const {
            std::cout << "Line: (" << start.x << ", " << start.y << ") to ("
                << end.x << ", " << end.y << ")\n";
        }
    };
}
