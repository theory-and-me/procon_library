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

using Graph = V<V<int>>;

vector<int> connected_component_on_complement_graph(Graph &G){
    int n = G.size();
    vector<int> connected_component(n, -1);

    auto bfs_on_complement_graph = [&](int s){
        queue<int> Q;
        Q.push(s);
        unordered_set<int> S;
        for(int i=0;i<n;i++) if(i != s) S.insert(i);

        while(!Q.empty()){
            int v = Q.front();Q.pop();
            connected_component[v] = s;
            unordered_set<int> L;
            for(auto u: G[v]){
                auto itr = S.find(u);
                if(itr != S.end()){
                    S.erase(itr);
                    L.insert(u);
                }
            }
            for(auto u: S){
                Q.push(u);
            }
            swap(S, L);
        }   
        return;
    };

    for(int i=0;i<n;i++){
        if(connected_component[i] == -1){
            bfs_on_complement_graph(i);
        }
    }

    return connected_component;
}

// verified @ https://codeforces.com/contest/1242/problem/B
int main(){

    ll n, m;
    cin >> n >> m;
    
    Graph G(n);
    REP(i, m){
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    auto comp = connected_component_on_complement_graph(G);

    set<int> st;
    for(auto x: comp) st.insert(x);

    cout << (ll)st.size() - 1 << endl;

    return 0;
}