#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e4 + 1;
vector<pair<ll,ll>> g[N];
ll k;
const int K = 100 + 1;
ll x;
ll dp[N][K][2];
ll out = 1e18;


void precalc(ll v, ll p = -1) {
    dp[v][1][1] = 0;
    dp[v][1][0] = 0;
    for (ll j = 2; j <= k; ++j) {
        dp[v][j][0] = INT_MAX;
        dp[v][j][1] = INT_MAX;
    }
    for (auto [u, w] : g[v]) {
        if (u != p) {
            precalc(u, v);
        }
    }
}

void sol(ll v, ll p = -1) {
    for (auto [u, w] : g[v]) {
        if (u != p) {
            sol(u, v);
        }
    }
    vector<pair<ll,ll>> chl;
    for (auto [u, w] : g[v]) {
        if (u != p) {
            chl.push_back({u, w});
        }
    }
    if (chl.size() == 2) {
        for (ll i = 3; i <= k; ++i) {
            for (ll l = 1; l < i - 1; ++l) {
                dp[v][i][1] = min(dp[v][i][1],
                                  dp[chl[0].first][l][1] + dp[chl[1].first][i - l - 1][1] + (
                                      chl[0].second + chl[1].second) * 2);
                dp[v][i][0] = min(dp[v][i][0],
                                  dp[chl[0].first][l][1] + dp[chl[1].first][i - l - 1][0] + chl[0].second * 2 + chl[1].
                                  second);
                dp[v][i][0] = min(dp[v][i][0], dp[chl[0].first][l][0] + dp[chl[1].first][i - l - 1][1] + chl[1].
                                  second * 2 + chl[0].second);
            }
        }
        for (ll i = 2; i <= k; ++i) {
            dp[v][i][1] = min(dp[v][i][1], dp[chl[0].first][i - 1][1] + 2 * chl[0].second);
            dp[v][i][1] = min(dp[v][i][1], dp[chl[1].first][i - 1][1] + 2 * chl[1].second);
            dp[v][i][0] = min(dp[v][i][0], dp[chl[0].first][i - 1][0] + chl[0].second);
            dp[v][i][0] = min(dp[v][i][0], dp[chl[1].first][i - 1][0] + chl[1].second);
        }

    }
    else if (chl.size() == 1) {
        for (ll i = 2; i <= k; ++i) {
            dp[v][i][1] = min(dp[v][i][1], dp[chl[0].first][i - 1][1] + 2 * chl[0].second);
            dp[v][i][0] = min(dp[v][i][0], dp[chl[0].first][i - 1][0] + chl[0].second);
        }
    }
}

struct jin {
    ll u, w;
};


void output(ll v) {
    vector<jin> a;
    for (auto [u, w] : g[v]) {
        a.push_back({u, w});
    }

        ll i = k;
        for (ll l = 1; l < i - 2; ++l) {
            for (ll j = 1; j <= i - 2 - l; ++j) {
                dp[v][k][0] = min(dp[v][k][0], dp[a[0].u][l][1] + dp[a[1].u][j][1] + dp[a[2].u][i - l - j - 1][0] + (a[0].w + a[1].w) * 2 + a[2].w);
                dp[v][k][0] = min(dp[v][k][0], dp[a[0].u][l][0] + dp[a[1].u][j][1] + dp[a[2].u][i - l - j - 1][1] + (a[1].w + a[2].w) * 2 + a[0].w);
                dp[v][k][0] = min(dp[v][k][0], dp[a[0].u][l][1] + dp[a[1].u][j][0] + dp[a[2].u][i - l - j - 1][1] + (a[0].w + a[2].w) * 2 + a[1].w);
            }
        }

    for (ll i = 3; i <= k; ++i) {
        for (ll l = 1; l < i - 1; ++l) {
            dp[v][i][0] = min(dp[v][i][0],
                              dp[a[0].u][l][1] + dp[a[1].u][i - l - 1][0] + a[0].w * 2 + a[1].
                              w);
            dp[v][i][0] = min(dp[v][i][0], dp[a[0].u][l][0] + dp[a[1].u][i - l - 1][1] + a[1].
                              w * 2 + a[0].w);
        }
    }
    for (ll i = 2; i <= k; ++i) {
        dp[v][i][0] = min(dp[v][i][0], dp[a[0].u][i - 1][0] + a[0].w);
        dp[v][i][0] = min(dp[v][i][0], dp[a[1].u][i - 1][0] + a[1].w);
    }

    for (ll i = 3; i <= k; ++i) {
        for (ll l = 1; l < i - 1; ++l) {
            dp[v][i][0] = min(dp[v][i][0],
                              dp[a[0].u][l][1] + dp[a[2].u][i - l - 1][0] + a[0].w * 2 + a[2].
                              w);
            dp[v][i][0] = min(dp[v][i][0], dp[a[0].u][l][0] + dp[a[2].u][i - l - 1][1] + a[2].
                              w * 2 + a[0].w);
        }
    }
    for (ll i = 2; i <= k; ++i) {
        dp[v][i][0] = min(dp[v][i][0], dp[a[0].u][i - 1][0] + a[0].w);
        dp[v][i][0] = min(dp[v][i][0], dp[a[2].u][i - 1][0] + a[2].w);
    }

    for (ll i = 3; i <= k; ++i) {
        for (ll l = 1; l < i - 1; ++l) {
            dp[v][i][0] = min(dp[v][i][0],
                              dp[a[1].u][l][1] + dp[a[2].u][i - l - 1][0] + a[1].w * 2 + a[2].
                              w);
            dp[v][i][0] = min(dp[v][i][0], dp[a[1].u][l][0] + dp[a[2].u][i - l - 1][1] + a[2].
                              w * 2 + a[1].w);
        }
    }

}


void solve() {
    precalc(x);
    sol(x);
    if (g[x].size() == 1 || g[x].size() == 2) {
        cout << dp[x][k][0];
    } else {
        output(x);
        cout << dp[x][k][0];
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n >> k >> x;
    x--;


    for (ll i = 0; i < n - 1; i++) {
        ll f, s, weight;
        cin >> f >> s >> weight;
        f--, s--;
        g[f].push_back({s, weight});
        g[s].push_back({f, weight});
    }

    solve();

}