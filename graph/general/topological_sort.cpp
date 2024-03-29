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

// トポロジカルソート
// （DAGかどうか，DAGならばトポロジカル順序）のタプルを返す
// 1->2->0 みたいなグラフなら [1, 2, 0] を返す，[2, 0, 1] ではないことに注意
using Graph = vector<vector<int>>;
tuple<bool, vector<int>> topologicalSort(Graph &G){
    int n = G.size();
    vector<int> in_deg(n, 0);
    queue<int> qu;
    
    REP(i, n){
        for(auto nx: G[i]){
            in_deg[nx]++;
        }
    }
    REP(i, n) if(!in_deg[i]) qu.push(i);

    vector<int> topological_order;
    int cnt = 0;
    while(!qu.empty()){
        int u = qu.front();qu.pop();
        topological_order.push_back(u);
        cnt++;
        for(auto v: G[u]){
            in_deg[v]--;
            if(!in_deg[v]) qu.push(v);
        }
    }

    bool is_dag = (cnt == n);
    return {is_dag, topological_order};
}

int main(){

	// // verified @ https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B
	// ll n, m;
	// cin >> n >> m;
	// Graph G(n);
	// REP(i, m){
	// 	ll s, t;
	// 	cin >> s >> t;
	// 	G[s].push_back(t);
	// }

	// auto[is_dag, ts] = topologicalSort(G);
	// for(auto v: ts) cout << v << "\n";

	// verified @ https://atcoder.jp/contests/abc139/tasks/abc139_e

	ll N;
	cin >> N;
	vector<vector<ll>> A(N);
	REP(i, N){
		REP(j, N-1){
			ll tmp;
			cin >> tmp;
			tmp--;
			A[i].push_back(tmp);
		}
	}

	Graph G(N*N);
	REP(i, N){
		REP(j, N-2){
			int x1 = i, y1 = A[i][j];
			int x2 = i, y2 = A[i][j+1];
			if(x1 > y1) swap(x1, y1);
			if(x2 > y2) swap(x2, y2);
			G[x1 * N + y1].push_back(x2 * N + y2);
		}
	}

	auto [is_dag, ts] = topologicalSort(G);
	if(!is_dag){
		cout << -1 << endl;
		return 0;
	}

	ll ma = 0;
	V<ll> dp(N*N, 0);
	for(auto u: ts){
		for(auto v: G[u]){
			chmax(dp[v], dp[u]+1);
			chmax(ma, dp[v]);
		}
	}

	cout << ma+1 << endl;

	return 0;
}