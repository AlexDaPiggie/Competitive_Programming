# Problem F — Avoid Division

## Links

- Problem: https://atcoder.jp/contests/abc453/tasks/abc453_f
- Solution: `solution.cpp`

---

## 1. Input Format

The input has multiple test cases (T of them).

```
T
N K
U1 V1
U2 V2
...
U_{N-1} V_{N-1}
C1 C2 ... C_K
```

| Part | What it means |
|------|--------------|
| `T` | Number of test cases |
| `N K` | Tree has N vertices. There are K colors available. |
| `U_i V_i` | The N-1 edges of the tree. `U_i` and `V_i` are the two vertex numbers (1 to N) connected by edge i. For example, "1 2" means vertex 1 and vertex 2 are connected by an edge. |
| `C_1 ... C_K` | Color i can be used at most `C_i` times |

**Constraints (full ranges):**

| Variable | Range |
|----------|-------|
| T | 1 ≤ T ≤ 10^5 |
| N | 2 ≤ N ≤ 3×10^5 (per test case) |
| Sum of N across all test cases | ≤ 3×10^5 |
| K | 1 ≤ K ≤ N |
| U_i, V_i | 1 ≤ U_i, V_i ≤ N |
| C_i | 1 ≤ C_i ≤ N |
| Sum of C_i | ≥ N (enough capacity for all vertices) |
| Time limit | 2 seconds |
| Memory limit | 1024 MB |

Sample input:
```
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
```
This has 2 test cases. The first has N=5, K=3, each color can be used twice. The second
has N=3, K=3, each color can be used once.

---

## 1b. Output Format

For each test case, output one line.

**If a valid coloring exists:** Output N integers `X_1 X_2 ... X_N` separated by spaces,
where `X_i` (1 ≤ X_i ≤ K) is the color assigned to vertex i.

For example, `3 2 2 1 1` means:
- Vertex 1 → color 3
- Vertex 2 → color 2
- Vertex 3 → color 2
- Vertex 4 → color 1
- Vertex 5 → color 1

**If no valid coloring exists:** Output just `-1`.

Example output for the sample input:
```
3 2 2 1 1
-1
```

The first test case produced a coloring; the second was impossible.

---

## 2. The Problem (in plain English)

We have a tree (a collection of vertices connected by edges with no cycles). We need to
color each vertex using colors numbered 1 to K. Color `i` can be used at most `C[i]` times.

**The rule:** Pick any edge and cut it. The tree splits into two separate pieces (two
subtrees). There must be at least one color that appears in **both** pieces. This must be
true for **every** edge in the tree.

If such a coloring exists, output it. Otherwise, output `-1`.

---

## 2. Understanding the Condition

### Why leaves are the bottleneck

A **leaf** is a vertex with only one neighbor (a "dead end" of the tree).

Imagine cutting the edge that connects a leaf to the rest of the tree. One piece is just
that single leaf. The other piece is everything else.

For this edge to satisfy the rule, the leaf's color must also appear **somewhere else**
in the tree (on the "everything else" side). This means:

> **Every leaf must share its color with at least one other vertex.**

A color that is used only once can never help — it can't be on both sides of any cut.
Only colors used at least 2 times matter for satisfying the condition.

---

## 3. Key Idea: The Leaf Centroid

We pick a special vertex called the **leaf centroid** (called `X` in the code). It has
this property:

> When we remove `X`, each remaining piece contains **at most half** of all the leaves.

This is useful because it guarantees that no single branch (group of leaves) is too
large — we can always find leaves from different branches to pair together.

### How to find the leaf centroid

1. Count all leaves in the tree (`L`).
2. Root the tree at any non-leaf vertex.
3. For each vertex, compute how many leaves exist in its subtree.
4. A vertex is the leaf centroid if every branch coming out of it has ≤ `L/2` leaves.

---

## 4. Grouping the leaves

Once we have the centroid `X`, we group the leaves by which neighbor of `X` they are
connected through:

```
     X
    /|\
   / | \
  G1 G2 G3   ← each Gi is a group of leaves in that branch
```

Leaves from different groups are in different "directions" from `X`. If a color appears
in two different groups, then for many edges, that color appears on both sides.

---

## 5. The Painting Algorithm

### Step A: Colors with capacity ≥ 2

For each color that can be used at least twice:

1. If there is only 1 unpainted leaf left, paint it and also paint `X` with this same
   color (so the leaf shares its color with `X`).
