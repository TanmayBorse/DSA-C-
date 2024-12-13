#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

const int INF = INT_MAX;

int f(int u, int v, int k, vector<vector<int>>& dp, const vector<vector<int>>& graph) {
    if (k == -1) {
        return graph[u][v];
    }

    if (dp[u][v] != -1) return dp[u][v];

    int notTake = f(u, v, k - 1, dp, graph);

    int take = INF;

    // if u to k and k to v not infinity
    if (f(u, k, k - 1, dp, graph) != INF && f(k, v, k - 1, dp, graph) != INF) {
        
        take = f(u, k, k - 1, dp, graph) + f(k, v, k - 1, dp, graph);
    }

    return dp[u][v] = min(notTake, take);
}

void floydWarshall(const vector<vector<int>>& graph) {
    int vertices = graph.size();

    vector<vector<int>> dp(vertices, vector<int>(vertices, -1));

    for (int u = 0; u < vertices; ++u) {
        for (int v = 0; v < vertices; ++v) {
            f(u, v, vertices - 1, dp, graph);
        }
    }

    cout << "Shortest distances between every pair of vertices:" << endl;
    for (int u = 0; u < vertices; ++u) {
        for (int v = 0; v < vertices; ++v) {
            if (dp[u][v] == INF)
                cout << "INF ";
            else
                cout << dp[u][v] << " ";
        }
        cout << endl;
    }
}

int main() {
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    vector<vector<int>> graph(vertices, vector<int>(vertices));

    cout << "Enter the adjacency matrix (use " << INF << " for no edge):" << endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF; // Set distance to INF for no edge
            }
        }
    }

    floydWarshall(graph);

    return 0;
}

/*
input 

0 5 INF 10
INF 0 3 INF
INF INF 0 1
INF INF INF 0

output 

0 5 8 9 
INF 0 3 4 
INF INF 0 1 
INF INF INF 0
*/