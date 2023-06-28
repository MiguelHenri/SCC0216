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

    Graph(int v, int e) { 
        this->vert = v;
        this->edges = e;
    }

    void insertEdge(int a, int b, int w) { 
        arrayEdges.push_back(Edge{a, b, w});
    }

    void relax(int a, int b, int w, int dist[], int antec[], int weiAntec[]) {
        if ((dist[a] != INT_MAX) && (dist[b] >= dist[a] + w)) {
            dist[b] = dist[a] + w;
            if (weiAntec[b] > w) {
                antec[b] = a;
                weiAntec[b] = w;
            }
        }
    }

    int BFVip(int cityDest, int antec[], int dist[]) {
        // array with visited vertices
        bool visited[vert];
        // initializing with false
        for (int i=0; i<vert; i++) visited[i] = false;

        // visiting cities in the way to cityDest
        visited[cityDest] = true; int ant;
        for (ant = antec[cityDest]; ant != -1; ant = antec[ant])
            visited[ant] = true;

        // non visited customers
        int nonVisited = 0;
        for (int i=0; i<vert; i++) 
            if (visited[i] == false)
                nonVisited++;
        
        // vip cost = vip dist * non visited customers
        return dist[cityDest] * nonVisited;
    }

    int BFStd(int source, int antec[], int weiAntec[]) {
        int standard = 0;

        // mapping crossed edges
        map<pair<int, int>, bool> crossed;

        // shortest path to all vertices from source
        for (int i=0; i<vert; i++) {
            if (i == source) continue;

            int ant;
            for (ant = antec[i]; ant != -1; ant = antec[ant]) {
                // if not crossed yet
                if (crossed[{i, antec[i]}] == false &&
                    crossed[{antec[i], i}] == false) {
                    
                    // summing weight
                    standard += weiAntec[i];

                    // marking as crossed
                    crossed[{i, antec[i]}] = true;
                    crossed[{antec[i], i}] = true;
                }
            }
        }

        return standard;
    }

    /*
    * Bellman-Ford argorithm applied to the problem
    * uses relax to get minimum distances between source and other vertices
    * uses BFVip and BFStd to calculate vip and standard delivery costs
    * returns a pair with vip and standard delivery costs
    */
    pair<int, int> BF(int cityDest) {
        // source = 0 (the problem defined)
        int source = 0;

        // array to store distances
        int dist[vert];

        // array to store antecedents
        int antec[vert];

        // array to store weight between antecedents
        int weiAntec[vert];

        // initializing values
        for (int i=0; i<vert; i++) {
            dist[i] = INT_MAX;
            antec[i] = -1;
            weiAntec[i] = INT_MAX;
        }
        dist[source] = 0;
        
        // relaxing edges and determining shortest paths
        for (int i=1; i<vert; i++) {
            for (int j=0; j<edges; j++) {
                int a = arrayEdges[j].source;
                int b = arrayEdges[j].dest;
                int w = arrayEdges[j].weight;
                relax(a, b, w, dist, antec, weiAntec);
            }
        }

        // getting VIP delivery cost
        int vip = BFVip(cityDest, antec, dist);
        
        // getting Standard delivery cost
        int standard = BFStd(source, antec, weiAntec);

        // returns std and vip
        return make_pair(vip, standard);

    }
};

void printAns(int vip, int standard) {
    if (standard > vip) 
        cout << "VIP\n" << vip << "\n";
    else if (standard < vip) 
        cout << "PADRAO\n" << standard << "\n";
    else 
        cout << "NDA\n" << vip << "\n";
}

int main() {
    // reading input and creating graph
    int v, e;
    cin >> v >> e;

    Graph g(v, e);

    for (int i=0, a, b, w; i<e; i++) {
        cin >> a >> b >> w;
        g.insertEdge(a, b, w);
    }

    // Pedro's city
    int c; cin >> c;

    // Bellman-Ford algorithm
    // returns Standard and VIP distance in a pair
    pair<int, int> ans = g.BF(c);

    // prints answer
    printAns(ans.first, ans.second);

    return 0;
}