2. If we have enough capacity to paint all remaining leaves, just paint them all.
3. Otherwise, pick **two leaves from different groups** and paint them with this color.
   This ensures the color spans at least two branches.
4. Use any remaining capacity of this color to paint more leaves (from any groups).

The code uses a **priority queue** (max-heap) to always pick from the group with the
most remaining unpainted leaves. This keeps the groups balanced.

### Step B: Fill remaining vertices

After all leaves are painted, some internal (non-leaf) vertices may still be uncolored.
They just get whatever color capacity is left over.

---

## 6. Why this works

- **Leaf edges are covered:** Every leaf shares its color with either another leaf (from
  a different branch) or the centroid `X`. So the edge connecting the leaf to its parent
  is covered.

- **Internal edges are covered:** If a color appears in two different branches from `X`,
  then any edge in one of those branches has that color on both sides (within the branch
  AND outside it). The centroid property guarantees we can always pair leaves from
  different branches.

- **The centroid guarantee:** Since no branch has more than half the leaves, as long as
  at least 2 leaves remain unpainted, we can always find two leaves from different
  groups to pair up.

---

## 7. Why a solution might be impossible

The algorithm outputs `-1` if either:

- The tree has only 2 vertices and no color can be used at least twice (so the two
  leaves can't share a color).
- After processing all colors with capacity ≥ 2, some leaves remain unpainted. This
  means there aren't enough multi-use colors to cover all the leaves.

---

## 8. Example Walkthrough

Consider the sample:
```
N = 5, K = 3
Edges: 1-2, 1-3, 2-4, 2-5
C = [2, 2, 2]  (each color can be used twice)
```

1. Leaves: vertices 3, 4, 5 (three leaves).
2. Centroid: vertex 1 or 2. Let's say X = 1.
3. Groups: {3} (via neighbor 3), {4, 5} (via neighbor 2).
4. Paint color 1: pick leaf 4 (from group 2) and leaf 3 (from group 1).
5. Paint color 2: remaining leaves = {5}. Paint leaf 5 and X = 1.
6. Paint color 3: remaining vertices.
7. Result: `3 2 2 1 1` — matching the sample output.

---

## 9. Key Code Sections

| Section | Lines | Purpose |
|---------|-------|---------|
| Build adjacency list | 8–15 | Read the tree |
| Special case N=2 | 21–29 | Handle the smallest tree |
| Count leaves | 32–35 | Find `L` |
| Root and DFS | 44–57 | Compute parent, order, and leaf counts |
| Find centroid X | 60–70 | Pick the leaf centroid |
| Group leaves | 72–85 | Group leaves by X's neighbors |
| Paint with max-heap | 93–183 | Greedy color assignment |
| Fill leftovers | 192–204 | Assign remaining colors |

---

## 10. Step-by-Step Implementation Guide

This chapter walks through the code section by section, explaining how to write each
part.

---

### 10.1 Read the tree (adjacency list)

**Technique:** Graph representation — adjacency list.

**Logic:** A tree is a graph where every vertex is connected by edges. To store it, we
use an **adjacency list**: for each vertex, we keep a list of its neighbors. Since edges
are undirected (you can travel both ways), we add each edge to both vertices' lists.
The `u--` converts from 1-based to 0-based indexing because C++ arrays start at 0.

```cpp
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
```

**What's happening:**
- Read N (vertices) and K (colors).
- `adj[u].push_back(v)` means "u is connected to v." We do this both ways since the
  edges are undirected.
- `u--` converts from 1-based indexing (vertex 1 is the first) to 0-based indexing
  (array position 0 is the first). This is a common trick — arrays start at 0 in C++.
- Read the capacity array `C` for each color.

---

### 10.2 Handle N = 2 (special case)

**Technique:** Edge case handling.

**Logic:** When N = 2, both vertices are leaves. Every leaf must share its color with
another vertex. With only two vertices, the only way is for both to have the same color.
We need a color with capacity ≥ 2. If none exists, the problem is impossible.

```cpp
if (N == 2) {
    int col = -1;
    for (int i = 0; i < K; i++) {
        if (C[i] >= 2) { col = i + 1; break; }
    }
    if (col == -1) cout << "-1\n";
    else cout << col << " " << col << "\n";
    return;
}
```

**What's happening:**
- With only 2 vertices, both are leaves. Each must share its color with the other —
  so we need one color that can be used at least twice.
- Pick the first color with C[i] ≥ 2 and give it to both vertices.
- If no such color exists, output -1.

---

### 10.3 Count leaves

**Technique:** Counting / linear scan.

**Logic:** A leaf is a vertex with degree 1, meaning it has exactly one neighbor. We
scan all vertices and count how many have `adj[i].size() == 1`. This total `L` is used
later to find the centroid.

```cpp
int L = 0;
for (int i = 0; i < N; i++) {
    if (adj[i].size() == 1) L++;
}
```

**What's happening:**
- A leaf is a vertex with only one neighbor (`adj[i].size() == 1`).
- Count all leaves and store the total in `L`.

---

### 10.4 Root the tree and run DFS

**Technique:** Post-order DFS (Depth-First Search) / tree DP (Dynamic Programming on
trees).

**Logic:** We need to know, for each vertex, how many leaves exist in its subtree. A
**post-order DFS** processes children first, then the parent. This lets us compute
bottom-up: a leaf contributes 1 to its own count, and an internal vertex sums the
counts of all its children.

**Identifying the Parent:**
In an undirected graph, a vertex $u$ is the **parent** of vertex $v$ if the traversal reached $v$ by following an edge from $u$. We track this in two ways:
1.  **During Traversal:** The DFS function `dfs(v, p)` accepts $p$ as an argument. When exploring neighbors of $v$, we skip $p$ to ensure we only move "down" the tree (away from the root).
2.  **Storage:** We store `parent[v] = p` in an array. This is critical for later steps (like finding the centroid) where we need to know which neighbor of a vertex leads back "up" the tree.

The `order` list stores vertices in the order they finish processing, ensuring parents always appear after all their descendants.

**Purpose of `sub_leaves`:**
This array stores the number of **leaf vertices** (from the original graph) that exist within the subtree of vertex $v$.
-   **Initialization:** If $v$ is a leaf, `sub_leaves[v] = 1`.
-   **Aggregation:** For an internal vertex, `sub_leaves[v]` is the sum of the `sub_leaves` counts of all its children.
-   **Usage:** This count is essential for finding the **centroid** in the next step. It allows us to determine, for any vertex, exactly how many leaves are in its subtree vs. how many are outside of it ($L - \text{sub\_leaves}[v]$).

```cpp
int root = -1;
for (int i = 0; i < N; i++) {
    if (adj[i].size() > 1) { root = i; break; }
}
```

Pick any non-leaf as the root. If we rooted at a leaf, the DFS would be awkward.

```cpp
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
```

**What's happening:**
- This is a **post-order DFS**: we process children first, then the parent.
- `sub_leaves[v]` = number of leaves in v's subtree (including v itself if it's a leaf).
- If v is a leaf, `sub_leaves[v] = 1`.
- If v is an internal node, `sub_leaves[v] = sum of sub_leaves of all children`.
- `order` stores vertices in the order they finish processing (useful for later).

