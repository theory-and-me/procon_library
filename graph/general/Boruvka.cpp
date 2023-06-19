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

template<typename T>
struct edge{
    int u, v;
    T weight;
};

template<typename T>
T Boruvka(vector<edge<T>> &E, int N){
    int M = E.size();
    vector<bool> used(M, false);


    while(true){

        vector<vector<int>> G(N);
        for(int i=0;i<M;i++){
            if(used[i]){
                auto &e = E[i];
                G[e.u].push_back(e.v);
                G[e.v].push_back(e.u);
            }
        }

        // DFS で連結成分を求める
        vector<int> component(N, -1);
        auto dfs = [&](auto self, int now, int par, int component_id)->void{
            if(component[now] != -1) return;
            component[now] = component_id;
            for(auto next: G[now]){
                if(next == par) continue;
                self(self, next, now, component_id);
            }
            return;
        };
        REP(i, N) dfs(dfs, i, -1, i);

        // 各連結成分から出る最小の辺を記録
        bool connected = true; // 連結成分が1つかどうか判定
        const auto INF_T = numeric_limits< T >::max();
        vector<T> component_min(N, INF_T);
        vector<int> component_min_edge_id(N, -1);
        for(int i=0;i<M;i++){
            auto &e = E[i];
            int c_u = component[e.u], c_v = component[e.v];
            if(c_u != c_v){
                connected = false;
                if(chmin(component_min[c_u], e.weight)){
                    component_min_edge_id[c_u] = i;
                }
                if(chmin(component_min[c_v], e.weight)){
                    component_min_edge_id[c_v] = i;
                }
            }
        }

        if(connected) break; // 連結成分が一つなら終了

        // 追加
        for(int i=0;i<N;i++){
            if(component_min_edge_id[i] != -1) used[component_min_edge_id[i]] = true;
        }
    }

    T res = 0;
    for(int i=0;i<M;i++) if(used[i]) res += E[i].weight;
    
    return res;
}

// verified @ https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

int main(){

    ll N, M;
    cin >> N >> M;
    V<ll> s(M), t(M), w(M);
    REP(i, M) cin >> s[i] >> t[i] >> w[i];

    V<edge<ll>> E;
    REP(i, M) E.push_back(edge<ll>{(int)s[i], (int)t[i], w[i]});

    ll res = Boruvka(E, N);

    cout << res << endl;

    return 0;
}