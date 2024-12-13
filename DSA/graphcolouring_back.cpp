#include <iostream>
#include <vector>
using namespace std;

#define V 4

// all functions are boolean

bool isSafe(int v,  vector<vector<bool>> &graph,  vector<int> &color, int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c) // if v to i is edge and color of neighbour i is same the return false
            return false;
    return true;
}

bool graphColoringUtil( vector<vector<bool>> &graph, int m, vector<int> &color, int v) {
    
    // if all vertex all reach then return true, base condition
    if (v == V) return true;

    for (int c = 1; c <= m; c++) {
        
        if (isSafe(v, graph, color, c)) {
            
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            color[v] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    vector<vector<bool>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3; // Number of colors m = V-1

    vector<int> color(V, 0);

    // adj graph, number of colors, color graph, starting vertex
    if (graphColoringUtil(graph, m, color, 0)) {
        cout<<"Solution exist :"<<endl;
        for(int i = 0; i < V; i++){
            cout<<"Vertex "<<i<<" -> colour "<<color[i]<<endl;
        }
    }
    else
        cout << "Solution does not exist.\n";

    return 0;
}