---

### 10.5 Find the leaf centroid X

**Technique:** Leaf centroid (adaptation of tree centroid).

**Logic:** A normal centroid is a vertex whose removal splits the tree into components
of size ≤ N/2. Here we use leaves instead of size — we want a vertex whose removal
splits the leaves into groups of size ≤ L/2. This ensures we can always pair leaves
from different groups. We check candidates using the post-order data: each vertex's
"outside" leaves (total L minus its subtree leaves) and "inside" leaves (each child's
subtree leaves) must all be ≤ L/2.

```cpp
int X = -1;
for (int v : order) {
    if (adj[v].size() == 1) continue; // skip leaves

    bool ok = ((L - sub_leaves[v]) <= L / 2);
    if (!ok) continue;

    for (int u : adj[v]) {
        if (u == parent[v]) continue;
        if (sub_leaves[u] > L / 2) { ok = false; break; }
    }

    if (ok) { X = v; break; }
}
```

The centroid must satisfy two checks:

**Check 1 — the "outside" part:** `L - sub_leaves[v]` counts how many leaves are
outside v's subtree (i.e., in the direction of the root). This represents the "upper" component of the tree if we were to remove $v$. We require this to be $\leq L/2$.

**Check 2 — the "inside" parts:** We iterate through all neighbors $u$ of $v$. 
-   **Why we skip the parent (`u == parent[v]`):** The component in the direction of the parent was already checked in **Check 1**. The stored `sub_leaves[u]` values only track nodes *below* $u$, so they would be incorrect for a parent node. 
-   **Why we check `sub_leaves[u] > L/2`:** For every child branch, the number of leaves must be $\leq L/2$. If any child's subtree contains **more than half** of the total leaves, $v$ is not a valid centroid because that one branch is "too heavy" to be balanced by the others.

