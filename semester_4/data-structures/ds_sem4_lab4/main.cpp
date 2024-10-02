#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    static double distance(const Point& p1, const Point& p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
};

/**
 * Calculates min distance between points simply by bruteforce.
 *
 * @param points - vector of points
 * @param left - left index
 * @param right - right index
 * @return pair of min distance and pair of points
 */
pair<double, pair<Point, Point>> getMinDistancePair(const vector<Point>& points, int left, int right) {
    double minDist = numeric_limits<double>::infinity();
    pair<Point, Point> minPair;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            double dist = Point::distance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                minPair = {points[i], points[j]};
            }
        }
    }
    return {minDist, minPair};
}

/**
 * Finds closest pair of points that are split between left and right.

 *
 * @param sortedByX - vector of points sorted by x
 * @param sortedByY - vector of points sorted by y
 * @param left - left index
 * @param right - right index
 * @param minDistance - min distance
 * @param closestPair - best pair of points
 * @return
 */
pair<double, pair<Point, Point>> closestSplitPair(
        const vector<Point>& sortedByX,
        const vector<Point>& sortedByY,
        int left,
        int right,
        double minDistance,
        pair<Point, Point> closestPair
        ) {
    int mid = left + (right - left) / 2;
    int midX = sortedByX[mid].x;

    vector<Point> strip;
    for (const auto& point : sortedByY) {
        if (abs(point.x - midX) < minDistance) {
            strip.push_back(point);
        }
    }

    double closestDistance = minDistance;
    auto stripSize = strip.size();
    for (int i = 0; i < stripSize - 1; ++i) {
        for (int j = i + 1; j < stripSize && (strip[j].y - strip[i].y) < closestDistance; ++j) {
            double dist = Point::distance(strip[i], strip[j]);
            if (dist < closestDistance) {
                closestPair = {strip[i], strip[j]};
                closestDistance = dist;
            }
        }
    }
    return {closestDistance, closestPair};
}

/**
 * Recursive function to find closest pair of points. Divide and conquer approach.
 *
 * @param sortedByX - vector of points sorted by x
 * @param sortedByY - vector of points sorted by y
 * @param left - left index
 * @param right - right index
 * @return pair of min distance and pair of points
 */
pair<double, pair<Point, Point>> closestPairRec(const vector<Point>& sortedByX, const vector<Point>& sortedByY, int left, int right) {
    if (right - left <= 3) {
        return getMinDistancePair(sortedByX, left, right);
    }

    // Find middle point
    int mid = left + (right - left) / 2;
    Point midPoint = sortedByX[mid];

    // Divide points in two halves
    vector<Point> leftY, rightY;
    for (const auto& point : sortedByY) {
        if (point.x <= midPoint.x) {
            leftY.push_back(point);
        } else {
            rightY.push_back(point);
        }
    }

    // Recur for left and right halves
    auto [leftDist, leftClosest] = closestPairRec(sortedByX, leftY, left, mid);
    auto [rightDist, rightClosest] = closestPairRec(sortedByX, rightY, mid, right);

    // Find the smaller distance
    double minDistance = min(leftDist, rightDist);
    pair<Point, Point> closestPair = (leftDist < rightDist) ? leftClosest : rightClosest;

    // Find the closest pair of points that are split between left and right
    auto [splitDist, splitClosest] = closestSplitPair(sortedByX, sortedByY, left, right, minDistance, closestPair);

    // Return the smallest one
    if (minDistance <= splitDist) {
        return {minDistance, closestPair};
    } else {
        return {splitDist, splitClosest};
    }
}

/**
 * Finds closest pair of points. Wrapper function for the recursive one.
 *
 * @param points - vector of points
 * @return pair of min distance and pair of points
 */
pair<double, pair<Point, Point>> closestPair(vector<Point>& points) {
    vector<Point> sortedByX = points;
    vector<Point> sortedByY = points;

    // Sort by x and y
    sort(sortedByX.begin(), sortedByX.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    sort(sortedByY.begin(), sortedByY.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    return closestPairRec(sortedByX, sortedByY, 0, points.size());
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    auto [minDist, closestPoints] = closestPair(points);

    cout << "Min dist: " << minDist << endl;
    cout << "Closest points: (" << closestPoints.first.x << ", " << closestPoints.first.y << ") and ("
         << closestPoints.second.x << ", " << closestPoints.second.y << ")" << endl;

    return 0;
}
