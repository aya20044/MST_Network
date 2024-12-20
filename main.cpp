#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent;
    int rank;
};
int findParent(vector<Subset>& subsets, int node) {
    if (subsets[node].parent != node) {
        subsets[node].parent = findParent(subsets, subsets[node].parent);
    }
    return subsets[node].parent;
}

//function to union two subsets by rank
void unionSubsets(vector<Subset>& subsets, int u, int v) {
    int rootU = findParent(subsets, u);
    int rootV = findParent(subsets, v);

    if (subsets[rootU].rank < subsets[rootV].rank) {
        subsets[rootU].parent = rootV;
    } else if (subsets[rootU].rank > subsets[rootV].rank) {
        subsets[rootV].parent = rootU;
    } else {
        subsets[rootV].parent = rootU;
        subsets[rootU].rank++;
    }
}

//function to implement Kruskal's algorithm
void kruskalMST(vector<Edge>& edges, int V) {
    //sort all edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    //create subsets for union-find
    vector<Subset> subsets(V);
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> mst; //to store the resulting MST
    int mstWeight = 0;

    //pick the smallest edge and check if it forms a cycle
    for (const auto& edge : edges) {
        int u = findParent(subsets, edge.src);
        int v = findParent(subsets, edge.dest);

        //if including this edge doesn't form a cycle
        if (u != v) {
            mst.push_back(edge); // Add edge to MST
            mstWeight += edge.weight;
            unionSubsets(subsets, u, v);
        }
    }

    //Print the MST
    cout << "Edges in the MST:\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << "\n";
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}


int main() {
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    kruskalMST(edges, V);

    return 0;
}