If both checks pass, $v$ is a perfect "hub" for pairing leaves.

If both conditions hold, v is the centroid — every branch leaving v has at most
half the leaves.

---

### 10.6 Group leaves by X's neighbors

**Technique:** DFS traversal / tree branching.

**Logic:** We treat X as the "center" of the tree and look at each neighbor branch
separately. For each neighbor of X, we run a DFS to find every leaf reachable through
that neighbor (without crossing back through X). Each branch's leaves become one
group. This way, leaves in the same group are in the same direction from X, and
leaves in different groups are in different directions.

**Why the DFS stops at the Centroid (X):**
When collecting leaves for a specific branch, the DFS is instructed to never move
back toward $X$ (by passing $X$ as the initial parent `p`).
- **Isolation:** This ensures that each group is strictly contained within its own
  subtree. If the DFS were allowed to pass through $X$, it would "bleed" into other
  branches and collect leaves that belong to different groups.
- **Directional Integrity:** By stopping at $X$, we guarantee that all leaves in a
  single group are on the same side of the centroid. This is what allows us to later
  guarantee that picking leaves from *different* groups will force the path to
  cross $X$.
- **Disjoint Sets:** It ensures that every leaf belongs to exactly one group.

**Why this matters:**
To satisfy the problem's condition (every edge must be crossed by at least one color),
we aim to make every color "pass through" the centroid $X$. An edge is "covered"
by a color if that color exists on both sides of the edge.
- If we assign a color to leaves in two **different** groups, the path between
  them **must** pass through $X$. This covers all edges on the paths from those
  leaves to $X$.
- Since $X$ is the leaf centroid, every edge in the tree lies on a path from at
  least one leaf to $X$.
- Therefore, if every leaf is part of a color that spans at least two different
  groups (or one group and $X$), every edge in the tree will be covered.
- Grouping by neighbor allows us to easily pick leaves from different branches.

**Strategic Preview:**
These groups will be used in a **Greedy Pairing** algorithm. By always picking
leaves from the **two largest groups** first, we guarantee that no single branch
ever becomes so large that it runs out of "partner leaves" in other branches to
cross the centroid with.

```cpp
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
```

**What's happening:**
- For each neighbor `start` of X, run a DFS to collect all leaves in that direction.
- Each neighbor's collection becomes one **group** of leaves.
- Groups with no leaves are skipped (not all branches of X contain leaves).

---

### 10.7 Paint leaves with a priority queue

**Technique:** Greedy algorithm with a max-heap (priority queue).

**Detailed Strategy:**
We iterate through each color $i$ with capacity $C_i \ge 2$. Our goal is to make
each color "cross" the centroid $X$ by using leaves from different groups.

1.  **Maintain Balance:** We keep all leaf groups in a **Max-Heap** sorted by their
    number of unpainted leaves.
2.  **Force the Cross:** For each color, we **must** take the first two leaves from the
    **two largest groups** in the heap. This ensures the color spans across $X$ and
    simultaneously reduces the sizes of the most "dangerous" (largest) branches.
3.  **Drain Capacity:** If a color can hold more than 2 vertices, we fill the remaining
    capacity by repeatedly taking leaves from the **single largest** group currently
    available. This further helps keep the tree balanced.
4.  **Special Case - The Last Leaf:** if only one leaf is left unpainted in the whole
    tree, we paint it and the **centroid $X$** with the same color. This ensures the
    last leaf's path to the center is covered even without another leaf partner.
5.  **Special Case - Capacity Overload:** If a color has enough capacity to paint
    **all** remaining unpainted leaves, we do so immediately.

#### 1. Setup

```cpp
vector<int> ptr(G, 0);       // next unpainted leaf index in each group
vector<int> color(N, -1);    // color of each vertex (-1 = unpainted)
int unpainted = L;           // how many leaves are still unpainted

priority_queue<pair<int, int>> pq;
for (int g = 0; g < G; g++) {
    pq.push({(int)groups[g].size(), g});
}
```

