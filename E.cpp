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

ll T[70];

void solve()
{
    u64 n; cin >> n;
    int L = 64 - __builtin_clzll(n);
    ll ans = 0;
    for (int h = 0; h <= L - 3; h++) ans = (ans + T[h]) % MOD;
    int h = L - 2;
    if (h >= 0) {
        bool ok = (n >> h) & 1ULL;
        if (ok) {
            vector<int> d(h);

            for (int k = 0; k < h; k++)
                d[k] = (int)((n >> (h - 1 - k)) & 1ULL);

            vector<ll> dp0(h + 1), dp1(h + 1);

            dp0[h] = 1;
            dp1[h] = 1;

            for (int pos = h - 1; pos >= 0; pos--) {
                ll v0 = dp0[pos + 1];

                if (pos + 2 <= h) v0 = (v0 + 2LL * dp0[pos + 2]) % MOD;

                dp0[pos] = v0 % MOD;
                ll total;
                if (d[pos] == 0) total = dp1[pos + 1];
                else total = dp0[pos + 1];

                if (pos + 2 <= h) {
                    int nval = 2 * d[pos] + d[pos + 1];
                    if (1 < nval)total = (total + dp0[pos + 2]) % MOD;
                    else if (1 == nval)total = (total + dp1[pos + 2]) % MOD;
                    if (3 < nval)total = (total + dp0[pos + 2]) % MOD;
                    else if (3 == nval)total = (total + dp1[pos + 2]) % MOD;
                }

                dp1[pos] = total % MOD;
            }

            ans = (ans + dp1[0]) % MOD;
        }
    }

    cout << ans << el;
}

signed main() {
    LAPDZ;
    if (fopen(task ".inp", "r")) {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }

    T[0] = 1;
    T[1] = 1;

    for (int i = 2; i < 70; i++) T[i] = (T[i - 1] + 2LL * T[i - 2]) % MOD;

    clock_t start, end;
    start = clock();

    ll test = 1;
    cin >> test;

    ll TestCase = 0;

    while (test--) {
        TestCase++;
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        solve();
        // if (test) cout << '\n';
    }

    end = clock();
    cerr << "Time = " << (double)(end - start) / CLOCKS_PER_SEC << '\n';

    return 0;
}