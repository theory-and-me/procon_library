# 解き方のコツ

##  不等式制約下での最大化

* にぶたんする (ARC50-B 花束とか)
* 候補を全列挙する．不等式制約・目的関数の形によっては，変数を一つ固定するともう一つの値を決めることができたりするので，それで列挙する数を削る．(ABC13-C 節制とか)

## ディオファントス方程式
* 大小関係を考えると，全探索の範囲を減らせる可能性がある
* https://codeforces.com/contest/1244/problem/C ←これだと，yを0<=y<=100000で全探索すればおk（y>100000ならばxの方に押し付けることでx+yがより小さい解にできるため）

## コンビネーションを含む確率の問題
* 普通に計算すると簡単にオーバーフロー・アンダーフローするので，うまく計算する必要がある．

* nCk/(2^n) はパスカルの三角形を利用して計算できるので，これを利用する．実装: combination_probability.cpp 問題: ABC11-D 大ジャンプ

##  連結度の問題
* 辺を削除して非連結にする系問題はフローで解く.

##  無向グラフの最大流
* 適当な向きに辺を追加して，逆辺の容量を元の容量と同じにすればOK．（有向では0にする）

## 漸化式
* 行列累乗を用いて高速に計算できる．また，演算は加算・積算じゃなくても半環の構造を持てばOK（XOR と AND，max と +  とか）
* AND の単位元は ~0L

## 数字の埋め方の数え上げ

* 大きい順・小さい順とかでやるとうまくいくことがあるゾイ

## 和の制約

* 和の制約（Σa_i <= M とか）がある場合，次のようなことが考えられる
* まず，a_i の中に同じ値は sqrt(M) くらいしかない．
* あと，REP(i, N)REP(j, a[i]) みたいなのが可能になる．これによってDPテーブルを埋める時間を削減できたりする．

## gcd とか lcm とか

* gcd, lcm 系の操作は、整数を (素因数 2 の個数, 素因数 3 の個数, 素因数 5 の個数, ...)という無限次元のベクトルに変換すると見通しがよくなることが 多いです。実は、gcd はこのベクトルの各要素について min を取る操作であり、lcm は max を取る操作です。(from DISCO2017 B GCD ロボット　解説)

## 操作がめっちゃ難しい場合は辺を貼ってDPで数え上げとかする可能性
* うほょじょご

## 集合演算
*  集合Sの部分集合を列挙する方法は for(ll T=S;T>=0;T=(T-1)&S)
* ↑は集合S自体と空集合を含むので，分割に関するDPをしたいときは for(ll T=(S-1)&S;T>0;T=(T-1)&S) とする
* S\T の求め方は S^T (ただし T \subset S のとき．それ以外のときは S&~T )


## nが偶数の時n^(n+1) = 1が成り立つ

## 区間をカバーするDP
* codeforces round #544 E

## 回文は，x=x.reverse()で判定できる
* rolling hash, manacher, Z-alogrithm をつかうと効率的に判定できたりする

## rolling hash は 2^64 でmodを取らない
* 蟻本では2^64 だが，簡単にハッシュが衝突するインスタンスを作ることができる
* http://algoogle.hadrori.jp/algorithm/rolling-hash.html

## 木の中心
* 直径Dの木について，Dが偶数ならば，ある頂点vが存在してvから他の頂点までの距離がD/2以下
* Dが偶数ならば，ある頂点eが存在してeから他の頂点までの距離が(D-1)/2以下

## インタラクション問題
* こどふぉの場合，クエリがintでない場合，フラッシュにfflush(stdout)ではなくcout.flush()を使った場合にバグるっぽい
* そもそもC++の場合だとフラッシュは必要ない？

##  中央値の計算について

* クエリによって中央値を動的に求めていく必要がある場合，BITと二分探索によって求めることができる(場合によっては座圧も併用)

## 新しく挿入される値について+1しつつ，二分探索で中央値を取得

* ```
  ll lb = -1, ub = len;
              while(ub - lb > 1){
                  ll m = (ub+lb)/2;
                  if(bit.total(m) >= (cnt+1)/2) ub = m;
                  else lb = m;
              }           
  ```

* ABC127-F とかを参照

## setはinf, -inf を入れると色々楽

