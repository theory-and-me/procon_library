#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ull mod = 1e9 + 7;
#define REP(i,n) for(int i=0;i<(int)n;++i)

//debug
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

template<class S, class T> ostream& operator << (ostream& os, const pair<S, T> v){
  os << "(" << v.first << ", " << v.second << ")"; return os;
}
template<class T> ostream& operator << (ostream& os, const vector<T> v){
  for(int i = 0; i < v.size(); i++){if(i > 0){os << " ";} os << v[i];} return os;
}
template<class T> ostream& operator << (ostream& os, const vector<vector<T>> v){
  for(int i = 0; i < v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}

typedef vector<ll> Edges;
typedef vector<Edges> Graph;

// NOT VERIFIED
// トポロジカルソートで最長パスの長さを求めるやつ
// 返り値はトポロジカルソート不可能な場合（ループがある場合）-1
// それ以外は最長パスの長さ
// 配列tsには「頂点iを終点とする最長のパスの長さ」が入る

const ll V_MAX = 101010; // !! SHOULD BE EDITTED !!
vector<ll> ts(V_MAX, -1);

int topologicalSortLength(Graph &G){
	ll V = G.size();
	vector<ll> indeg(V, 0);
	queue<ll> qu;

	REP(i, V){
		REP(j, G[i].size()){
			indeg[G[i][j]]++;
		}
	}
	REP(i, V){
		if(!indeg[i]) qu.push(i);
	}

	ll depth = 0;
	while(!qu.empty()){
		ll s = qu.size();
		REP(i, s){
			ll now = qu.front();qu.pop();
			ts[now] = depth;
			REP(j, G[now].size()){
				ll next = G[now][j];
				indeg[next]--;
				if(!indeg[next]) qu.push(next);
			}
		}
		depth++;
	}

	REP(i, V){
		if(ts[i] == -1) return -1;
	}
	return depth;
}

// VERIFIED @ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B
// 普通のトポロジカルソート
// 返り値はトポロジカルソート不可能な場合（ループがある場合）false，それ以外 true
// tsには順番が入ります
// V_MAX と tsを上からコピーしてくるのを忘れない
bool topologicalSort(Graph &G){
	ll V = G.size();
	vector<ll> indeg(V, 0);
	queue<ll> qu;

	REP(i, V){
		REP(j, G[i].size()){
			indeg[G[i][j]]++;
		}
	}
	REP(i, V){
		if(!indeg[i]) qu.push(i);
	}

	ll idx = 0;
	while(!qu.empty()){
		ll s = qu.size();
		REP(i, s){
			ll now = qu.front();qu.pop();
			ts[now] = idx;
			idx++;
			REP(j, G[now].size()){
				ll next = G[now][j];
				indeg[next]--;
				if(!indeg[next]) qu.push(next);
			}
		}
	}

	return (idx == V);
}



int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll V, E;
    cin >> V >> E;
    Graph G(V);
    REP(i, E){
    	ll s, t;
    	cin >> s >> t;
    	G[s].push_back(t);
    }

    topologicalSort(G);
    vector<pll> P(V);
    REP(i, V) P[i].first = ts[i], P[i].second = i;
    sort(P.begin(), P.end());

    REP(i, V){
    	cout << P[i].second << endl;
    }
    return 0;
}