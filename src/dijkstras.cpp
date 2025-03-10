#include "dijkstras.h"
#include <iostream>
using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int num_vertices = G.numVertices;
    vector<int> distances(num_vertices, INF);
    vector<bool> visited(num_vertices, false);
    distances[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();
        if (visited[u]) { continue; }
        visited[u] = true;

        for (Edge e : G[u] ) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    vector<int> path_backwards;
    if (distances[destination] == INF) {
        return path;
    }
    for (int i = destination; i != -1; i = previous[i]) {
        path_backwards.push_back(i);
    }
    if (!path_backwards.empty()) {
        for (int j = 0; j < path_backwards.size(); ++j) {
            path.push_back(path_backwards[j]);
        }    
    }
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (path.empty()) {
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
    cout << "Total cost is" << total << endl;
}