## 任意の長さの配列のソートは長さ2のソートに分解できる（i.e. バブルソート）
* 任意の長さのソートを繰り返して作れる配列は長さ2のソートを繰り返して作れる配列に等しい
* えでゅふぉ67 D

## N=5000とかでO(N^2 logN)はきつい 定数倍高速化を考える
* https://codeforces.com/contest/1194/problem/E

## 操作順が非対称なゲームのdpをする場合は「今どちらの手順か」を添字にもつ
* こうすると遷移を考えやすくなるというメリットもある

## 複数の文字列のパターンマッチングはAho-Corasick
* https://ei1333.github.io/luzhiled/snippets/string/aho-corasick.html
* 使い方はECR70 Eなどを参照

## 順列の数え上げ
* bitDP
* 挿入DP
* 箱根駅伝DP
* DEGWERさんのpdfを見る！

## ベルマンフォードの負閉路検出には注意！
* 「グラフに負閉路があるかどうか」と「ある頂点に行くときに負閉路があるかどうか」は別！
* 前者は普通に確認できるけど，後者は注意が必要
* 後者については距離を求めた後にもう一回ベルマンフォードして，負閉路フラグを伝播させると良い
* https://atcoder.jp/contests/abc137/tasks/abc137_e

## ロリハのコツ
* ロリハは半開区間で考えると楽
* すべてのプレフィクスに対してハッシュ値を計算するのは普通に前から計算するだけです．そのテーブルがあれば，任意の部分文字列に対するハッシュも h(s[i,j)) = h(s[0,j)) - h(s[0,i)) * p^{j-i} として計算できます．p^{k} をすべての k について前計算しておけば h(s[i,j)) も O(1) です．
* https://topcoder.g.hatena.ne.jp/spaghetti_source/20130209/1360403866

## 有向グラフにおける閉路検出（というか無限にぐるぐる回る場所の検出）は書き方がある！
* 下の問題の自分の回答を参考にすると良い
* うほょじご https://atcoder.jp/contests/mujin-pc-2018/tasks/mujin_pc_2018_d
* Graph Traveler https://codeforces.com/contest/1200/problem/F
* 上のをやる前に，始点全探索でできる可能性を考えてみるのも大事！https://codeforces.com/contest/1242/problem/C

## 10^7 という制約は，入力をバケットとして扱えることを意味する場合がある
* http://drken1215.hatenablog.com/entry/2019/04/17/193100

## 離散の冪乗根は離散対数問題に変換して解くことができる！
https://cp-algorithms.com/algebra/discrete-root.html
* 具体的には，x^a = y (mod p)なるxを求めたいとすると，pが素数なので原子根gが存在して，あるkを使ってx=g^kと書ける．
* この時，(g^k)^a = y → (g^a)^k = yとなり，kを求める離散対数問題になる．
* 離散対数問題はbaby step giant step などで解ける．
* xは g^k(mod p) で求まります

## 集合からいくつか選んでxorを最大化するのは，掃き出し法で可能！
* 上位ビットから貪欲に１にしていけば良い
https://atcoder.jp/contests/abc141/tasks/abc141_f

## 無向グラフの最小閉路の長さ
* BFSを使った方法と，最短路を使った方法の二種類がある
* BFSを使った方法は，ある頂点からBFSして，合流した時に距離の和をとる．これを全ての頂点からやって最短のものが最小閉路．この方法は多重辺があると壊れるので注意．
https://codeforces.com/contest/1205/problem/B
* 最短路を使った方法は，全ての辺(u, v)をのぞいた時に，u-v最短路の長さ+1が辺(u,v)を含むサイクルのサイクルのサイクルの最短長になるので，これを全ての(u,v)について調べる

## 包徐のコツ
* 普通に考えると頭がバグるので，ちゃんと論理記号の形で書く．
* 「または」の形になっている場合は普通に包徐．
* 「かつ」の形になっている場合はドモルガンを使って「または」に直す．A and B = not ((not A) or (not B))

## 上がったり下がったりするものを並べ替えて全体の最大値・最小値を最適化する問題
* https://codeforces.com/contest/1203/problem/F1
* https://arc053.contest.atcoder.jp/tasks/arc053_c
* トータルで上がるか下がるかで場合分けして，ソートする
* ソートの仕方は，片方はわかりやすいがもう片方が難しい場合がある．そういう時は，逆向きの操作を考えると本質的に同じことをすればよくなる

