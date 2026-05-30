#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, K;
    cin >> N >> K;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> C(K);
    for (int i = 0; i < K; i++) cin >> C[i];

    // Special case N = 2
    if (N == 2) {
        int col = -1;
        for (int i = 0; i < K; i++) {
            if (C[i] >= 2) { col = i + 1; break; }
        }
        if (col == -1) cout << "-1\n";
        else cout << col << " " << col << "\n";
        return;
    }

    // Count leaves
    int L = 0;
    for (int i = 0; i < N; i++) {
        if (adj[i].size() == 1) L++;
    }

    // Root tree at a non-leaf vertex
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (adj[i].size() > 1) { root = i; break; }
    }

    // DFS to compute subtree leaf counts (post-order)
    vector<int> parent(N, -1), order, sub_leaves(N, 0);
    function<void(int, int)> dfs = [&](int v, int p) {
        parent[v] = p;
        bool is_leaf = true;
        for (int u : adj[v]) {
            if (u == p) continue;
            is_leaf = false;
            dfs(u, v);
            sub_leaves[v] += sub_leaves[u];
        }
        if (is_leaf) sub_leaves[v] = 1;
        order.push_back(v);
    };
    dfs(root, -1);

    // Find centroid X: each component after removal has ≤ L/2 leaves
    int X = -1;
    for (int v : order) {
        if (adj[v].size() == 1) continue; // not a leaf
        bool ok = ((L - sub_leaves[v]) <= L / 2);
        if (!ok) continue;
        for (int u : adj[v]) {
            if (u == parent[v]) continue;
            if (sub_leaves[u] > L / 2) { ok = false; break; }
        }
        if (ok) { X = v; break; }
    }

    // Group leaves by which neighbor of X they belong to
    vector<vector<int>> groups;
    for (int start : adj[X]) {
        vector<int> leaves;
        function<void(int, int)> collect = [&](int v, int p) {
            if (adj[v].size() == 1) leaves.push_back(v);
            for (int u : adj[v]) {
                if (u == p) continue;
                collect(u, v);
            }
        };
        collect(start, X);
        if (!leaves.empty()) groups.push_back(leaves);
    }

    int G = groups.size();
    vector<int> ptr(G, 0);
    vector<int> color(N, -1);
    int unpainted = L;

    // Max-heap: (remaining_leaves, group_index)
    priority_queue<pair<int, int>> pq;
    for (int g = 0; g < G; g++) {
        pq.push({(int)groups[g].size(), g});
    }

    auto paint_leaf = [&](int g, int c) {
        int v = groups[g][ptr[g]++];
        color[v] = c;
        unpainted--;
    };

    auto clean_top = [&]() -> pair<int, int> {
        while (!pq.empty()) {
            auto [cnt, g] = pq.top();
            int actual = (int)groups[g].size() - ptr[g];
            if (actual == 0) {
                pq.pop();
            } else if (cnt != actual) {
                pq.pop();
                pq.push({actual, g});
            } else {
                return pq.top();
            }
        }
        return {-1, -1};
    };

    // Process colors with C_i ≥ 2
    for (int i = 0; i < K; i++) {
        if (C[i] < 2) continue;
        int rem = C[i];

        while (rem > 0 && unpainted > 0) {
            clean_top();
            if (pq.empty()) break;

            if (unpainted == 1) {
                // Paint the last leaf and X
                for (int g = 0; g < G; g++) {
                    if (ptr[g] < (int)groups[g].size()) {
                        paint_leaf(g, i + 1);
                        break;
                    }
                }
                if (color[X] == -1) {
                    color[X] = i + 1;
                }
                rem = 0;
                break;
            }

            if (unpainted <= rem) {
                // Paint all remaining leaves
                while (unpainted > 0) {
                    auto [cnt, g] = clean_top();
                    pq.pop();
                    paint_leaf(g, i + 1);
                    rem--;
                    if (ptr[g] < (int)groups[g].size())
                        pq.push({(int)groups[g].size() - ptr[g], g});
                }
                break;
            }

            // rem < unpainted and unpainted ≥ 2
            // Pop two largest distinct groups
            auto [cnt1, g1] = clean_top();
            pq.pop();
            auto [cnt2, g2] = clean_top();
            pq.pop();

            paint_leaf(g1, i + 1);
            paint_leaf(g2, i + 1);
            rem -= 2;

            if (ptr[g1] < (int)groups[g1].size())
                pq.push({(int)groups[g1].size() - ptr[g1], g1});
            if (ptr[g2] < (int)groups[g2].size())
                pq.push({(int)groups[g2].size() - ptr[g2], g2});

            // Drain remaining capacity on largest groups
            while (rem > 0 && unpainted > 0) {
                auto [cnt, g] = clean_top();
                if (g == -1) break;
                pq.pop();
                paint_leaf(g, i + 1);
                rem--;
                if (ptr[g] < (int)groups[g].size())
                    pq.push({(int)groups[g].size() - ptr[g], g});
            }
        }
    }

    if (unpainted > 0) {
        cout << "-1\n";
        return;
    }

    // Fill remaining internal vertices with any unused capacity
    vector<int> used(K, 0);
    for (int v = 0; v < N; v++) {
        if (color[v] != -1) used[color[v] - 1]++;
    }

    int ci = 0;
    for (int v = 0; v < N; v++) {
        if (color[v] == -1) {
            while (ci < K && used[ci] >= C[ci]) ci++;
            color[v] = ci + 1;
            used[ci]++;
        }
    }

    for (int v = 0; v < N; v++) {
        cout << color[v] << " \n"[v == N - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
