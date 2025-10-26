# 🧮 Computational Geometry Library (C++)

A **single-file, templated C++ library** for fundamental and advanced 2D computational geometry operations.  
Lightweight, easy to integrate, and built for clarity, speed, and precision.

---

## 📖 Table of Contents

[Overview](#overview)  
[Features](#features)  
[Getting Started](#getting-started)  
[Usage Example's](#Usage-Example's)
[Full Sample Code](#Full-Example-Program)
[Summary](#Summary)

---

## 🧩 Overview

This **single-file C++ Computational Geometry Library** provides a suite of efficient, templated geometric algorithms designed for both **integer** and **floating-point** numeric types.

All functionality is contained within the **`CompGeom`** namespace.

The library includes algorithms for:
- Point manipulation and comparison
- Line segment and polygon operations
- Convex hull computation
- Point-in-polygon tests
- Closest pair and diameter analysis

---

## ⚙️ Features

| Category | Functions / Components | Description |
|-----------|------------------------|--------------|
| **Core Structure** | `Point<T>` | 2D point struct supporting arithmetic and comparison operators |
| **Basic Utilities** | `orientation()`, `onSegment()` | Orientation test and point-on-segment check |
| **Intersection** | `doIntersect()` | Detects intersection between two line segments |
| **Polygons & Hulls** | `convexHull()`, `isInside()`, `polygonArea()` | Convex hull, point-in-polygon, and polygon area |
| **Point Set Analysis** | `closestPair()`, `polygonDiameter()` | Minimum and maximum distance between points |

All algorithms are implemented in **O(1)**, **O(n)**, or **O(n log n)** time complexities.

---

## 🚀 Getting Started

### 1️⃣ Copy the File
Add **`comp_geom_2D.cxx`** to your project directory. "Note that i just like to use .cxx instead of .cpp, but if u want to use .cpp, just rename to "comp_geom_2D.cpp""

### 2️⃣ Include the File
In your main C++ file, include the library after all standard headers:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include "comp_geom_2D.cxx"  // Include the geometry library
```
### 3️⃣ Use the Namespace (optional) 
```
using namespace comp_geom_2D;
```

💡 Tip: For production builds, separate your main() function and compile comp_geom_2D.cxx as its own translation unit, or move its contents into a header file (comp_geom.hpp).

### 🧩 Usage Example's
-> 🟢 ``` Point<T> ``` - Creating and Using Points

    Point<double> a(0, 0);
    Point<double> b(10, 10);
    Point<int> c(3, 4);

    std::cout << "Point a: " << a << std::endl;
    std::cout << "Point b: " << b << std::endl;

    if (a == b)
        std::cout << "Points are equal" << std::endl;
    else
        std::cout << "Points are not equal" << std::endl;

Output
```
Point a: (0, 0)
Point b: (10, 10)
Points are not equal
```

-> 🧭 ``` orientation(p, q, r)``` - Determines the orientation (collinear, clockwise, counter-clockwise) of three points.

```
Point<double> p(0, 0), q(4, 4), r(1, 2);

int val = orientation(p, q, r);

if (val == 0) std::cout << "Collinear\n";
else if (val == 1) std::cout << "Clockwise\n";
else std::cout << "Counter-clockwise\n";
```

Output 
```
Counter-clockwise
```

-> 📏 ``` onSegment(p, q, r) ``` - Checks if point ```q``` lies on the segment ```pr``` (assuming the three points are collinear).

```
Point<double> p(0, 0), q(3, 3), r(5, 5);

if (onSegment(p, q, r))
    std::cout << "Point lies on segment" << std::endl;
else
    std::cout << "Point does not lie on segment" << std::endl;
```

Output
```
Point lies on segment
```

-> 🔀 ```doIntersect(p1, q1, p2, q2)``` - Checks if two line segments intersect.
```
Point<double> p1(1, 1), q1(10, 1);
Point<double> p2(1, 2), q2(10, 2);

std::cout << (doIntersect(p1, q1, p2, q2) ? "Intersect" : "Do not intersect") << std::endl;

Point<double> p3(10, 0), q3(0, 10);
Point<double> p4(0, 0), q4(10, 10);

std::cout << (doIntersect(p3, q3, p4, q4) ? "Intersect" : "Do not intersect") << std::endl;
```
Output
```
Do not intersect
Intersect
```

-> ⛵ ```convexHull(points)``` - Computes the convex hull of a set of points using Andrew’s Monotone Chain algorithm.

```
std::vector<Point<double>> points = {
    {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}
};

std::vector<Point<double>> hull = convexHull(points);

std::cout << "Convex Hull points:\n";
for (auto& p : hull)
    std::cout << "(" << p.x << ", " << p.y << ")\n";
```

Output
```
Convex Hull points:
(0, 0)
(3, 0)
(3, 3)
(0, 3)
```

-> 🏠 ```isInside(polygon, p)``` - Determines if a point lies inside or on the edge of a simple polygon.

```
std::vector<Point<double>> polygon = {
    {0, 0}, {10, 0}, {10, 10}, {0, 10}
};

Point<double> test1(5, 5);
Point<double> test2(15, 5);

std::cout << (isInside(polygon, test1) ? "Inside" : "Outside") << std::endl;
std::cout << (isInside(polygon, test2) ? "Inside" : "Outside") << std::endl;
```

Output
```
Inside
Outside
```

-> 🧮 ```polygonArea(polygon)``` - Computes the area of a simple (non-self-intersecting) polygon using the Shoelace formula.
```
std::vector<Point<double>> polygon = {
    {0, 0}, {10, 0}, {10, 10}, {0, 10}
};

std::cout << "Polygon area: " << polygonArea(polygon) << std::endl;
```

Output
```
Polygon area: 100
```

-> ⚡ ```closestPair(points)``` - Finds the minimum distance between any two points in a set using a divide-and-conquer approach.

```
std::vector<Point<double>> points = {
    {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}
};

long double dist = closestPair(points);

std::cout << "Closest pair distance: " << dist << std::endl;
```

Output
```
Closest pair distance: 1.41421
```

-> 📐 ```polygonDiameter(points)``` - Computes the maximum distance between any two points in a set (using Convex Hull + Rotating Calipers).

```
std::vector<Point<double>> points = {
    {0, 0}, {0, 10}, {10, 0}, {10, 10}
};

long double diameter = polygonDiameter(points);

std::cout << "Polygon diameter: " << diameter << std::endl;
```

Output
```
Polygon diameter: 14.1421
```

### 🧩 Full Example Program

```
#include <iostream>
#include <vector>
#include "comp_geom.cxx"

using namespace CompGeom;

signed main() {
    std::vector<Point<double>> pts = {
        {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}
    };

    auto hull = convexHull(pts);
    std::cout << "Hull Points:\n";
    for (auto& p : hull) std::cout << "(" << p.x << ", " << p.y << ")\n";

    Point<double> test(1, 2);
    std::cout << "Inside hull? " << (isInside(hull, test) ? "Yes" : "No") << std::endl;

    std::cout << "Hull Area: " << polygonArea(hull) << std::endl;
    std::cout << "Hull Diameter: " << polygonDiameter(pts) << std::endl;

    return 0;
}
```

### ✅ Summary
| Function            | Description                                  | Example Complexity |
| ------------------- | -------------------------------------------- | ------------------ |
| `orientation()`     | Orientation of 3 points                      | O(1)               |
| `onSegment()`       | Checks if point lies on a segment            | O(1)               |
| `doIntersect()`     | Tests intersection between two line segments | O(1)               |
| `convexHull()`      | Computes convex hull of point set            | O(n log n)         |
| `isInside()`        | Checks if a point is inside a polygon        | O(n)               |
| `polygonArea()`     | Computes polygon area                        | O(n)               |
| `closestPair()`     | Finds the closest pair of points             | O(n log n)         |
| `polygonDiameter()` | Finds the farthest pair of points            | O(n log n)         |


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
