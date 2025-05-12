```cpp
// This program finds the closest pair of points in a given set of points using the divide-and-conquer algorithm.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <float.h>

using namespace std;

typedef pair<double, double> Point;

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

pair<double, pair<Point, Point>> bruteForce(const vector<Point>& points) {
    double min_dist = DBL_MAX;
    pair<Point, Point> closest_pair;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double dist = distance(points[i], points[j]);
            if (dist < min_dist) {
                min_dist = dist;
                closest_pair = make_pair(points[i], points[j]);
            }
        }
    }
    return make_pair(min_dist, closest_pair);
}

pair<double, pair<Point, Point>> closestSplitPair(const vector<Point>& points_x, const vector<Point>& points_y, double delta) {
    double mid_x = points_x[points_x.size() / 2].first;
    vector<Point> strip;
    for (const auto& p : points_y) {
        if (abs(p.first - mid_x) < delta) {
            strip.push_back(p);
        }
    }

    double min_dist = delta;
    pair<Point, Point> closest_pair;

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < min(strip.size(), i + 8); ++j) {
            double dist = distance(strip[i], strip[j]);
            if (dist < min_dist) {
                min_dist = dist;
                closest_pair = make_pair(strip[i], strip[j]);
            }
        }
    }
    return make_pair(min_dist, closest_pair);
}

pair<double, pair<Point, Point>> closestPairRecursive(const vector<Point>& points_x, const vector<Point>& points_y) {
    size_t n = points_x.size();

    if (n <= 3) {
        return bruteForce(points_x);
    }

    size_t mid = n / 2;
    vector<Point> left_x(points_x.begin(), points_x.begin() + mid);
    vector<Point> right_x(points_x.begin() + mid, points_x.end());

    double mid_x_value = points_x[mid].first;

    vector<Point> left_y;
    vector<Point> right_y;
    for (const auto& p : points_y) {
        if (p.first <= mid_x_value) {
            left_y.push_back(p);
        } else {
            right_y.push_back(p);
        }
    }

    pair<double, pair<Point, Point>> left_result = closestPairRecursive(left_x, left_y);
    pair<double, pair<Point, Point>> right_result = closestPairRecursive(right_x, right_y);

    double delta;
    pair<Point, Point> closest_pair;
    if (left_result.first <= right_result.first) {
        delta = left_result.first;
        closest_pair = left_result.second;
    } else {
        delta = right_result.first;
        closest_pair = right_result.second;
    }

    pair<double, pair<Point, Point>> split_result = closestSplitPair(points_x, points_y, delta);

    if (split_result.first < delta) {
        return split_result;
    } else {
        return make_pair(delta, closest_pair);
    }
}

pair<double, pair<Point, Point>> closestPairOfPoints(vector<Point>& points) {
    if (points.empty() || points.size() < 2) {
        return make_pair(DBL_MAX, make_pair(Point(0,0), Point(0,0)));
    }

    vector<Point> points_x = points;
    sort(points_x.begin(), points_x.end(), [](const Point& a, const Point& b) {
        return a.first < b.first;
    });

    vector<Point> points_y = points;
    sort(points_y.begin(), points_y.end(), [](const Point& a, const Point& b) {
        return a.second < b.second;
    });

    return closestPairRecursive(points_x, points_y);
}

int main() {
    vector<Point> points = {
        {0, 0}, {1, 1}, {0, 1}, {1, 0}
    };

    pair<double, pair<Point, Point>> result = closestPairOfPoints(points);

    cout << "Minimum distance: " << result.first << endl;
    cout << "Closest pair: (" << result.second.first.first << ", " << result.second.first.second << ") and ("
         << result.second.second.first << ", " << result.second.second.second << ")" << endl;

    return 0;
}
```