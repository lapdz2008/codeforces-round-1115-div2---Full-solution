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

vector<ll> bitTong, bitDem;
ll sz;

void updateTong(ll id, ll val) {
    while (id <= sz) {
        bitTong[id] += val;
        id += id & (-id);
    }
}

void updateDem(ll id, ll val) {
    while (id <= sz) {
        bitDem[id] += val;
        id += id & (-id);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> can(n + 1);
    REP(i, 1, n) cin >> can[i];

    vector<ll> a(n * m);
    FOR(i, 0, n * m) cin >> a[i];

    vector<ll> nen = a;
    sort(all(nen));
    nen.erase(unique(all(nen)), nen.end());
    sz = nen.size();
    bitTong.assign(sz + 1, 0);
    bitDem.assign(sz + 1, 0);
    ll tong = 0;
    ll ans = m;
    REPD(i, n, 1) {
        ll hang = 0;
        ll dau = (i - 1) * m;

        FOR(j, 0, m) {
            ll x = a[dau + j];

            ll id = lower_bound(all(nen), x) - nen.begin() + 1;
            ll pos = sz - id + 1;

            updateTong(pos, x);
            updateDem(pos, 1);

            hang += x;
        }
        tong += hang;
        if (tong < can[i]) continue;

        ll p = 0;
        ll lay = 0;
        ll dem = 0;

        REPD(b, 20, 0) {
            ll nxt = p + (1LL << b);
            if (nxt <= sz && lay + bitTong[nxt] < can[i]) {
                p = nxt;
                lay += bitTong[nxt];
                dem += bitDem[nxt];
            }
        }

        ll thieu = can[i] - lay;
        ll gt = nen[sz - (p + 1)];
        ll them = (thieu + gt - 1) / gt;
        ans = min(ans, dem + them);
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