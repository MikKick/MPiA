#include "min_spanning_tree.h"
#define inf 100000
using namespace std;

//O(VlnV+ElnV) = O(ElnV)
std::vector<std::pair<int, int>> min_spanning_tree(const Graph &graph) {
	if (graph.get_vertices().size() == 0)
		return {};
	int u,v;
	vector<bool> inMST(graph.get_vertices().size(), false);
	vector<pair<int, int>> result;
	priority_queue <pair<int, double>, vector<pair<int, double>>, CompareDist> Q;
	vector<double> MinWeight(graph.get_vertices().size(), inf);
	vector<int> Parent(graph.get_vertices().size(), -1);
	MinWeight[0] = 0;
	Q.push({ 0, 0 });
	while (!Q.empty())
	{
		u = Q.top().first;
		Q.pop();
		if (inMST[u] == true) {
			continue;
		}
		inMST[u] = true;
		auto adjacent = graph.get_adjacent_edges(u);
		for (int i = 0; i < adjacent.size(); i++)
		{
			v = adjacent[i].first;
			if (!inMST[v] && MinWeight[v] > graph.edge_weight(u, v))
			{
				MinWeight[v] = graph.edge_weight(u, v);
				Parent[v] = u;
				Q.push({ v,  MinWeight[v] });
			}
		}
	}
	for (int i = 1; i < graph.get_vertices().size(); i++)
		result.push_back(make_pair(i, Parent[i]));

	return result;
}






