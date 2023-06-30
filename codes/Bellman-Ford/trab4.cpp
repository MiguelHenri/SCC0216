#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

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
