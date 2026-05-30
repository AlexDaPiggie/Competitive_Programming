#include <iostream> 
#include <vector>
#include <functional> //DFS
#include <queue> //priority queue
#include <utility>
using namespace std;

void solve() {
    int n, k; // n vertices & k colors;
    cin >> n >> k;

    // Build the tree - adjacency list
    /*
    Strategy: 
        - Store the neighbors of each vertex in a vector
    */
    vector<vector <int>> adj (n); 
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v; 
        u--; v--;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }

    // Save the colors
    vector <int> C (k);
    for (int i = 0; i < k; i ++) {
        cin >> C[i];
    }

    // Handle 2 vertices case
    if (n == 2) {
        int color = -1;
        for (int i = 0; i < k; i++) {
            if (C[i] < 2) {continue;}
            color = i; 
            break;
        }
        if (color == -1) {
            cout << -1 << endl;
        }
        else {
            cout << color + 1 << " " << color + 1 << endl;
        }
        return;
    }

    // Count the number of leaves 
    int L = 0;
    for (int v = 0; v < n; v++) {
        if (adj[v].size() > 1) {continue;}
        L++;
    }

    // Build sub_leaves, parents, order using DFS
    /*
    Strategy: 
        - Find a random root
        - Recursive DFS starting from a random root UNTIL we meet the leaves
        - Post-order tracking
    */

    int root = -1;
    for (int v = 0; v < n; v++){
        //Choose root that is not a leaf
        if (adj[v].size() > 1) {
            root = v; 
            break;
        }
    }

    vector<int> sub_leaves (n, 0);
    vector<int> parents (n, -1);
    vector<int> order;
    function<void(int, int)> dfs = [&](int v, int p) {
        parents[v] = p;
        bool isleaf = true;
        for (int u : adj[v]){
            if (u == p) {continue;} // break because we reach a leaf
            isleaf = false;
            dfs(u, v);
            sub_leaves[v] += sub_leaves[u];
        }
        if (isleaf) {
            sub_leaves[v] = 1;
        }
        order.push_back (v);
    };
    dfs(root, -1);

    // Find the leave centroid 
    /*
    Strategy: 
        - initialize centroid = -1
        - Interate in post-order to find the vertex satisfying:
            - Create an upper part with <= L / 2 leaves
            - Create other subtrees (not upper part) with <= L / 2 leaves
        - Assign centroid with that vertex and break
    */

    int x = -1;
    for (int v : order){
        if (adj[v].size() == 1) {continue;}
        //upper part
        bool satisfy = ((L - sub_leaves[v]) <= L / 2);
        if (!satisfy){continue;}

        //remaining part
        if (satisfy){
            for (int u : adj[v]) {
                if (u == parents[v]) {continue;}
                if (sub_leaves[u] > L / 2) {
                    satisfy = false;
                    break;
                }
            }
        }
        if (satisfy) {
            x = v;
            break;
        }
    }

    // Cluster the leaves into groups
    /*
    Strategy: 
        - DFS (check if the vertex is leave)
        - Store leaves into a vector
        - Store vector of leaves into groups (2-D vector)
    */

    vector<vector <int>> groups;
    for (int start : adj[x]) {
        vector <int> leaves; //vector storing leaves
        function <void (int, int)> collect = [&] (int v, int p) {
            //Purpose: store the leaves of each sub tree into leavesr
            if (adj[v].size() == 1)
               leaves.push_back(v);
            for (int u : adj[v]) {
                if (u == p) {continue;} // condition of a leaf
                collect (u, v);
            }
        };
        collect (start, x);
        if (!leaves.empty()){
            groups.push_back(leaves);
        }
    }
    int G = groups.size();
    
    // Create pointer to track the leaves in each group
    /*
    Strategy: 
        - a vector to store the index of each group
        - initialize the index = 0
    */
    vector <int> ptr (G, 0);

    // Track the leaves in each group 
    /*
    Strategy: 
        - Use priority queue to track the group with most unpainted leaves
        - Specify the leave using pointer 
    */

    priority_queue<pair<int, int>> pq;
    for (int g = 0; g < G; g++) {
        pq.push ({groups[g].size(), g});
    }
    
    // Color the leaves
    /*
    Helper function: 
        - paint_leaf (int group, int color):
            Purpose: 
                - Color the leave in the specified group with color i
                - Update the unpainted leaf 

    Variables:
        - unpainted: track # of unpainted leaves
        - rem: track # remaining color 

    Strategy: 
        - Use same Color for the two groups with greatest number of 'unpainted' leaves
        - Spam the same color for the group with greatest number of ......
        - 
    */
   
    int unpainted = L;
    vector <int> color (n, -1);    

    auto paint_leaf = [&](int g, int c) {
        //Purpose: paint the vertex of each group with color c
        unpainted--;
        int v = groups[g][ptr[g]++];
        color[v] = c;
    };
    auto get_top = [&]() -> pair<int, int> {
        while (!pq.empty()){
            auto [cnt, g] = pq.top();
            int actual = groups[g].size() - ptr[g];
            if (actual == 0) {
                pq.pop();
            }
            else if (actual != cnt){
                pq.pop();
                pq.push ({actual, g});
            }
            else {
                return pq.top();
            }
        }
        return {-1, -1};
    };

    for (int i = 0; i < k; i++) {
        if (C[i] < 2) {continue;}
        int rem = C[i];

        while (unpainted > 0 && rem > 0){
            get_top();
            if (pq.empty()) break;

            /*
            Color the current unpainted leaf with the current color
            Color the centroid with the current color
            */
            if (unpainted == 1) {
                for (int g = 0; g < G; g++) {
                    if (ptr[g] >= groups[g].size()){continue;} 
                    paint_leaf(g, i + 1);
                    break;
                }
                if (color[x] == -1)
                    color[x] = i + 1;
                break;
            }
            
            /*
            If we have enough of the current color to paint all the remaining leaves:
                -> Spamming the current color until unpainted = 0
            */
            if (rem >= unpainted) {
                while (unpainted > 0){
                    auto [cnt, g] = get_top();
                    paint_leaf(g, i + 1);
                    rem--;
                    pq.pop(); 
                    if (ptr[g] < groups[g].size()){
                        pq.push ({cnt - 1, g});
                    }                    
                }
                break;
            }

            // Getting the two groups with most unpainted leaves
            auto[cnt1, g1] = get_top();
            pq.pop();
            auto[cnt2, g2] = get_top();
            pq.pop();
            
            paint_leaf(g1, i + 1);
            paint_leaf(g2, i + 1);
            rem -= 2;

            if (ptr[g1] < groups[g1].size()) {
                pq.push ({cnt1 - 1, g1});
            }
            if (ptr[g2] < groups[g2].size()) {
                pq.push ({cnt2 - 1, g2});
            }            

            //drain the group with most unpainted leaves with current color
            while (rem > 0 && unpainted > 0) {
                auto[cnt, g] = get_top();
                if (g == -1) break;
                paint_leaf(g, i + 1);
                rem --;
                pq.pop();
                if (ptr[g] < groups[g].size()) {
                    pq.push ({cnt - 1, g});
                }                            
            }
        }
    }
     
    if (unpainted > 0) {
        cout << -1 << endl;
        return;
    }

    // Color the remaining vertices 
    /*
    Strategy: Spam coloring with the remaining color - 2 Pointers
        - 1st pointer: track the availability of remaining color
        - 2nd pointer: track the index of uncolored vertex
    */
    
    vector <int> used (k, 0); //track the availability of uncolored vertex
    for (int i = 0; i < n; i++) {
        if (color[i] == -1)  {continue;}
        used[color[i] - 1]++;
    }
    
    int ci = 0; //1st pointer to track the availability of remaining color
    for (int i = 0; i < n; i ++ ){
        //get to the uncolored vertex
        if (color[i] != -1) {continue;}
        //jump to available color
        while (ci < k && used[ci] >= C[ci]) ci++;
        color[i] = ci + 1;
        used[ci]++;
    }

    
    for (int i = 0; i < n; i ++){
        cout << color[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
}
int main () {
    int t; cin >> t;
    while (t > 0) {
        solve();
        t--;
    }
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abc453/tasks/abc453_f
/*g++ Avoid_Division.cpp -o main.exe
@"
2
5 3
1 2
1 3
2 4
2 5
2 2 2
3 4
1 2
1 3 
1 1 1 2
"@ | ./main.exe*/