## 燃やす埋める
* 最小カットを使ってやるやつ
* Project Selection Problem とかで理解するのも」良いっぽい
* 例題 https://atcoder.jp/contests/arc085/tasks/arc085_c
* Project selection problem http://tokoharuland.hateblo.jp/entry/2017/11/12/234636
* https://en.wikipedia.org/wiki/Max-flow_min-cut_theorem#Project_selection_problem

## 独立なゲームに分けられるようなゲームはgrundy数を考えると良い！
* grundy数は理論的に求めるのは難しいので実験でエスパーすることが多い

## オーバーフローする場合の解決
* python を使う
* long double を使う https://codeforces.com/contest/903/submission/33193449
* 自分で多倍長整数を定義する　https://codeforces.com/blog/entry/67827
* atcoder なら boost が使える

## 隣あう2つの値をその和で置き換える時，「数が減る」か「和か9減る」
* https://atcoder.jp/contests/ddcc2020-qual/tasks/ddcc2020_qual_d

## 操作の回数がどうやっても等しい時は，何らかの不変量があると考えるべき

## 二分探索は，単調性がない場合もできる！！
* 逆の視点で書くと、元々二分探索のアルゴリズムができることは「ある判定の結果が左端＝A、右端＝Bだと分かっているときに、A, Bが隣り合っている箇所をどこでもいいから1つだけ見つける」ことです。さらにもし単調性がある場合にはこの箇所がただ1つであり、そこを境界にしてAとBが真っ二つに分かれるので、最大値・最小値を求めるために使える、というわけです。 https://betrue12.hateblo.jp/entry/2019/11/25/235324
* https://atcoder.jp/contests/ddcc2020-qual/tasks/ddcc2020_qual_e

## 「何個かの内何個かを選んで」みたいなDP
* 同じ物を二度使えないので，何らか順番をつける必要がある
* このとき，「二つの要素iとjが入れ替え可能な条件」を考えると良いかもしれない
* 例えば，「条件Aが成り立つならばi->jの時必ずj->iもOK」みたいな条件があったなら，条件Aが成り立つように並び替えればj->iの場合だけ考えれば良くなる
* https://atcoder.jp/contests/dp/tasks/dp_x

## 区間グラフ
* 基本的に区間の始点と終点をイベントソートして，左から右に見ていくとうまくいくことがある（始点と終点の間に順序関係を入れる必要がある場合に注意！）
* 区間 [s1, t1],...,[sn, tn] で交わらないものが存在する　⇄　あるiとjについてti < sj ⇄ min(t) < max(s)
* https://codeforces.com/contest/1284/problem/D

## 木に近いグラフの最短路
* 先に全域木をとっておいて，木を通る最短路に関してはLCAで，それ以外に関しては「全域木に入ってない枝の両端から先にダイクストラをして距離を保持しておく」ことで対応すると，素早く処理できる
* https://codeforces.com/contest/1051/problem/F


## 長い桁数の数字の比較二つの長い数字があって（例; S=144555, T=345），Tをスライドさせて行ったときにSの該当部分とTのどっちが大きいかを知りたい．これはT+SにZ-algorithmを使っておけばO(|S|+|T|)でできる
* https://codeforces.com/contest/1051/problem/E

## ある区間の「ユニークな要素数」を求めるのは，range sum query でできる！
* 最新の値のみに1を立てつつ左から右に走査
* https://codeforces.com/contest/1288/problem/E

## 「大きさDの部分木にx加算」というクエリはdfs+range add queryでできる！
* https://codeforces.com/contest/1288/problem/E

## 隣接スワップする問題は，bitDP+転倒数で行けることが多い

## 二点間のマンハッタン距離の最大値は，次元をk, 点の数をnとしてO(n2^k)で求められる
* しかもセグ木とかにも載せることができる
* 分かりやすい解説 http://kagamiz.hatenablog.com/entry/2014/12/21/213931
* 問題 https://codeforces.com/contest/1093/problem/G

## 線分の交差判定
* https://codeforces.com/contest/1036/problem/E とかを参考に．

## メビウス関数の計算
* https://codeforces.com/contest/1139/submission/51778759 とかを参考に

## シンプルなDPの更新はFFTでできたりする
* https://codeforces.com/contest/1096/problem/G

