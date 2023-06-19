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

// hitonanode さんの radix heap. https://hitonanode.github.io/cplib-cpp/data_structure/radix_heap.hpp
template <class Uint, class Label, typename std::enable_if<std::is_unsigned<Uint>::value>::type * = nullptr>
class radix_heap {
    int sz;
    Uint last;
    std::array<std::vector<std::pair<Uint, Label>>, std::numeric_limits<Uint>::digits + 1> v;

    template <class U, typename std::enable_if<sizeof(U) == 4>::type * = nullptr>
    static inline int bucket(U x) noexcept {
        return x ? 32 - __builtin_clz(x) : 0;
    }
    template <class U, typename std::enable_if<sizeof(U) == 8>::type * = nullptr>
    static inline int bucket(U x) noexcept {
        return x ? 64 - __builtin_clzll(x) : 0;
    }

    void pull() {
        if (!v[0].empty()) return;
        int i = 1;
        while (v[i].empty()) ++i;
        last = v[i].back().first;
        for (int j = 0; j < int(v[i].size()); j++) last = std::min(last, v[i][j].first);
        for (int j = 0; j < int(v[i].size()); j++) {
            v[bucket(v[i][j].first ^ last)].emplace_back(std::move(v[i][j]));
        }
        v[i].clear();
    }

public:
    radix_heap() : sz(0), last(0) {
        static_assert(std::numeric_limits<Uint>::digits > 0, "Invalid type.");
    }
    std::size_t size() const noexcept { return sz; }
    bool empty() const noexcept { return sz == 0; }
    void push(Uint x, const Label &val) { ++sz, v[bucket(x ^ last)].emplace_back(x, val); }
    void push(Uint x, Label &&val) { ++sz, v[bucket(x ^ last)].emplace_back(x, std::move(val)); }
    template <class... Args> void emplace(Uint x, Args &&...args) {
        ++sz, v[bucket(x ^ last)].emplace_back(std::piecewise_construct, std::forward_as_tuple(x),
                                               std::forward_as_tuple(args...));
    }
    void pop() { pull(), --sz, v[0].pop_back(); }
    std::pair<Uint, Label> top() { return pull(), v[0].back(); }
    Uint top_key() { return pull(), last; }
    Label &top_label() { return pull(), v[0].back().second; }
    void clear() noexcept {
        sz = 0, last = 0;
        for (auto &vec : v) vec.clear();
    }
    void swap(radix_heap<Uint, Label> &a) {
        std::swap(sz, a.sz), std::swap(last, a.last), v.swap(a.v);
    }
};

template<typename T> // T は辺のコストの型
struct grid_map{
    const T T_INF = numeric_limits<T>::max();
    const int num_dirs =  4;
    const vector<int> dx = {0, -1, 0, 1};
    const vector<int> dy = {-1, 0, 1, 0};
    const vector<char> dc = {'L', 'U', 'R', 'D'};

    // H: 縦の長さ W: 横の長さ
    // access: 移動コストを表現する3次元配列．access[x][y][dir] はマス(x, y)から方向dirに進むときのコストを表す．-1の場合は移動不可能．
    int H, W;
    vector<vector<vector<T>>> access;
    vector<T> access_array;
    bool array_flag = false;

    grid_map(int H, int W): H(H), W(W){
        access.resize(H);
        for(int i=0;i<H;i++) access[i].resize(W);
        for(int i=0;i<H;i++) for(int j=0;j<W;j++) access[i][j].resize(num_dirs);
        for(int i=0;i<H;i++) for(int j=0;j<W;j++) for(int k=0;k<num_dirs;k++) access[i][j][k] = -1;
        access_array.resize(H * W * num_dirs);
    }

    int encode_access(int x, int y, int z){
        return x * W * num_dirs + y * num_dirs + z;
    }

    int encode_grid(int x, int y){
        return x * W + y;
    }

    pair<int, int> decode_grid(int x){
        return {x / W, x % W};
    }

    void make_access_array(){
        REP(i, H) REP(j, W) REP(k, num_dirs) access_array[encode_access(i, j, k)] = access[i][j][k];
        array_flag = true;
    }

