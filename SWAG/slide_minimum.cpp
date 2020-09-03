#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
//typedef vector<vector<ll>> Graph;

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

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n; // length of array
    ll k; // length of sliding window

    cin >> n >> k;

    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    vector<ll> res(n-k+1);
    deque<int> dq;
    REP(i, n){
        // 最小値のときは>=, 最大値のときは<=
    	//while(!dq.empty() && a[dq.back()] >= a[i]){
        while(!dq.empty() && a[dq.back()] <= a[i]){
    		dq.pop_back();
    	}
    	dq.push_back(i);

        // iが小さい場合についても出力したい場合
        //cout << a[dq.front()] << endl;

    	if(i>=k-1){
    		res[i-k+1] = a[dq.front()];
    		if(dq.front() == i-k+1) dq.pop_front();
    	}
    }

    cout << res << endl;

    return 0;
}