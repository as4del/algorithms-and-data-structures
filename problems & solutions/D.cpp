#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 3e5 + 1;
const int L = 20;
vector<ll> g[N];
ll binup[L][N];
ll tin[N], tout[N];
ll tme = 0;


void precalc(ll v = 0, ll p = 0) {
    tin[v] = tme++;

    binup[0][v] = p;

    for (int l = 1; l < L; ++l) {
        binup[l][v] = binup[l - 1][binup[l - 1][v]];
    }

    for (auto u : g[v]) {
        if (u != p) {
            precalc(u, v);
        }
    }
    tout[v] = tme;
}

bool acs(ll v, ll u) {
    if (tin[v] <= tin[u] && tout[v] >= tout[u]) {
        return 1;
    } else {
        return 0;
    }
}

ll lca (ll v, ll u) {
    for (int l = L - 1; l >= 0; --l) {
        if (!acs(binup[l][v], u)) {
            v = binup[l][v];
        }
    }
    return binup[0][v];
}

ll dist(ll v, ll u) {
    ll rast = 0;

    for (int l = L - 1; l >= 0; --l) {
        if (!acs(binup[l][v], u)) {
            rast += (1 << l);
            v = binup[l][v];
        }
    }
    rast++;
    return rast;
}

ll dist_all (ll v, ll rast) {
    for (int l = L - 1; l >= 0; --l) {
        if (rast - (1 << l) >= 0) {
            v = binup[l][v];
            rast -= (1 << l);
        }
        if (rast == 0) {
            break;
        }
    }
    return v;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    precalc();
    ll q;
    cin >> q;
    while (q--) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        if (a == b) {
            cout << a + 1 << '\n';
        }
        else if (acs(a,b)) {
            ll distation = dist(b, a);
            if (c - distation >= 0) {
                cout << b + 1 << '\n';
            } else {
                ll cur = distation - c;
                cout << dist_all(b, cur) + 1 << '\n';
            }
        }
        else if (acs(b,a)) {
            ll distation = dist(a, b);
            if (c - distation >= 0) {
                cout << b + 1 << '\n';
            } else {
                cout << dist_all(a, c) + 1 << '\n';
            }
        } else {
            ll lowest = lca(a, b);
            ll dista = dist(a, lowest);
            ll distb = dist(b, lowest);
            if (dista + distb <= c) {
                cout << b + 1 << '\n';
            } else {
                if (c <= dista) {
                    cout << dist_all(a, c) + 1 << '\n';
                } else {
                    ll cur = c - dista;
                    cur = distb - cur;
                    cout << dist_all(b, cur) + 1 << '\n';
                }
            }
        }
    }
}