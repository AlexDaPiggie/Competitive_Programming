#include <iostream>
#include <vector> 
#include <functional>
#include <queue> 
#include <utility>
using namespace std;

void solve () {
    int n, k, u, v, c;
    cin >> n >> k; // n vertices, k colors

    //Build tree
    vector <vector<int>> adj;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    
    //Save colors
    vector<int> C(k);
    for (int i = 0; i < k; i++){
        cin >> C[i];
    }

    //dfs traversal 
    int root = -1;
    for (int i = 0; i < n; i++){
        if (adj[i].size() == 1) {continue;}
        root = i; 
        break;
    }
    
    vector <int> parent(n, -1);
    vector <int> sub_leaves (n, 0);
    vector <int> order (n);
    function<void(int, int)> dfs = [&](int v, int p) {
        parent[v] = p;
        for (int u : adj[v]) {
            if (u == p) {continue;}
            dfs(u, v);
            sub_leaves[v] += sub_leaves[u];
        }
        order.push_back(v);
    };
    dfs(root, -1);

    //count leaves
    int L = 0;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            L++;
        }
    }

    //finding leaf centroid
    /*
    - Leaf centroid has to seperate the upper half to L / 2
    - Create subtrees all with leaves < L / 2
    */
    int x = -1;
    for (int v : order){
        bool satisfy = ((L - sub_leaves[v]) <= L / 2);
        if (!satisfy) {continue;}
        for (int u : adj[v]){
            if (sub_leaves[u] > L / 2) satisfy = false;
        }
        if (satisfy) {
            x = v; 
            break;
        }
    }

    //Save leaves of each group
    vector<vector <int>> groups;
    for (int start : adj[x]) {
        vector<int> leaves;
        function<void(int, int)> collect = [&](int v, int p){
            if (adj[v].size() == 1) {
                leaves.push_back(v);
            }
            for (int u : adj[v]) {
                if (u == p) {continue;}
                collect (u, v);
            }
        };
        collect(start, x);
        if (!leaves.empty()) {
            groups.push_back(leaves);
        }
    }
    int G = groups.size();

    //store leaves indices with priority queue -> heling to decide at a specific time, which is the groups that had the most number of unpainted leaves.
    priority_queue<pair<int, int>> pq;
    for (int g = 0; g < G; g++) {
        pq.push ({groups[g].size(), g});
    }
    
    //Color the leaves
    vector<int> ptr (G, 0);
    vector<int> color (n, -1);
    int unpainted = L;

    auto paint_vertex = [&](int g, int c){};
    auto get_top = [&]() -> pair<int, int> {};

    for (int i = 0; i < k; i++) {
        if (C[i] < 2) {continue;} 
        int rem = C[i];
        while (rem > 0 && unpainted > 0){
            /*
            only one last unpainted leaf:
                - That leaf will automatically also be the last leaf of a group 
                - Use paint_vertex to paint last vertex with the current color
                - Use paint_vertex to paint centroid with the same color
            */
            if (unpainted == 1)  {
                for (int g = 0; g < G; g++){
                    //Check if this group has one last unpainted leaf
                    if (ptr[g] < groups[g].size()) {
                        paint_vertex(g, i + 1);
                    }
                    if (color[x] == -1){
                        paint_vertex(x, i + 1);
                    }
                    unpainted = 0; //break the loop
                }
            }

            /*
            If the current color has enough slot for the remaining leaves -> we will just spamming it for all remaining leave
            */

            if (C[i] >= unpainted){
                while (unpainted > 0){
                    auto[cnt, g] = get_top();
                    pq.pop();
                    paint_vertex(g, i + 1);
                    
                }
            }
        }
    }

    return;
}

int main() {
    int t; 
    for (int i = 0; i < t; i++) {
        solve();
    }
}

//Link Problem: https://atcoder.jp/contests/abc453/tasks/abc453_f
/*
g++ .\Avoid_Division.cpp -o .\main.exe
@"
2
5 3
1 2
1 3
2 4
2 5
2 2 2
3 3
1 2
2 3
1 1 1
"@ | ./main.exe
*/
