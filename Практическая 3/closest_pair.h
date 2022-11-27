#pragma once

#include "point.h"
#include <algorithm>
#include <vector>
#include "iostream"
#include <chrono>

// Find the closest pair of points from given points.
std::pair<Point, Point> closest_pair_between(const std::vector <Point> &PLeft, const std::vector <Point>& PRight, double d);
std::pair<Point, Point> closest_pair_trivial(const std::vector<Point> &points);
std::pair<Point, Point> closest_pair(const std::vector<Point>& points);