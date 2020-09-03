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

// https://sleepy-yoshi.hatenablog.com/entry/20130720/p1 のtomerunさんのコード
// [0, N) の乱数をK個非復元抽出？
vector<int> sampling_without_replacement(int N, int K, mt19937 &mt){
    vector<int> vec(N);
    iota(vec.begin(), vec.end(), 0);
    uniform_int_distribution<int> dist(0, INT_MAX);

    vector<int> shuffle_vec;
    for(int i=0;i<K;i++){
        int pos = dist(mt) % (N-i);
        shuffle_vec.push_back(vec[i+pos]);
        swap(vec[i], vec[i+pos]);
    }
    return shuffle_vec;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    random_device rnd;
    mt19937 mt(rnd());

    REP(i, 100){
        cout << sampling_without_replacement(10, 5, mt) << endl;
    }    

    return 0;
}