    // BFS. 辺重みが1のみの場合しか使えない
    vector<vector<T>> bfs(int sx, int sy){

        if(!array_flag) make_access_array();

        vector<T> dist(H * W, -1);
        queue<int> qu;

        int s = encode_grid(sx, sy);
        dist[s] = 0;
        qu.emplace(s);

        while(!qu.empty()){
            auto v_cur = qu.front();qu.pop();
            auto [cx, cy] = decode_grid(v_cur);
            for(int i=0;i<num_dirs;i++){
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                int v_next = encode_grid(nx, ny);
                if(access_array[encode_access(cx, cy, i)] == -1) continue;
                if(dist[v_next] != -1) continue;
                
                dist[encode_grid(nx, ny)] = dist[v_cur] + access_array[encode_access(cx, cy, i)];
                qu.emplace(v_next);
            }
        }
        
        vector<vector<T>> dist_grid(H, vector<T>(W));
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                dist_grid[i][j] = dist[encode_grid(i, j)];
            }
        }

        return dist_grid;
    }

    // 経路復元付きBFS. 辺重みが1のみの場合しか使えない
    tuple<T, string> bfs_reconstruction(int sx, int sy, int tx, int ty){

        if(!array_flag) make_access_array();

        vector<T> dist(H * W, -1);
        vector<T> pre_v(H * W, -1);
        queue<int> qu;

        int s = encode_grid(sx, sy);
        dist[s] = 0;
        qu.emplace(s);

        while(!qu.empty()){
            auto v_cur = qu.front();qu.pop();
            auto [cx, cy] = decode_grid(v_cur);
            for(int i=0;i<num_dirs;i++){
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                int v_next = encode_grid(nx, ny);
                if(access_array[encode_access(cx, cy, i)] == -1) continue;
                if(dist[v_next] != -1) continue;
                
                dist[encode_grid(nx, ny)] = dist[v_cur] + access_array[encode_access(cx, cy, i)];
                pre_v[v_next] = v_cur;
                qu.emplace(v_next);
            }
        }

        string route = "";

        if(dist[encode_grid(tx, ty)] == -1){
            return {-1, route};
        }

        int v_cur = encode_grid(tx, ty);
        while(v_cur != s){
            int v_pre = pre_v[v_cur];
            auto [cx, cy] = decode_grid(v_cur);
            auto [px, py] = decode_grid(v_pre);
            for(int i=0;i<4;i++){
                if(dx[i] == cx - px and dy[i] == cy - py){
                    route.push_back(dc[i]);
                }
            }
            v_cur = v_pre;
        }
        reverse(route.begin(), route.end());
        return {dist[encode_grid(tx, ty)], route};
    }

    // Dijkstra法による最短経路．負辺は扱えない
    vector<vector<T>> Dijkstra(int sx, int sy){

        if(!array_flag) make_access_array();

        int s = encode_grid(sx, sy);
        vector<T> dist(H * W, T_INF);
        vector<int> pre_v(H * W, T_INF);

        using Pi = pair<T, int>;
        priority_queue<Pi, vector<Pi>, greater<Pi>> pq;
        // radix_heap<typename std::make_unsigned<T>::type, int> pq; // 符号なし整数にしか使えないが，定数倍が高速

        dist[s] = 0;
        pq.emplace(0, s);

        while(!pq.empty()){
            auto [cost, v_cur] = pq.top();pq.pop();
            auto [x_cur, y_cur] = decode_grid(v_cur);
            if(dist[v_cur] < cost) continue;
            for(int i=0;i<num_dirs;i++){
                if(access_array[v_cur * num_dirs + i] == -1) continue;
                auto cost_next = cost + access_array[v_cur * num_dirs + i];
                int x_next = x_cur + dx[i];
                int y_next = y_cur + dy[i];
                int v_next = encode_grid(x_next, y_next);
                if(dist[v_next] <= cost_next) continue;
                dist[v_next] = cost_next;
                pq.emplace(dist[v_next], v_next);
            }
        }

        vector<vector<T>> dist_grid(H, vector<T>(W));
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                dist_grid[i][j] = dist[encode_grid(i, j)];
            }
        }

        return dist_grid;
    }

    // Dijkstra法による経路復元付き最短経路．負辺は扱えない
    tuple<T, string> Dijkstra_reconstruction(int sx, int sy, int tx, int ty){

        if(!array_flag) make_access_array();

        int s = encode_grid(sx, sy);
        vector<T> dist(H * W, T_INF);
        vector<int> pre_v(H * W, T_INF);

        using Pi = pair<T, int>;
        priority_queue<Pi, vector<Pi>, greater<Pi>> pq;
        // radix_heap<typename std::make_unsigned<T>::type, int> pq; // 符号なし整数にしか使えないが，定数倍が高速

        dist[s] = 0;
        pq.emplace(0, s);

        while(!pq.empty()){
            auto [cost, v_cur] = pq.top();pq.pop();
            auto [x_cur, y_cur] = decode_grid(v_cur);
            if(dist[v_cur] < cost) continue;
            for(int i=0;i<num_dirs;i++){
                if(access_array[v_cur * num_dirs + i] == -1) continue;
                auto cost_next = cost + access_array[v_cur * num_dirs + i];
                int x_next = x_cur + dx[i];
                int y_next = y_cur + dy[i];
                int v_next = encode_grid(x_next, y_next);
                if(dist[v_next] <= cost_next) continue;
                dist[v_next] = cost_next;
                pre_v[v_next] = v_cur;
                pq.emplace(dist[v_next], v_next);
            }
        }

        string route = "";

        if(dist[encode_grid(tx, ty)] == T_INF){
            return {dist[encode_grid(tx, ty)], route};
        }

        int v_cur = encode_grid(tx, ty);
        while(v_cur != s){
            int v_pre = pre_v[v_cur];
            auto [cx, cy] = decode_grid(v_cur);
            auto [px, py] = decode_grid(v_pre);
            for(int i=0;i<4;i++){
                if(dx[i] == cx - px and dy[i] == cy - py){
                    route.push_back(dc[i]);
                    break;
                }
            }
            v_cur = v_pre;
        }
        reverse(route.begin(), route.end());

        return {dist[encode_grid(tx, ty)], route};
    }
};