## 区間反転・区間加算などの操作は，階差をとって二点への操作と考えると良いことがある
* https://atcoder.jp/contests/abc155/tasks/abc155_f

## 最密部分グラフ的な問題はネットワークフローで解ける
* https://codeforces.com/contest/1082/problem/G

## ソートしてDPするみたいなやつの考え方
* 「ある実効可能解があるとき，それを何らかの順番でソートしても実行可能解のままである」+ 「目的関数値はソートしても変わらないor小さくなる」みたいな性質がある時に使える方法
* この場合，最初からソートされた順番で選ぶことを考えれば全てのパターンを考慮できていることになるのでOKみたいな理屈
* 前者の条件は，「隣り合っている2つをときにある基準が成り立つように入れ替えても実行可能性が壊れず目的関数も増加しない」ことを言えばいい．このとき「ある基準」がソートの評価関数になる
https://atcoder.jp/contests/dp/tasks/dp_w
https://codeforces.com/contest/1203/problem/F1
https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_d

## 同型な2分木を前列挙する方法
* 葉を付け替えながら連続的に変形していく
* パスから初めて，パスの先端をなるべく根元につけていくのを繰り返す
* https://codeforces.com/contest/1311/problem/E のtuteさんのsubmitを見るといいかも

## 桁DPで leading zero がめんどくさい時
* 賢い方法があります
* https://codeforces.com/problemset/problem/1073/E
* 例えば 24567 以下の(条件)の数を数えるときは，
  1. 一番上の桁から遷移するときだけ，1-9に遷移するようにする（普通は0-9）こうすることで，一番上の位は0でないことが保証される
  2. 上の方法で数えた時の値を f(x) とすると，f(24567) + f(9999) + f(999) + f(99) + f(9) で数える．これによりleading zero を回避可能．
* 詳しくは上の問題の editorial, sample code を見ればわかるかも

## 文字列の最小周期はKMPテーブルを使って求められる
* 文字のprefixとsuffixの最大共通要素数を前計算すればOK. これはKMPテーブルとか，prefix function とか呼ばれたりする．
* 例えば，abbabbabb の prefix function は 6．KMPを使えば，長さnの文字列について各i文字目までのprefix functionをO(n)で計算できる
* https://pekempey.hatenablog.com/entry/2017/07/17/232047

## 区間で一度しか出てこない要素を求めるクエリ
* https://codeforces.com/contest/1000/problem/F
* 右端を固定すればセグ木で可能．（値ごとに，一番右の要素の場所に「直左の同じ値の要素の場所」を入れ，それ以外はINFを入れておく．[L, R+1)で最小値クエリして値がLより小さければその値が一度しか出てこない）
* オフラインだったら右端ソートして順番にやればOK
* 「区間の要素数」はクエリ平方分割が定石だが，セグ木でできることも多い

## 必ず使う〜を求めよ，みたいな問題は，「範囲を考えてそれが一意なら使う」みたいに考えると良いかも
* https://atcoder.jp/contests/abc161/tasks/abc161_e

## 構築で分からなかったらこれとか見てみる？
* https://www.hamayanhamayan.com/entry/2017/08/21/102212

## 前からと後ろからがあってややこしい問題はワイルドカードを使うと考えやすいかも…
* https://codeforces.com/contest/1336/problem/C

## 状態が大きい探索（BFS, DFS, Dijkstra）はグラフを陽に構築しないほうがいいかも…
* https://codeforces.com/contest/1340/problem/C

## Dijkstraだとやばそうな場合，BFSとか01BFSで線形にできないかを考えてみる
* https://codeforces.com/contest/1340/problem/C

## グラフにの頂点や辺に値が乗っていて，GCDが1でない連結成分やパスを考える問題
* 素因数ごとにグラフを作って考えれば分かりやすい
* 素因数ごとに考える場合，各頂点が出てくる回数はそれほど多くならないことに注意する（なぜなら，一つの自然数が持つ素因数の数は非常に少ないため）
* https://codeforces.com/contest/1101/problem/D

## メディアンに関する色々
* 大小関係に関する多数決だと思えば良いことがある　https://codeforces.com/contest/1349/problem/B
* メディアンがx以上である区間の数は転倒数っぽくO(n log n) で数えられる．
* メディアンが丁度xである区間の数は上記で（x以上の数）-(x+1以上の数)をすれば数えられる
* 二分探索と相性が良い
