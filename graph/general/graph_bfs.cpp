#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<vector<ll>> Graph;

const ll mod = 1e9 + 7;
//const ll mod = 998244353;

#define REP(i,n) for(ll i=0;i<(ll)n;i++)
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define spa << " " <<
#define fi first
#define se second

template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }

template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){
os << "(" << v.first << ", " << v.second << ")"; return os;
}
template<class T> ostream& operator << (ostream& os, const vector<T> v){
for(int i = 0; i < (int)v.size(); i++){if(i > 0){os << " ";} os << v[i];} return os;
}
template<class T> ostream& operator << (ostream& os, const vector<vector<T>> v){
for(int i = 0; i < (int)v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}

template<typename T> void debug(vector<vector<T>>&v,ll h,ll w){for(ll i=0;i<h;i++)
{cerr<<v[i][0];for(ll j=1;j<w;j++)cerr spa v[i][j];cerr<<endl;}};
template<typename T> void debug(vector<T>&v,ll n){if(n!=0)cerr<<v[0];
for(ll i=1;i<n;i++)cerr spa v[i];
cerr<<endl;};

string num2bit(ll num, ll len){
    string bit = "";
    REP(i, len){
    bit += char('0'+(num>>i & 1));
    }
    return bit;
}

vector<int> graph_bfs(Graph &G, vector<ll> &s){
    // sは始点のリスト
    const int N = G.size();
    vector<int> dist(N, -1);
    queue<int> qu;

    // initialization
    for(auto v: s){
        qu.push(v);
        dist[v] = 0;
    }

    while(!qu.empty()){
        int now = qu.front();qu.pop();
        for(auto next: G[now]){
            if(dist[next] != -1) continue;
            dist[next] = dist[now] + 1;
            qu.push(next);
        }
    }

    return dist;
}

// verified @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;
    Graph G(n);
    REP(i, n){
        ll u, k;
        cin >> u >> k;
        u--;
        REP(j, k){
            ll v;
            cin >> v;
            v--;
            G[u].push_back(v);
        }
    }

    vector<ll> s = {0};

    auto dist = graph_bfs(G, s);

    REP(i, n){
        cout << i+1 << " " << dist[i] << endl;
    }

    return 0;
}