*   **`ptr` vector:** A "bookmark" for each group. It tracks which leaf is next to
    be painted in each branch so we don't repeat or search.
*   **`unpainted`:** A global counter. We need this to know when to trigger the
    "Last Leaf" or "Endgame" scenarios.
*   **`priority_queue`:** A Max-Heap that keeps the groups with the most leaves
    at the top. This is the "brain" of our greedy strategy.

#### 1.5 The Main Color Loop

The entire painting process happens inside a loop that goes through each color one by one.

```cpp
for (int i = 0; i < K; i++) {
    if (C[i] < 2) continue; // Skip colors that can't "cross" an edge
    if (unpainted == 0) break; // All leaves are done!

    int rem = C[i]; // How much capacity we have for this color
    
    // ... [Cases 1, 2, and 3 happen inside here] ...
}
```

*   **The Filter:** `if (C[i] < 2) continue;` is crucial. A color with capacity 1 can only be placed on one vertex. It cannot exist on *both* sides of a cut edge, so it is useless for covering leaves. We save these colors for the internal vertices later.
*   **The Exit:** `if (unpainted == 0) break;` stops the complex logic as soon as our primary goal (securing the leaves) is complete.
*   **The Resource:** `rem` tracks the remaining uses of the current color as we hand it out.

#### 2. Helper: paint_leaf

```cpp
auto paint_leaf = [&](int g, int c) {
    int v = groups[g][ptr[g]++];
    color[v] = c;
    unpainted--;
};
```

*   **The Goal:** Perform all bookkeeping for a single painting action.
*   **Mechanics:** It uses the group ID `g` to find the correct bookmark, paints
    the vertex `v`, and decrements the global `unpainted` count. This is $O(1)$.

#### 3. Helper: clean_top

```cpp
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
```

*   **The Goal:** Ensure the heap is accurate before we make a decision.
*   **Audit Logic:** Since we don't update the heap every time a leaf is painted
    (lazy updates), this function clears out empty groups and updates "stale"
    counts until it finds the true largest group.

#### 4. Case 1: The Last Leaf (Emergency Fallback)

```cpp
if (unpainted == 1) {
    for (int g = 0; g < G; g++) {
        if (ptr[g] < (int)groups[g].size()) {
            paint_leaf(g, i + 1);
            break;
        }
    }
    if (color[X] == -1) color[X] = i + 1;
    rem = 0;
    break;
}
```

*   **Logic:** If only one leaf remains, it cannot cross $X$ with another leaf.
    We pair it with the **Centroid $X$** itself to ensure the branch edges are covered.

#### 5. Case 2: Capacity Overload (The Endgame)

```cpp
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
```

*   **Logic:** When one color can finish **all** remaining leaves, we no longer
    need to worry about future balance. We simply drain every group.

#### 6. Case 3: The Cross and Drain (The Midgame)

```cpp
// 1. Force the Cross
auto [cnt1, g1] = clean_top(); pq.pop();
auto [cnt2, g2] = clean_top(); pq.pop();
paint_leaf(g1, i + 1);
paint_leaf(g2, i + 1);
rem -= 2;

// 2. Put them back
if (ptr[g1] < (int)groups[g1].size()) pq.push({cnt1 - 1, g1});
if (ptr[g2] < (int)groups[g2].size()) pq.push({cnt2 - 1, g2});

// 3. Drain remaining capacity
while (rem > 0 && unpainted > 0) {
    auto [cnt, g] = clean_top();
    pq.pop();
    paint_leaf(g, i + 1);
    rem--;
    if (ptr[g] < (int)groups[g].size()) pq.push({cnt - 1, g});
}
```

*   **The Cross:** By taking from the **two largest** groups, we guarantee the
    path passes through the centroid $X$.
*   **The Drain (Active Balancing):**
    -   **The Purpose:** After the first two leaves satisfy the "crossing" requirement,
        any leftover capacity in the current color is a valuable resource for
        **preserving balance**.
    -   **The Strategy:** We repeatedly target the **single largest group** in the
        heap. 
    -   **Why the Largest?** The biggest threat to a valid coloring is one branch
        becoming so large that it contains more leaves than all other branches
        combined. If that happens, future colors will be "trapped" in that branch
        and fail to cross the centroid.
    -   **Result:** This phase aggressively "trims" the heaviest branches,
        ensuring that the tree remains in a state where $Largest \le Others$ for
        the next color in the loop. This is what makes the greedy approach robust.

