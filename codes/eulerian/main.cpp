#include <bits/stdc++.h>

using namespace std;

#define luint long unsigned int

class Graph {
    public:

    vector<vector<int>> adj; //adjascent list

    vector<int> ans; //answer, eulerian cycle path

    int vnum; //number of vertices

    int edges; //number of edges

    luint fixedEdges; //fixed number of edges (doesnt change)

    Graph(int v, int e) { 
        this->vnum = v;
        this->edges = e;
        this->fixedEdges = (luint)e;
        adj.resize(v+1);
    }

    void insertEdge(int a, int b) { 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void removeEdge(int a, int b) {
        for(luint i=0; i<adj[a].size(); i++) {
            if(adj[a][i] == b)
                adj[a].erase(adj[a].begin() + i);
        }
        for(luint i=0; i<adj[b].size(); i++) {
            if(adj[b][i] == a)
                adj[b].erase(adj[b].begin() + i);
        }
    }

    bool existEdge(int a, int b) {
        for(luint i=0; i<adj[a].size(); i++){
            if(adj[a][i] == b)
                return true;
        }
        return false;
    }

    void printAns() {
        for(luint i=0; i<ans.size(); i++)
            cout << ans[i] << " ";
        cout << ans[0];
    }

    bool findEulerianCycle(int a, int first) { 
        // tries to find eulerian cycle, stores in ans
        for(int i=0; i<vnum; i++) {
            if(existEdge(a, i)) { // edge exists
                if(adj[i].size() > 1 || edges == 1) { // edge 'a' non bridge or only possible opition
                    if(edges == 1) { // last one needs to connect with first one
                        if(!existEdge(a, first)) return false;
                    }
                    removeEdge(a, i); // removes edge
                    edges--; // -1 edge
                    ans.push_back(a); // stores in ans
                    findEulerianCycle(i, first);
                }
            }
        }
        return ans.size() == fixedEdges;
    }

    bool isEulerian() {
        // counting edges with odd degree
        int odds = 0; 
        int a = 0; // least significant node with odd degree
        for(int i=vnum-1; i>=0; i--) {
            if(adj[i].size()%2 == 1) {
                odds++;
                a = i;
            }
            if(adj[i].size() == 0) { // node with no connections
                odds = 100;
            }
        }
        if(odds > 2) // more than 2 edges with odd degree, impossible to be eulerian
            return false;
        else
            return findEulerianCycle(a, a);
    }
};

Graph readInput() {
    char fileName[100];
    scanf("%s", fileName);

    FILE *file = fopen(fileName, "r");

    // reading data from txt file (graph connections)
    int edges, verticesNumber; 
    fscanf(file, "%d %d", &verticesNumber, &edges);
    Graph g(verticesNumber, edges);
    int a, b;
    for(int i=0; i<edges; i++) {
        // storing edges
        fscanf(file, "%d %d", &a, &b);
        g.insertEdge(a, b);
    }

    fclose(file);

    return g;
}

int main() {
    Graph g = readInput();

    if(g.isEulerian()) {
        cout << "Sim\n";
        g.printAns();
    }
    else    
        cout << "Não\n";

    return 0;
}
