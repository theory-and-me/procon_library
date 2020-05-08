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
void debug(vector<string>&v,ll h,ll w){for(ll i=0;i<h;i++)
{for(ll j=0;j<w;j++)cerr<<v[i][j];cerr<<endl;}};
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

struct Trie{
    char a_init; // 最初の文字
    int D; // 文字の種類数
    int INVALID = -1;
    std::vector<std::vector<int>> child;
    // 子のid．サイズは（頂点数，文字の種類数）で，child[v][c]は「頂点vから文字cで下降したときの頂点のid」
    // 行き先に頂点がない場合はINVALIDが格納される
    using T_NODE = int;
    vector<T_NODE> v_info;
    // v_info には適当に頂点vの性質をメモすることができる
    // 例えば add_word の info に1を入れると出現回数のカウントができる
    Trie(char a_init = 'a', int D = 26) : a_init(a_init), D(D), child(1, std::vector<int>(D, INVALID)), v_info(1) {}
    void add_word(string str, T_NODE info) {
        int now = 0; // 頂点のid
        for (auto &c : str) {
            if (child[now][c - a_init] == INVALID) {
                child[now][c - a_init] = child.size();
                child.emplace_back(std::vector<int>(D, INVALID));
                v_info.resize(child.size());
            }
            now = child[now][c - a_init];
        }
        v_info[now] += info;
    }

    // 操作はこの上でdfsなどをすればOK
};

// verified @ https://tenka1-2016-final-open.contest.atcoder.jp/tasks/tenka1_2016_final_c
// see also https://codeforces.com/contest/965/problem/E
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    string S;
    cin >> S;
    ll N = S.size();

    ll M;
    cin >> M;
    vector<string> P(M);
    REP(i, M) cin >> P[i];
    vector<ll> W(M);
    REP(i, M) cin >> W[i];

    Trie trie('a', 26);
    trie.add_word("", 0);
    REP(i, M){
        trie.add_word(P[i], W[i]);
    }

    //debug(trie.child[0], 26);

    vector<ll> dp(N+1, -1);
    dp[0] = 0;
    REP(i, N){
        ll now = 0;
        ll j = 0;
        while(now != -1){
            chmax(dp[i+j], dp[i]+trie.v_info[now]);
            if(i+j>=N) break;
            now = trie.child[now][S[i+j]-'a'];
            j++;
        }
        chmax(dp[i+1], dp[i]);
    }    

    cout << dp[N] << endl;

    return 0;
}