**Step-by-Step Breakdown:**

1.  **Iterate through Colors ($C_i \ge 2$):** A color with capacity 1 cannot "cross"
    an edge because it can only exist on one side. Therefore, we only use colors
    with $C_i \ge 2$ to cover the edges.

2.  **The "Last Leaf" (Case 1):** If only one leaf remains, it has no partner to
    form a path. We pair it with the **Centroid $X$**. Since $X$ is connected to
    every branch, the path from the last leaf to $X$ will cover all edges in that
    leaf's branch.

3.  **Capacity Overload (Case 2 - The "Endgame"):** This occurs when
    `unpainted <= rem`.
    -   **The Situation:** The current color has enough space to take **every single
        remaining leaf** in the tree.
    -   **The Logic:** Because no more leaves will exist after this color, we no
        longer need to worry about "saving" partners for future colors. We simply
        drain all groups until they are empty. The tree's balance is no longer a
        concern because the leaf-painting phase is effectively over.

4.  **The Greedy Cross (Case 3 - The "Midgame"):** This occurs when
    `unpainted > rem`.
    -   **The Situation:** There are more leaves left than this color can hold. We
        must be highly disciplined because **future colors** will still need
        available "partner leaves" in different branches to satisfy their own
        crossing requirements.
    -   **The Mandatory Pairing:** We **must** pop the **two largest** groups. This
        guarantees the color crosses $X$ and, more importantly, prevents the
        largest groups from pulling away and becoming a majority.
    -   **The Drain Phase:** Any leftover capacity is used to shrink the current
        largest group. This "active balancing" is what keeps the $Largest \le Others$
        invariant true for the next color in the loop.
    -   **The Double Pop:** We take leaves from the **two largest** groups. Because
        these groups are different branches of $X$, the path between them **must**
        cross $X$.
    -   **Update & Push:** After painting, we immediately update the group sizes
        and push them back into the PQ. This keeps our "view" of the heaviest
        branches accurate.
    -   **The Drain Phase:** Once the crossing is guaranteed (after the first 2 leaves),
        we use any remaining capacity (`rem > 0`) to shrink the largest available
        group. This is purely for **balance**—it ensures that for the *next* color,
        the groups are as even as possible.

---

### 10.8 Fill remaining vertices

**Technique:** Two-pointer greedy fill.

**Logic:** After painting all leaves, some internal vertices may still be uncolored.
We count how many times each color has been used, then scan through uncolored vertices
and assign them to the first color that still has capacity. The pointer `ci` always
moves forward (never backward) because once a color is full, earlier colors will stay
full — this makes the scan efficient (O(N) total).

```cpp
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
```

**What's happening:**
- Count how many times each color has been used so far.
- For each unpainted vertex, find a color that still has remaining capacity.
- `ci` scans forward through colors; once a color is full, we move to the next one.
- This fills all internal vertices that were never painted during the leaf phase.

---

### 10.9 Final Output

**Technique:** Standard Output with Fast I/O.

**Logic:** Once the `color` array is fully populated (both leaves and internal vertices), we print the results. If any vertex remains uncolored (value is `-1`), it means the constraints made the coloring impossible, and we output `-1`.

```cpp
// 1. Validation
bool possible = true;
for (int v = 0; v < N; v++) {
    if (color[v] == -1) {
        possible = false;
        break;
    }
}

// 2. Printing
if (!possible) {
    cout << "-1\n";
} else {
    for (int i = 0; i < N; i++) {
        cout << color[i] << (i == N - 1 ? "" : " ");
    }
    cout << "\n";
}
```

**Key Considerations:**
- **Indexing:** The problem uses 1-based indexing for vertices (1 to N), but our array is 0-indexed. The loop correctly outputs `color[0]` to `color[N-1]`.
- **Trailing Spaces:** The ternary operator `(i == N - 1 ? "" : " ")` ensures no space is printed after the final integer, satisfying strict judge requirements.
- **Performance:** 
    - Use `\n` instead of `endl` to avoid unnecessary buffer flushes, which is critical when $N=3 \times 10^5$.
    - Ensure Fast I/O is enabled at the start of `main()`:
      ```cpp
      ios::sync_with_stdio(false);
      cin.tie(NULL);
      ```

---

## 11. Complexity

- **Time:** O(N log N) per test case — sorting/heap operations on the groups.
- **Memory:** O(N) — adjacency list, groups, color array.
