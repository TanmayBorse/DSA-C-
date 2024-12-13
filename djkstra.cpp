#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

// Function to find the vertex with the minimum distance value, from the set of vertices not yet processed.
int findMinDistanceVertex(const vector<int>& distances, const vector<bool>& visited, int vertices) {
    int minDistance = INT_MAX;
    int minVertex = -1;

    for (int v = 0; v < vertices; ++v) {
        if (!visited[v] && distances[v] < minDistance) {
            minDistance = distances[v];
            minVertex = v;
        }
    }
    return minVertex;
}

// Dijkstra's algorithm
void dijkstra(const vector<vector<int>>& graph, int source) {
    int vertices = graph.size();
    vector<int> distances(vertices, INT_MAX); // Distance from source to each vertex
    vector<bool> visited(vertices, false);   // Track visited vertices
    distances[source] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        int u = findMinDistanceVertex(distances, visited, vertices);
        visited[u] = true;

        // Update distances for adjacent vertices
        for (int v = 0; v < vertices; ++v) {
            if (!visited[v] && graph[u][v] && distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
            }
        }
    }

    // Print the distances
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < vertices; ++i) {
        cout << i << "\t" << distances[i] << endl;
    }
}

int main() {
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    vector<vector<int>> graph(vertices, vector<int>(vertices));

    cout << "Enter the adjacency matrix (use 0 for no edge):" << endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cin >> graph[i][j];
        }
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    dijkstra(graph, source);

    return 0;
}

/*
0 10 0 0 5
0 0 1 0 2
0 0 0 4 0
7 0 6 0 0
0 3 9 2 0
*/