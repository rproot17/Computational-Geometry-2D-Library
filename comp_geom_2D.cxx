// Please Refer The README.md for how to use this as intended

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>

class comp_geom_2D {
public:
    static constexpr double EPS = 1e-9; // adjust for required accuracy

    template <typename T>
    struct Point {
        T x, y;
        Point() : x(0), y(0) {}
        Point(T x, T y) : x(x), y(y) {}
        bool operator<(const Point& other) const {
            if (x != other.x) {
                return x < other.x;
            }
            return y < other.y;
        }
        bool operator==(const Point& other) const {
            if constexpr (std::is_floating_point<T>::value) {
                return std::abs(x - other.x) < EPS && std::abs(y - other.y) < EPS;
            } else {
                return x == other.x && y == other.y;
            }
        }
    };

    template <typename T>
    static int orientation(Point<T> p, Point<T> q, Point<T> r) {
        long double val = (long double)(q.y - p.y) * (r.x - q.x) - (long double)(q.x - p.x) * (r.y - q.y);

        if (std::abs(val) < EPS) return 0;  // Collinear
        return (val > 0) ? 1 : 2; // 1: Clockwise, 2: Counter-clockwise
    }

    template <typename T>
    static bool onSegment(Point<T> p, Point<T> q, Point<T> r) {
        return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
    }

    template <typename T>
    static bool doIntersect(Point<T> p1, Point<T> q1, Point<T> p2, Point<T> q2) {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 && o1 != o2 && o3 != o4)
            return true;

        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false;
    }

    template <typename T>
    static std::vector<Point<T>> convexHull(std::vector<Point<T>>& points) {
        int n = points.size();
        if (n <= 2) return points;

        std::sort(points.begin(), points.end());
        std::vector<Point<T>> hull;

        for (int i = 0; i < n; ++i) {
            while (hull.size() >= 2 && 
                   orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }

        int t = hull.size() + 1;
        for (int i = n - 2; i >= 0; i--) {
            while (hull.size() >= t && 
                   orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }

        hull.pop_back();
        return hull;
    }

    template <typename T>
    static bool isInside(const std::vector<Point<T>>& polygon, Point<T> p) {
        int n = polygon.size();
        if (n < 3) return false;

        T inf = std::numeric_limits<T>::max();
        Point<T> extreme = {inf, p.y};

        int count = 0;
        int i = 0;
        do {
            int next = (i + 1) % n;
            if (doIntersect(polygon[i], polygon[next], p, extreme)) {
                if (orientation(polygon[i], p, polygon[next]) == 0)
                    return onSegment(polygon[i], p, polygon[next]);
                count++;
            }
            i = next;
        } while (i != 0);
        // If count is odd, the point is inside.
        // If count is even, the point is outside.
        return count % 2 == 1;
    }

    // Calculates the area of a simple (non-self-intersecting) polygon using the Shoelace Formula.
    template <typename T>
    static long double polygonArea(const std::vector<Point<T>>& polygon) {
        int n = polygon.size();
        if (n < 3) return 0.0;
        long double area = 0.0;

        for (int i = 0; i < n; ++i) {
            area += (long double)(polygon[i].x) * polygon[(i + 1) % n].y;
            area -= (long double)(polygon[(i + 1) % n].x) * polygon[i].y;
        }

        return std::abs(area) / 2.0;
    }

    template <typename T>
    static long double closestPair(std::vector<Point<T>>& points) {
        if (points.size() < 2) return 0.0;
        
        std::vector<Point<T>> pointsX = points;
        std::vector<Point<T>> pointsY = points;

        // Sort by x and y
        std::sort(pointsX.begin(), pointsX.end());
        std::sort(pointsY.begin(), pointsY.end(), sortByY<T>);

        // Call the recursive utility and return the actual distance
        return std::sqrt(closestPairUtil(pointsX, pointsY));
    }

    template <typename T>
    static long double polygonDiameter(std::vector<Point<T>>& points) {
        if (points.size() < 2) return 0.0;

        std::vector<Point<T>> hull = convexHull(points);

        if (hull.size() == 2)
            return std::sqrt(distSq(hull[0], hull[1]));
        if (hull.size() < 2)
            return 0.0;

        int n = hull.size();
        long double max_dist_sq = 0.0;
        int j = 1;

        for (int i = 0; i < n; ++i) {
            while (true) {
                Point<T> p1 = hull[i];
                Point<T> p2 = hull[(i + 1) % n];
                Point<T> q1 = hull[j];
                Point<T> q2 = hull[(j + 1) % n];

                Point<T> vec_p = {p2.x - p1.x, p2.y - p1.y};
                Point<T> vec_q = {q2.x - q1.x, q2.y - q1.y};

                long double cross_prod = (long double)vec_p.x * vec_q.y - (long double)vec_p.y * vec_q.x; // Cross Product

                if (cross_prod > 0)
                    j = (j + 1) % n;
                else
                    break;
            }

            max_dist_sq = std::max(max_dist_sq, distSq(hull[i], hull[j]));
            max_dist_sq = std::max(max_dist_sq, distSq(hull[(i + 1) % n], hull[j]));
        }

        return std::sqrt(max_dist_sq);
    }

private:

    template <typename T>
    static long double distSq(Point<T> p1, Point<T> p2) {
        return (long double)(p1.x - p2.x) * (p1.x - p2.x) +
               (long double)(p1.y - p2.y) * (p1.y - p2.y);
    }

    template <typename T>
    static bool sortByY(const Point<T>& a, const Point<T>& b) {
        return a.y < b.y;
    }

    template <typename T>
    static long double stripClosest(std::vector<Point<T>>& strip, long double d) {
        long double min_d = d;
        
        for (size_t i = 0; i < strip.size(); ++i) {
            for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < min_d; ++j) {
                long double new_dist = distSq(strip[i], strip[j]);
                if (new_dist < min_d)
                    min_d = new_dist;
            }
        }
        return min_d;
    }

    template <typename T>
    static long double closestPairUtil(std::vector<Point<T>>& pointsX, std::vector<Point<T>>& pointsY) {
        int n = pointsX.size();
        if (n <= 3) {
            long double min_d = std::numeric_limits<long double>::max();
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    min_d = std::min(min_d, distSq(pointsX[i], pointsX[j]));
            return min_d;
        }

        int mid = n / 2;
        Point<T> midPoint = pointsX[mid];

        std::vector<Point<T>> yL, yR;
        for (const auto& p : pointsY) {
            if (p.x < midPoint.x || (p.x == midPoint.x && p.y < midPoint.y))
                yL.push_back(p);
            else
                yR.push_back(p);
        }

        std::vector<Point<T>> xL(pointsX.begin(), pointsX.begin() + mid);
        std::vector<Point<T>> xR(pointsX.begin() + mid, pointsX.end());

        // Recurse
        long double dL = closestPairUtil(xL, yL);
        long double dR = closestPairUtil(xR, yR);
        long double d = std::min(dL, dR);

        // Build the "strip" of points close to the dividing line
        std::vector<Point<T>> strip;
        for (const auto& p : pointsY)
            if (std::abs((long double)p.x - midPoint.x) * std::abs((long double)p.x - midPoint.x) < d)
                strip.push_back(p);

        return std::min(d, stripClosest(strip, d));
    }

};


template <typename T>
std::ostream& operator<<(std::ostream& os, const typename comp_geom_2D::Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}