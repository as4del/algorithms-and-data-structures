#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 2e5 + 1;
vector<ll> g[N], gr[N], gg[N];
ll d[N], fup[N];
vector<ll> visited (N);
multiset<pair<ll,ll>> r;
set<pair<ll, ll>> kr,most;
map <ll, ll> mp;

pair<ll,ll> edge(ll a, ll b) {
    if (a < b) {
        return make_pair(a, b);
    } else {
        return make_pair(b, a);
    }
}

ll tme = 0;
void dfs (ll v, ll p = -1) {
    visited[v] = 1;
    d[v] = fup[v] = tme++;

    for (auto u : g[v]) {
        if (u == p) continue;
        if (visited[u]) {
            fup[v] = min(fup[v], d[u]);
        } else {
            dfs(u, v);
            fup[v] = min(fup[u], fup[v]);
            if (fup[u] > d[v]) {
                if (kr.find(edge(u, v)) == kr.end()) {
                    most.insert(edge(v, u));
                    r.erase(r.find(edge(v, u)));
                }
            }
        }
    }
}

ll tme1 = -1;
void dfs2(ll v) {
    visited[v] = 1;
    mp[v] = tme1;

    for (auto u : gr[v]) {
        if (!visited[u]) {
            dfs2(u);
        }
    }

}


void dp1 (ll v, pair<ll,ll> &ans, ll p = -1, ll dist = 0) {
    visited[v] = 1;
    if (dist > ans.first) {
        ans = {dist, v};
    }

    for (auto u : gg[v]) {
        if (u != p) {
            dp1(u, ans, v, dist + 1);
        }
    }
}

void dp2 (ll v, pair<ll,ll> &ans, ll p = -1, ll dist = 0) {
    if (dist > ans.first) {
        ans = {dist, v};
    }

    for (auto u : gg[v]) {
        if (u != p) {
            dp2(u, ans, v, dist + 1);
        }
    }
}

ll diametr (ll v) {
    pair<ll,ll> ans = {-1, -1};
    dp1(v, ans);
    pair<ll,ll> ans2 = {-1, -1};
    dp2(ans.second, ans2);

    return ans2.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        if (a == b) {
            continue;
        }
        a--, b--;
        if (r.find(edge(a, b)) != r.end()) {
            kr.insert(edge(a, b));
        }
        g[a].push_back(b);
        g[b].push_back(a);
        r.insert(edge(a, b));
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    for (auto [v, u] : r) {
        gr[v].push_back(u);
        gr[u].push_back(v);
    }

    visited.clear();
    visited.resize(N);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            tme1++;
            dfs2(i);
        }
    }

    for (auto [v, u] : most) {
        gg[mp[v]].push_back(mp[u]);
        gg[mp[u]].push_back(mp[v]);
    }

    visited.clear();
    visited.resize(N);

    ll cur = tme1 + 1;
    ll maxx = 0;
    for (int i = 0; i < cur; ++i) {
        if (!visited[i]) {
            ll dm = diametr(i);
            maxx = max(maxx, dm);
        }
    }

    cout << most.size() - maxx;
}