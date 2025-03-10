#include "dijkstras.h"

int main() {
    Graph g;
    file_to_graph("small.txt", g);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(g, source, previous);

    for (int i = 0; i < g.numVertices; ++i){
        print_path(extract_shortest_path(distances, previous, i), distances[i]);
    }
}