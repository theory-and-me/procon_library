#include <bits/stdc++.h>
using namespace std;

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

using Graph = vector<vector<int>>;

tuple<vector<int>, vector<pii>> lowlink(const Graph &G){

    int N = G.size();
    vector<int> ord(N, -1), low(N, -1);
    vector<int> aps;
    vector<pii> bridges;
    int cnt = 0;

    auto dfs = [&](auto self, int v, int par) -> void{
        ord[v] = cnt;
        low[v] = cnt;
        cnt++;
        bool is_aps = false;
        int num_of_child = 0;
        for(auto u: G[v]){
            if(ord[u] == -1){
                num_of_child++;
                self(self, u, v);
                chmin(low[v], low[u]);
                if(par != -1 and ord[v] <= low[u]) is_aps = true;
                if(ord[v] < low[u]) bridges.emplace_back(min(u, v), max(u, v));
            }else if(u != par){
                low[v] = min(low[v], ord[u]);
            }
        }
        if(par == -1 and num_of_child >= 2) is_aps = true;
        if(is_aps) aps.push_back(v);
        return;
    };

    dfs(dfs, 0, -1);

    sort(ALL(aps));
    sort(ALL(bridges));

    return {aps, bridges};
}

int main(){

    int N, M;
    cin >> N >> M;
    vector<int> s(M), t(M);
    REP(i, M) cin >> s[i] >> t[i];

    Graph G(N);
    REP(i, M){
        G[s[i]].push_back(t[i]);
        G[t[i]].push_back(s[i]);
    }

    auto [aps, bridges] = lowlink(G);

    // articulation points
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
    // for(auto v: aps) cout << v << "\n";

    // bridge
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja
    for(auto [u, v]: bridges) cout << u spa v << "\n";
    return 0;
}