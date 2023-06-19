#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

#define REP(i,n) for(ll i=0;i<(ll)n;i++)
#define dump(x)  cerr << "Line " << __LINE__ << ": " <<  #x << " = " << (x) << "\n";
#define spa << " " <<
#define fi first
#define se second
#define ALL(a)  (a).begin(),(a).end()
#define ALLR(a)  (a).rbegin(),(a).rend()

using ld = long double;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;

template<typename T> using V = vector<T>;
template<typename T> using P = pair<T, T>;
template<typename T> vector<T> make_vec(size_t n, T a) { return vector<T>(n, a); }
template<typename... Ts> auto make_vec(size_t n, Ts... ts) { return vector<decltype(make_vec(ts...))>(n, make_vec(ts...)); }
template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){os << "(" << v.first << ", " << v.second << ")"; return os;}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { for (auto &e : v) os << e << ' '; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<vector<T>> &v){ for(auto &e : v){os << e << "\n";} return os;}
struct fast_ios { fast_ios(){ cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; } fast_ios_;

template <class T> void UNIQUE(vector<T> &x) {sort(ALL(x));x.erase(unique(ALL(x)), x.end());}
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
void fail() { cout << -1 << '\n'; exit(0); }
inline int popcount(const int x) { return __builtin_popcount(x); }
inline int popcount(const ll x) { return __builtin_popcountll(x); }
template<typename T> void debug(vector<vector<T>>&v,ll h,ll w){for(ll i=0;i<h;i++)
{cerr<<v[i][0];for(ll j=1;j<w;j++)cerr spa v[i][j];cerr<<"\n";}};
template<typename T> void debug(vector<T>&v,ll n){if(n!=0)cerr<<v[0];
for(ll i=1;i<n;i++)cerr spa v[i];
cerr<<"\n";};

const ll INF = (1ll<<62);
// const ld EPS   = 1e-10;
// const ld PI    = acos(-1.0);
const ll mod = (int)1e9 + 7;
//const ll mod = 998244353;

// Lorent さんの swag https://yukicoder.me/submissions/597464

ll op(ll x, ll y){
    return max(x, y);
}

ll e(){
    return -INF;
}

template<class S, S (*op)(S, S), S (*e)()> struct swag {
    std::stack<std::pair<S, S>> front_stack, back_stack;
    swag() {
        front_stack.emplace(e(), e());
        back_stack.emplace(e(), e());
    }
    bool empty() const { return front_stack.size() == 1 && back_stack.size() == 1; }
    size_t size() const { return front_stack.size() + back_stack.size() - 2; }
    S fold() const { return op(front_stack.top().second, back_stack.top().second); }
    void push(const S& x) { back_stack.emplace(x, op(back_stack.top().second, x)); }
    void pop() {
        assert(front_stack.size() > 1 || back_stack.size() > 1);
        if (front_stack.size() > 1) {
            front_stack.pop();
        } else {
            while (back_stack.size() > 2) {
                front_stack.emplace(back_stack.top().first, op(front_stack.top().second, back_stack.top().first));
                back_stack.pop();
            }
            back_stack.pop();
        }
    }
};

// verified @ https://atcoder.jp/contests/typical90/tasks/typical90_ak
int main(){

    ll W, N;
    cin >> W >> N;

    vector<ll> L(N), R(N), V(N);
    REP(i, N) cin >> L[i] >> R[i] >> V[i];

    vector<ll> dp(W+1, -INF);
    dp[0] = 0;

    REP(i, N){
        swag<ll, op, e> qu;
        vector<ll> td(W+1, -INF);
        REP(j, W+1){
            if(j>=L[i]) qu.push(dp[j-L[i]]);
            ll ma = (qu.empty() ? -INF : qu.fold());
            chmax(td[j], dp[j]);
            chmax(td[j], ma+V[i]);
            if(j>=R[i]) qu.pop();
        }
        // cout << td << endl;
        swap(dp, td);
    }

    cout << (dp[W] < -INF/2 ? -1 : dp[W]) << "\n";

    return 0;
}