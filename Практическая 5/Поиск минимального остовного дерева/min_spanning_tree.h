#pragma once

#include "graph.h"

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include "iostream"
#include <chrono>
#include <algorithm>
using namespace std;

// Return minimal spanning tree for the (connected) graph as array of edges.
std::vector<std::pair<int, int>> min_spanning_tree(const Graph &graph);


class CompareDist
{
public:
    bool operator()(pair<int, double> n1, pair<int, double> n2) {
        return n1.second > n2.second;
    }
};