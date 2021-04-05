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

// ここから
template<typename T>
struct edge{
    int to;
    T weight;
    edge(int to, T weight): to(to), weight(weight) {}
};
template<typename T> using Graph = vector<vector<edge<T>>>;
template<typename T> 
tuple<T, vector<int>> tree_diameter(Graph<T> &G){

    T diameter = 0;
    V<int> vertices;

    int N = G.size();

    auto dfs = [&](auto self, int now, int par, T d, vector<T> &dist, vector<int> &prev) -> void{
        dist[now] = d;
        prev[now] = par;
        for(auto &edge: G[now]){
            if(edge.to != par){
                self(self, edge.to, now, d + edge.weight, dist, prev);
            }
        }
        return;
    };

    vector<T> dist1(N);
    vector<int> prev1(N);
    dfs(dfs, 0, -1, 0, dist1, prev1);
    int v = -1;
    T ma = -numeric_limits<T>::max();
    REP(i, N) if(chmax(ma, dist1[i])) v = i;

    vector<T> dist2(N);
    vector<int> prev2(N);
    dfs(dfs, v, -1, 0, dist2, prev2);
    int u = -1;
    ma = -numeric_limits<T>::max();
    REP(i, N) if(chmax(ma, dist2[i])) u = i;

    diameter = ma;

    ll now = u;
    while(now != -1){
        vertices.push_back(now);
        now = prev2[now];
    }
    return {diameter, vertices};
}
// ここまで

// verified @ https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
int main(){

    ll n;
    cin >> n;
    Graph<ll> G(n);
    map<pll, ll> mp;
    REP(i, n-1){
        ll s, t, w;
        cin >> s >> t >> w;
        G[s].emplace_back(t, w);
        G[t].emplace_back(s, w);
        if(s > t) swap(s, t);
        mp[pll{s, t}] = w;
    }

    auto [diameter, vertices] = tree_diameter(G);

    // cout << diameter << endl; // verify diameter

    // verify vertices
    ll res = 0;
    REP(i, (int)vertices.size()-1){
        ll x = vertices[i];
        ll y = vertices[i+1];
        if(x > y) swap(x, y);
        res += mp[pll{x, y}];
    }
     cout << res << endl;

    return 0;
}