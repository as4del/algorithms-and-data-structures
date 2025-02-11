#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5 + 1;
const int L = 20;
int deep[N], tin[N], tout[N], heigh[N];
vector<ll> g[N];
ll binup [L][N];
ll timer = 0;

void precalc (ll v = 0, ll p = 0, ll d = 0) {
    tin[v] = timer++;
    deep[v] = d;

    binup[0][v] = p;

    for (int l = 1; l < L; ++l) {
        binup[l][v] = binup[l - 1][binup[l - 1][v]];
    }

    for (auto w : g[v])  {
        if (w != p) {
            precalc(w, v, d + 1);
        }
    }

    tout[v] = timer++;
}

bool acs(ll v, ll u) {
    if (tin[v] <= tin[u] && tout[v] >= tout[u]) {
        return 1;
    } else {
        return 0;
    }
}

ll lca (ll v, ll u) {
    if (acs(v, u)) {
        return v;
    }
    if (acs(u ,v)) {
        return u;
    }

    for (int l = L - 1; l >= 0; --l) {
        if (!acs(binup[l][v], u)) {
            v = binup[l][v];
        }
    }
    return binup[0][v];
}

ll dist (ll v, ll u) {
    if (acs(v, u)) {
        ll summ = 0;
        for (int l = L - 1; l >= 0; --l) {
            if (!acs(binup[l][u], v)) {
                summ += (1 << l);
                u = binup[l][u];
            }
        }
        summ++;
        return summ;
    }
    if (acs(u, v)) {
        ll summ = 0;
        for (int l = L - 1; l >= 0; --l) {
            if (!acs(binup[l][v], u)) {
                summ += (1 << l);
                v = binup[l][v];
            }
        }
        summ++;
        return summ;
    }
    ll summ1 = 0;
    ll summ2 = 0;
    for (int l = L - 1; l >= 0; --l) {
        if (!acs(binup[l][v], u)) {
            summ1 += (1 << l);
            v = binup[l][v];
        }
    }
    summ1++;
    for (int l = L - 1; l >= 0; --l) {
        if (!acs(binup[l][u], v)) {
            summ2 += (1 << l);
            u = binup[l][u];
        }
    }
    summ2++;
    return summ1 + summ2;
}

void dfs (ll v = 0, ll p = -1) {
    heigh[v] = 1;
    for (auto w : g[v]) {
        if (w != p) {
            dfs(w, v);
            heigh[v] += heigh[w];
        }
    }
}

ll pred (ll v, ll u) {
    for (int l = L - 1; l >= 0; --l) {
        if (!acs(binup[l][v], u)) {
            v = binup[l][v];
        }
    }
    return v;
}
ll zapr (ll v, ll dist) {
    for (int l = L - 1; l >= 0; --l) {
        if (dist == 0) {
            break;
        }
        if (1 << l <= dist) {
            v = binup[l][v];
            dist -= (1 << l);
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
    dfs();
    ll q;
    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        if (a == b) {
            cout << n << '\n';
            continue;
        }
        ll distance = dist (a, b);
        if (distance % 2 != 0) {
            cout << 0 << '\n';
            continue;
        }
        ll lowest = lca(a ,b);
        if (dist (a, lowest) == dist (b, lowest)) {
            ll ans = n - heigh[pred(a, lowest)] - heigh[pred(b, lowest)];
            cout << ans << '\n';
            continue;
        }
        if (deep[a] < deep[b]) {
            swap(a, b);
        }
        ll disttocenter = distance / 2;
        ll otvet = heigh[zapr(a, disttocenter)] - heigh[zapr(a, disttocenter - 1)];
        cout << otvet << '\n';
    }
}
