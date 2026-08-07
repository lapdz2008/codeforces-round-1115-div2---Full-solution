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
    ll n; cin >> n;
    string s; cin >> s;
    ll xoa0 = 0;
    ll xoa1 = 0;
    ll cnt = 0;

    ll i = 0;

    while (i < n) {
        ll j = i;

        while (j < n && s[j] == s[i]) {
            j++;
        }

        ll sz = j - i;

        if (s[i] == '0') xoa0 += sz - 1;
        else xoa1 += sz - 1;
        

        cnt++;
        i = j;
    }

    ll hieu = abs(xoa0 - xoa1);
    ll ans;

    if (hieu <= 1)  ans = n - cnt;
    else{
        char c;
        if (xoa0 > xoa1) c = '1';
        else c = '0';
        

        ll can = hieu - 1;
        ll d = 0;

        if (s[0] == c) d++;
        

        if (s[n - 1] == c) d++;
        

        if (can > d) ans = -1;
        else ans = (n - cnt) + can;
        
    }

    cout << ans << el;
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