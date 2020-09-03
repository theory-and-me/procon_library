#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
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

string num2bit(ll num, ll len){
    string bit = "";
    REP(i, len){
    bit += char('0'+(num>>i & 1));
    }
    return bit;
}

// アルメリアさんのを参考に
// https://atcoder.jp/contests/abc141/submissions/8551806

// vの most significant bit のみが立った数を返す
// やってることは，v の msb 以下の bit が全て立った数 w を作って，w^(w>>1)を返す
ll msb(ll v){
  v = v | (v >>  1);
  v = v | (v >>  2);
  v = v | (v >>  4);
  v = v | (v >>  8);
  v = v | (v >> 16);
  v = v | (v >> 32);
  return v ^ (v >> 1);
}

vector<ll> elimination_F2(vector<ll> &A){
    vector<ll> V;
    for(ll a: A){
        for(ll v: V){
            if(msb(v)&a) a ^= v;
        }
        if(a>0){
            for(ll& v: V){
                if(msb(a)&v) v ^= a;
            }
            V.push_back(a);
            sort(V.rbegin(), V.rend());
        }
    }
    return V;
} 

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<ll> A(N);
    REP(i, N) cin >> A[i];

    ll res = 0;
    REP(b, 60){
        ll cnt = 0;
        ll val = (1ll<<b);
        REP(i, N){
            if(A[i]>>b & 1) cnt++;
        }
        if(cnt&1){
            res += val;
            REP(i, N){
                if(A[i]>>b & 1) A[i] ^= val;
            }
        }
    }

    auto V = elimination_F2(A);
    ll tmp = 0;
    for(auto v: V){
        tmp ^= v;
    }
    cout << res+2*tmp << endl;

    return 0;
}