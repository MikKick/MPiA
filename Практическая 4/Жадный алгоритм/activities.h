#pragma once

#include "activity.h"
#include "iostream"
#include <vector>
#include <algorithm>
#include <random>
#include <list>
#include <chrono>
using namespace std;
// Get a maximum-size subset of mutually compatible activities.
vector<Activity> random_sequence(int size, int min, int max);
vector<Activity> get_max_activities_native(const std::vector<Activity>& activities);
vector<Activity> get_max_activities(const std::vector<Activity> &activities);