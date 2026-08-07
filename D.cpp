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

const ll MOD = 998244353;
const ll maxn = 1e6 + 7;
const ll INF = 1e9 + 7;

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    FOR(i, 0, n) cin >> a[i];

    REPD(i, n - 1, 1) a[i] -= a[i - 1];
    
    ll l = 1;
    while (l < n){
        ll r = l;
        while (r + 1 < n && (a[r + 1] - a[l]) % 2 == 0)
        {
            r++;
        }
        sort(a.begin() + l, a.begin() + r + 1);
        l = r + 1;
    }

    REP(i, 1, n - 1)  a[i] += a[i - 1];
    

    FOR(i, 0, n) cout << a[i] << " ";
    
    cout << el;
}

signed main() {
    LAPDZ;
    if (fopen(task ".inp", "r")) {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }

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