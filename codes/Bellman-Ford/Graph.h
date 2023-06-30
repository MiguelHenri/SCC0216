#include <bits/stdc++.h>
using namespace std;

struct edge {
    int source;
    int dest;
    int weight;
};

typedef struct edge Edge;

class Graph {
    public:

    int vert; //number of vertices (cities)

    int edges; //number of edges (roads)

    vector<Edge> arrayEdges;

    Graph(int v, int e);

    void insertEdge(int a, int b, int w);

    void relax(int a, int b, int w, int dist[], int antec[], int weiAntec[]);

    int BFVip(int cityDest, int antec[], int dist[]);

    int BFStd(int source, int antec[], int weiAntec[]);

    /*
    * Bellman-Ford argorithm applied to the problem
    * uses relax to get minimum distances between source and other vertices
    * uses BFVip and BFStd to calculate vip and standard delivery costs
    * returns a pair with vip and standard delivery costs
    */
    pair<int, int> BF(int cityDest);
};