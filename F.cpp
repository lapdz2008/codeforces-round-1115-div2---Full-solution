#include <bits/stdc++.h>
#define LAPDZ ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define task "none"
#define pb push_back
#define fi first
#define se second
#define reset(x) memset(x, 0, sizeof(x))
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FORD(i,a,b) for(int i = (a); i > (b); i--)
#define REP(i,a,b) for(int i = (a); i <= (b); i++)
#define REPD(i,a,b) for(int i = (a); i >= (b); i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define turn_on(i,m) (m |= (1LL << (i)))
#define turn_off(i,m) (m &= ~(1LL << (i)))
#define bit(x,i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define c_bit(x) __builtin_popcountll(x)
#define el '\n'

using namespace std;

typedef long long ll;
typedef double db;
using u64 = uint64_t;
using u128 = __uint128_t;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const ll MOD = 1000000007;
const ll maxn = 1e6 + 7;
const ll INF = 1e9 + 7;
const int LOG = 19;

ll T[70];

int n;
vector<int> C, K;
vector<vector<int>> adj;
vector<int> tin, tout, depth;
vector<vector<int>> up;
int timer;

void dfs(int v, int p, int d)
{
    tin[v] = ++timer;
    depth[v] = d;
    up[v][0] = p;

    FOR(i, 1, LOG)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u : adj[v])
        if (u != p)
            dfs(u, v, d + 1);

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int get_lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;

    REPD(i, LOG - 1, 0)
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];

    return up[u][0];
}

void solve()
{
    cin >> n;

    C.assign(n + 1, 0);
    K.assign(n + 1, 0);
    adj.assign(n + 1, vector<int>());
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    depth.assign(n + 1, 0);
    up.assign(n + 1, vector<int>(LOG, 1));

    timer = 0;

    vector<vector<int>> colors(n + 1);

    REP(i, 1, n)
    {
        cin >> C[i];
        colors[C[i]].pb(i);
    }

    REP(i, 1, n)
        cin >> K[i];

    FOR(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1, 1, 0);

    vector<ll> ans(n + 1, -1);
    vector<int> cnt(n + 1, 0);

    REP(c, 1, n)
    {
        if (colors[c].empty())
            continue;

        int M_c = colors[c].size();
        int K_c = K[c];

        vector<int> nodes = colors[c];

        sort(all(nodes), [&](int a, int b)
        {
            return tin[a] < tin[b];
        });

        int sz = nodes.size();

        FOR(i, 0, sz - 1)
            nodes.pb(get_lca(nodes[i], nodes[i + 1]));

        sort(all(nodes), [&](int a, int b)
        {
            return tin[a] < tin[b];
        });

        nodes.erase(unique(all(nodes)), nodes.end());

        for (int u : colors[c])
            cnt[u] = 1;

        vector<int> st;
        vector<pair<int, int>> vt_edges;

        for (int u : nodes)
        {
            while (!st.empty() && !is_ancestor(st.back(), u))
                st.pop_back();

            if (!st.empty())
                vt_edges.pb({st.back(), u});

            st.pb(u);
        }

        ll total_dist = 0;
        vector<pair<ll, ll>> edge_weights;

        REPD(i, (int)vt_edges.size() - 1, 0)
        {
            int p = vt_edges[i].fi;
            int u = vt_edges[i].se;

            cnt[p] += cnt[u];

            ll w = min((ll)cnt[u], (ll)M_c - cnt[u]);
            ll L = depth[u] - depth[p];

            total_dist += w * L;
            edge_weights.pb({w, L});
        }

        sort(rall(edge_weights));

        ll saved = 0;
        ll need = K_c - 1;

        for (auto x : edge_weights)
        {
            ll take = min(need, x.se);
            saved += take * x.fi;
            need -= take;

            if (need == 0)
                break;
        }

        ans[c] = total_dist - saved;

        for (int u : nodes)
            cnt[u] = 0;
    }

    REP(i, 1, n)
        cout << ans[i] << (i == n ? '\n' : ' ');
}

signed main()
{
    LAPDZ;

    if (fopen(task ".inp", "r"))
    {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }

    clock_t start, end;
    start = clock();

    ll test = 1;
    cin >> test;

    ll TestCase = 0;

    while (test--)
    {
        TestCase++;
        cerr << "Processing test = " << TestCase << '\n';
        solve();
    }

    end = clock();
    cerr << "Time = " << (double)(end - start) / CLOCKS_PER_SEC << '\n';

    return 0;
}
