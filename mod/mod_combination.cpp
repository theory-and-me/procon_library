#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ull mod = 1000000000 + 7;
#define REP(i,n) for(int i=0;i<(int)n;++i)

//コンビネーションのクエリ応答用の高速mod計算．
//make()で配列を先に作ることで高速にクエリ応答できる．
//C = 0 の場合は0を，D=0の場合は1を返すことに注意．

const ll N_MAX = 300005;

ll inv[N_MAX],fac[N_MAX],finv[N_MAX];
void make(){
    fac[0]=fac[1]=1;
    finv[0]=finv[1]=1;
    inv[1]=1;
    for(int i=2;i<N_MAX;i++){
        inv[i]=mod-inv[mod%i]*(mod/i)%mod;
        fac[i]=fac[i-1]*(ll) i%mod;
        finv[i]=finv[i-1]*inv[i]%mod;
    }
}

ll comb(ll C, ll D){
    // 先にmakeをするのを忘れない！
    if(C<D||C<1) return 0;
    return fac[C]*(finv[D]*finv[C-D]%mod)%mod;
}

int main(){
    // verified @ https://abc021.contest.atcoder.jp/tasks/abc021_d

    make();

    ll n, k;
    cin >> n >> k;

    cout << comb(k+n-1, k) << endl;
    return 0;
}