#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

// This is the working code provided in the prompt's first turn.
// I am comparing this against the user's latest code.
// The primary difference is the structure of the logic flow and
// how the priority queue and unpainted leaves are managed.

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

    if (N == 2) {
        int col = -1;
        for (int i = 0; i < K; i++) {
            if (C[i] >= 2) { col = i + 1; break; }
        }
        if (col == -1) cout << "-1\n";
        else cout << col << " " << col << "\n";
        return;
    }

    int L = 0;
    for (int i = 0; i < N; i++) {
        if (adj[i].size() == 1) L++;
    }

    int root = -1;
    for (int i = 0; i < N; i++) {
        if (adj[i].size() > 1) { root = i; break; }
    }

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

    int X = -1;
    for (int v : order) {
        if (adj[v].size() == 1) continue; 
        bool ok = ((L - sub_leaves[v]) <= L / 2);
        if (!ok) continue;
        for (int u : adj[v]) {
            if (u == parent[v]) continue;
            if (sub_leaves[u] > L / 2) { ok = false; break; }
        }
        if (ok) { X = v; break; }
    }

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

    for (int i = 0; i < K; i++) {
        if (C[i] < 2) continue;
        int rem = C[i];

        while (rem > 0 && unpainted > 0) {
            clean_top();
            if (pq.empty()) break;

            if (unpainted == 1) {
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
