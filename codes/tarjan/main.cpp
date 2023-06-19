#include <bits/stdc++.h>

using namespace std;

class Graph {
    public:

    vector<vector<int>> adj; //adjascent list

    int vnum; //number of vertices

    int edges; //number of edges

    Graph(int v, int e) { 
        this->vnum = v;
        this->edges = e;
        adj.resize(v+1);
    }

    void insertEdge(int a, int b) { 
        adj[a].push_back(b);
    }

    void dfsSCC(int v, int discoveryTime[], int low[], stack<int> *scc, bool isStacked[], int *time, set<set<int>> *ans) {

        // updating time and disc/low values
        discoveryTime[v] = ++(*time);
        low[v] = *time;
        // adding to stack
        (*scc).push(v);
        isStacked[v] = true;

        // running adj vertices
        for(int i=0; i<(int)adj[v].size(); i++) {
            int w = adj[v][i];
            
            if(discoveryTime[w] == -1) { // was not discovered
                // keeps dfs
                dfsSCC(w, discoveryTime, low, scc, isStacked, time, ans); 
                // checks if v gets to w's ancestor
                low[v] = min(low[v], low[w]);
            }

            // cheks if v was already visited and
            // gets to w's ancestor
            else if(isStacked[w] == true) {
                low[v] = min(low[v], discoveryTime[w]);
            }
        }

        // found a head node, stores scc found
        if(low[v] == discoveryTime[v]) {
            // temporary set, stores a full SCC
            set<int> temp;

            // getting components
            int t;
            do {
                t = (*scc).top();
                temp.insert(t);
                isStacked[t] = false;
                (*scc).pop();
            } while(t != v);

            (*ans).insert(temp);
        }
    }

    // ans gets a set of sets with the scc's components
    set<set<int>> findSCC() {
        // function return answer
        set<set<int>> ans;

        // variable now has the current time
        int now = 0;

        // vector of discovery time
        int discoveryTime[vnum];
        // low (last found) vector
        int low[vnum];
        // stack used in tarjan algorithm
        stack<int> scc;
        // vector to check if vertice is isStacked
        bool isStacked[vnum];

        // initializing values
        for(int i=0; i<vnum; i++) {
            discoveryTime[i] = -1;
            low[i] = -1;
            isStacked[i] = false;
        }

        // running dfs trought the graph
        for(int v=0; v<vnum; v++) {
            if(discoveryTime[v] == -1)
                dfsSCC(v, discoveryTime, low, &scc, isStacked, &now, &ans);
        }

        return ans;
    }
    
};

void print(set<set<int>> ans) {
    cout << ans.size() << "\n";
    for(auto i = ans.begin(); i != ans.end(); ++i) {
        for(auto j = (*i).begin(); j != (*i).end(); ++j) {
            if(++j == (*i).end()) {
                j--;
                cout << *j << "\n";
            }
            else {
                j--;
                cout << *j << " ";
            }
        }
    }
}

int main() {
    // reading input and creating graph
    int v, e;
    cin >> v >> e;

    Graph g(v, e);

    for(int i=0, a, b; i<e; i++) {
        cin >> a >> b;
        g.insertEdge(a, b);
    }

    // calculating strongly connected components (SCC) and returning answer
    set<set<int>> ans = g.findSCC();

    // printing answer
    print(ans);

    return 0;
}
