#include "graph.h"
#include <algorithm>
#include <stdexcept>
#include <set>
#include "iostream"
using namespace std;

Graph::Graph(initializer_list<tuple<int, int, double>> edges) {
    for (const auto &e: edges) {
        add_edge(get<0>(e), get<1>(e), get<2>(e));

    }
}


void Graph::add_vertex(int vertex) {
    if (!has_vertex(vertex)) {
        vertices[vertex] = std::map<int, double>();
    }
}

void Graph::add_edge(int start_vertex, int end_vertex, double weight) {
    add_vertex(start_vertex);
    add_vertex(end_vertex);
    graph_edges.push_back(std::make_tuple(start_vertex, end_vertex, weight));
    vertices[start_vertex][end_vertex] = weight;
    vertices[end_vertex][start_vertex] = weight;
}


int Find_1(vector<int> Parent, int k)
{
    // если `k` это корень
    if (Parent[k] == k) {
        return k;
    }

    // повторяем для родителя, пока не найдем корень
    return Find_1(Parent, Parent[k]);
}

void Union_1(vector<int>& Parent, int a, int b)
{
    // найти корень множеств, в которых элементы
    // `x` и `y` принадлежат
    int x = Find_1(Parent, a);
    int y = Find_1(Parent, b);
    Parent[x] = y;
}


double random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

void Graph::random_graph(int kol_vertex)
{
    /*for (int i = 0; i < kol_vertex; i++)
        for (int j = i + 1; j < kol_vertex; j++)
            add_edge(i, j, random(1, 10000));*/
    int i = 0;
    vector<int> Parent(kol_vertex);
    set<pair<int, int>> visited;
    while(i != kol_vertex)
    {
        int j = rand() % kol_vertex;
        if (i != j && visited.find(make_pair(i, j)) == visited.end() && visited.find(make_pair(j, i)) == visited.end())
        {
            add_edge(i, j, random(1, 10000));
            visited.insert(make_pair(i, j));
            Union_1(Parent, i, j);
            i++;
        }
    }
    for (auto edge : graph_edges)
    {
        int root_1 = Find_1(Parent, get<0>(edge));
        int root_2 = Find_1(Parent, get<1>(edge));
        if (root_1 != root_2)
        {
            add_edge(get<0>(edge), get<1>(edge), random(1, 10000));
            Union_1(Parent, root_1, root_2);
        }
    }
}

void Graph::clear(int kol_vertex)
{
    for (auto i : graph_edges)
        remove_edge(get<0>(i), get<1>(i));
    for (int i = 0; i < kol_vertex; i++)
        remove_vertex(i);
    graph_edges.clear();
    vertices.clear();
}


std::vector<int> Graph::get_vertices() const {
    std::vector<int> result;
    for (const auto &p: vertices) {
        result.push_back(p.first);
    }
    return result;
}

std::vector<std::tuple<int, int, double>> Graph::get_edges() const {
    std::vector<std::tuple<int, int, double>> result;
    for (const auto& p : graph_edges) {
        result.push_back(p);
    }
    return result;
}

std::vector<int> Graph::get_adjacent_vertices(int src_vertex) const {    
    const auto it = vertices.find(src_vertex);
    if (it == vertices.end()) {
        return std::vector<int> {};
    }
    vector<int> result;
    for (const auto &p: it->second) {
        result.push_back(p.first);
    }
    return result;
}

vector<pair<int, double>> Graph::get_adjacent_edges(int src_vertex) const {
    const auto it = vertices.find(src_vertex);
    if (it == vertices.end()) {
        return vector<pair<int, double>> {};
    }
    vector<pair<int, double>> result;
    for (const auto &p: it->second) {
        result.push_back(make_pair(p.first, p.second));
    }
    return result;
}

bool Graph::has_vertex(int vertex) const {
    return (vertices.find(vertex) != vertices.end());
}

bool Graph::has_edge(int start_vertex, int end_vertex) const {    
    const auto it = vertices.find(start_vertex);
    if (it == vertices.end()) {
        return false;
    }
    return (it->second.find(end_vertex) != it->second.end());
}

double Graph::edge_weight(int start_vertex, int end_vertex) const {        
    const auto it_s = vertices.find(start_vertex);
    if (it_s == vertices.end()) {
        throw invalid_argument("Edge doesn't exist");
    }
    const auto it_e = it_s->second.find(end_vertex);
    if (it_e == it_s->second.end()) {
        throw invalid_argument("Edge doesn't exist");   
    }
    return it_e->second;
}

void Graph::remove_vertex(int vertex) {
    /// Remove adjacent edges.
    auto adjacent_vertices = get_adjacent_vertices(vertex);
    for (const auto &adj_v: adjacent_vertices) {
        remove_edge(adj_v, vertex);
    }
    /// Remove the vertex itself.
    vertices.erase(vertex);    
}

void Graph::remove_edge(int start_vertex, int end_vertex) {
    auto it_s = vertices.find(start_vertex);
    if (it_s != vertices.end()) {
        it_s->second.erase(end_vertex);
    }
    auto it_e = vertices.find(end_vertex);
    if (it_e != vertices.end()) {
        it_e->second.erase(start_vertex);
    }
}