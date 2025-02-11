#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 1;

int n;
int sz[N], tin[N], tout[N], head[N], pr[N];
vector<int> g[N];

void recalc_sizes(int v = 0, int p = -1) {
    pr[v] = p;
    sz[v] = 1;

    for (int &to: g[v])
        if (to == p) swap(to, g[v].back());
    for (auto &u : g[v]) {
        if (p != u) {
            recalc_sizes(u, v);
            sz[v] += sz[u];

            if (sz[u] > sz[g[v][0]]) {
                swap(u, g[v][0]);
            }
        }
    }
}

auto lol = clock();
int tme = 0;
int euler[N];

void euler_tour(int v = 0, int p = -1, int p_start = 0) {
    head[v] = p_start;

    euler[tme] = 0;
    tin[v] = tme++;

    for (int i = 0; i < g[v].size(); ++i) {
        int u = g[v][i];
        if (u != p) {
            if (i == 0) {
                euler_tour(u, v, p_start);
            } else {
                euler_tour(u, v, u);
            }
        }
    }

    tout[v] = tme;
}

int t[4 * N];
int lazy[4 * N];

void build(int v = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) {
        t[v] = euler[tl];
        return;
    }

    int tm = (tl + tr) / 2;

    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);

    t[v] = min(t[v * 2], t[v * 2 + 1]);
}

inline void assign(int v, int val) {
    t[v] = val;
    lazy[v] = val;
}

inline void push(int v, int tl, int tr) {
    if (tl != tr && lazy[v]) {
        assign(v * 2, lazy[v]);
        assign(v * 2 + 1, lazy[v]);

        lazy[v] = 0;
    }
}

void update(int l, int r, int x, int v = 1, int tl = 0, int tr = n - 1) {
    if (l > r) {
        return;
    }
    if (l == tl && r == tr) {
        assign(v, x);
        return;
    }

    push(v, tl, tr);

    int tm = (tl + tr) / 2;

    update(l, min(r, tm), x, v * 2, tl, tm);
    update(max(l, tm + 1), r, x, v * 2 + 1, tm + 1, tr);

    t[v] = min(t[v * 2], t[v * 2 + 1]);
}

int get(int l, int r, int v = 1, int tl = 0, int tr = n - 1) {
    if (l > r) {
        return INT_MAX;
    }
    if (l == tl && r == tr) {
        return t[v];
    }

    push(v, tl, tr);

    int tm = (tl + tr) / 2;

    int l_ans = get(l, min(r, tm), v * 2, tl, tm);
    int r_ans = get(max(l, tm + 1), r, v * 2 + 1, tm + 1, tr);

    return min(l_ans, r_ans);
}

inline void precalc_hld() {
    recalc_sizes();

    euler_tour();

//    build();
}

inline bool acs(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

inline void up(int &v, int &u, int c) {
    while (!acs(head[v], u)) {
        update(tin[head[v]], tin[v], c);
        v = pr[head[v]];
    }
}

inline void update_hld(int v, int u, int c) {
    up(v, u, c);
    up(u, v, c);

    if (!acs(v, u)) {
        swap(v, u);
    }

    update(tin[v], tin[u], c);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> n >> q;

    for (int i = 0; i + 1 < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    precalc_hld();

    while (q--) {

        int tp;
        cin >> tp;

        if (tp == 1) {
            int v, u, c;
            cin >> v >> u >> c;
            --v, --u;

            update_hld(v, u, c);
        } else {
            int v;
            cin >> v;
            --v;

            cout << get(tin[v], tin[v]) << '\n';
        }
    }
}