// verified BFS @ https://atcoder.jp/contests/abc007/tasks/abc007_3
// int main(){

//     int H, W, sx, sy, tx, ty;
//     cin >> H >> W >> sx >> sy >> tx >> ty;
//     sx--, sy--, tx--, ty--;
//     vector<string> S(H);
//     REP(i, H) cin >> S[i];

//     grid_map<int> G(H, W);
//     REP(i, H){
//         REP(j, W){
//             if(S[i][j] == '#') continue;
//             REP(k, G.num_dirs){
//                 int nx = i + G.dx[k];
//                 int ny = j + G.dy[k];
//                 if(nx >= 0 and nx < H and ny >= 0 and ny < W and S[nx][ny] != '#'){
//                     G.access[i][j][k] = 1;
//                 }
//             }
//         }
//     }

//     // auto dist = G.bfs(sx, sy);
//     // cout << dist[tx][ty] << endl;

//     auto [dist, route] = G.bfs_reconstruction(sx, sy, tx, ty);
//     cout << route << endl;

//     return 0;
// }

// Verified Dijkstra @ https://atcoder.jp/contests/past201912-open/tasks/past201912_j
int main(){
    int H, W;
    cin >> H >> W;
    auto A = make_vec(H, W, 0ll);
    REP(i, H) REP(j, W) cin >> A[i][j];

    grid_map<ll> G(H, W);
    REP(i, H){
        REP(j, W){
            REP(k, G.num_dirs){
                int nx = i + G.dx[k];
                int ny = j + G.dy[k];
                if(nx >= 0 and nx < H and ny >= 0 and ny < W){
                    G.access[i][j][k] = A[nx][ny];
                }
            }
        }
    }

    auto dist1 = G.Dijkstra(H-1, 0);
    auto dist2 = G.Dijkstra(0, W-1);
    auto dist3 = G.Dijkstra(H-1, W-1);

    ll res = G.T_INF;
    REP(i, H){
        REP(j, W){
            chmin(res, dist1[i][j] + dist2[i][j] + dist3[i][j] - 2 * A[i][j]);
        }
    }
    cout << res << endl;

    // auto [dist, route] = G.Dijkstra_reconstruction(0, W-1, H-1, 0);
    // cout << dist << endl;
    // cout << route << endl;
}