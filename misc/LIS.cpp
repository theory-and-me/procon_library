#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(ll i=0;i<(ll)n;i++)
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define spa << " " <<
#define fi first
#define se second
#define ALL(a)  (a).begin(),(a).end()
#define ALLR(a)  (a).rbegin(),(a).rend()

using ld = long double;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<long, long>;
using pdd = pair<ld, ld>;

template<typename T> struct V : vector<T> { using vector<T>::vector; };
// V() -> V<ll>;
// V(size_t) -> V<ll>;
// template<typename T> V(size_t, T) -> V<T>;
template<typename T> vector<T> make_vec(size_t n, T a) { return vector<T>(n, a); }
template<typename... Ts> auto make_vec(size_t n, Ts... ts) { return vector<decltype(make_vec(ts...))>(n, make_vec(ts...)); }
template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){os << "(" << v.first << ", " << v.second << ")"; return os;}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { for (auto &e : v) os << e << ' '; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<vector<T>> &v){ for(auto &e : v){os << e << "\n";} return os;}
struct fast_ios { fast_ios(){ cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;

template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
void fail() { cout << -1 << '\n'; exit(0); }
inline int popcount(const int x) { return __builtin_popcount(x); }
inline int popcount(const ll x) { return __builtin_popcountll(x); }
template<typename T> void debug(vector<vector<T>>&v,ll h,ll w){for(ll i=0;i<h;i++)
{cerr<<v[i][0];for(ll j=1;j<w;j++)cerr spa v[i][j];cerr<<endl;}};
template<typename T> void debug(vector<T>&v,ll n){if(n!=0)cerr<<v[0];
for(ll i=1;i<n;i++)cerr spa v[i];
cerr<<endl;};

const ll INF = (1ll<<62);
// const ld EPS   = 1e-10;
// const ld PI    = acos(-1.0);
const ll mod = (int)1e9 + 7;
//const ll mod = 998244353;

// verified @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
V<ll> LIS(const V<ll> &X, bool strict, bool increase){
    // res[i] には区間[0, i]におけるLISの長さが入る
    // strict で狭義か否かを指定
    // increase で単調増加か否かを指定
    ll N = X.size();
    V<ll> A(N);
    REP(i, N) A[i] = X[i];
    if(!increase) REP(i, N) A[i] *= -1;
    V<ll> dp(N, INF);
    V<ll> res(N);
    REP(i, N){
        vector<ll>::iterator itr;
        if(strict) itr = lower_bound(ALL(dp), A[i]);
        else itr = upper_bound(ALL(dp), A[i]);
        *itr = A[i];
        ll pos = lower_bound(ALL(dp), INF) - dp.begin();
        res[i] = pos;
    }
    return res;
};

int main(){

    ll n;
    cin >> n;
    V<ll> a(n);
    REP(i, n) cin >> a[i];
    auto l  = LIS(a, true, true);
    cout << l.back() << endl;

    return 0;
}