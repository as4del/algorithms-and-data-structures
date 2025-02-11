#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5 + 1;
const int mod = 1e9 + 7;

vector<ll> g[N], gr[N], gg[N];
multiset<pair<ll,ll>> st, st1;
vector<ll>visited (N);
ll fup[N], d[N];

pair<ll,ll> edge(ll a, ll b) {
    if (a < b) {
        return make_pair(a, b);
    } else {
        return make_pair(b, a);
    }
}

ll tme = 0;
void dfs1 (ll v, ll p = -1){
    visited[v] = 1;
    d[v] = fup[v] = tme++;

    for (auto u : g[v]) {
        if (u == p) continue;
        if (visited[u]) {
            fup[v] = min(fup[v], d[u]);
        } else {
            dfs1(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[u] > d[v]) {
                st.erase(st.find(edge(v, u)));
                st1.insert(edge(v, u));
            }
        }
    }
}

vector<ll> ans(N);
ll summ = 0;
ll tme1 = -1;
map<ll, ll> mp;
void dfs2 (ll v) {
    summ++;
    visited[v] = 1;
    mp[v] = tme1;
    for (auto u : gr[v]) {
        if (!visited[u]) {
            dfs2(u);
        }
    }
}

ll cnt = 0;
vector<ll>listt;
void dfs3(ll v) {
    visited[v] = 1;
    if (gg[v].size() == 1 || gg[v].empty()) {
        cnt++;
        listt.push_back(v);
    }
    for (int i = 0; i < gg[v].size(); ++i) {
        auto u = gg[v][i];
        if (!visited[u]) {
            dfs3(u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
        st.insert(edge(a, b));
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    for (auto [v, u] : st) {
        gr[v].push_back(u);
        gr[u].push_back(v);
    }

    visited.clear();
    visited.resize(N);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            tme1++;
            summ = 0;
            dfs2(i);
            ans[tme1] = summ;
        }
    }

    for (auto [v, u] : st1) {
        gg[mp[v]].push_back(mp[u]);
        gg[mp[u]].push_back(mp[v]);
    }

    visited.clear();
    visited.resize(N);

    ll kl = 0;
    ll cur = tme1 + 1;
    for (int i = 0; i < cur; ++i) {
        cnt = 0;
        if (!visited[i]) {
            dfs3(i);
            kl += cnt;
        }
    }
    if (tme1 == 0) {
        cout << 1 << ' ';
    } else {
        cout << kl << ' ';
    }
    ll res = 1;
    for (auto i : listt) {
        res = (res * ans[i]) % mod;
    }
    cout << res;
}