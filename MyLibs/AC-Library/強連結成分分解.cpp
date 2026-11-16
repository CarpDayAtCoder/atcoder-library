#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// AC-Library SCC（強連結成分分解）テンプレート
//
// 使用頻度：★★★☆☆
// 主な用途：有向グラフの強連結成分分解，サイクル，縮約グラフ
// キーワード：scc_graph，add_edge，scc
//
// scc_graph g(n);
//   頂点0～n-1を持つ有向グラフを作成する．
//
// g.add_edge(u, v);
//   u → v の有向辺を追加する．
//
// auto groups = g.scc();
//   強連結成分を vector<vector<int>> で返す．
//   groups[i] が1つの強連結成分の頂点一覧．
//   強連結成分はトポロジカル順に並ぶ．
//   各強連結成分内の頂点の順番は保証されない．
//
// 計算量：O(N+M)
//
// 【注意】
// scc_graphが扱う頂点番号は0～n-1．
// 1-indexでn+1頂点作ると，使わない頂点0も1つのSCCとして出力される．
//
// ============================================================

// ============================================================
// 実戦用テンプレート
// ============================================================
#if 0

#include <atcoder/scc>
using namespace atcoder;

int main() {
    int n, m;   cin >> n >> m;

    scc_graph g(n);                       // 頂点0～n-1．1-indexにはしない

    for (int i=0; i<m; i++) {
        int u, v;   cin >> u >> v;
        u--, v--;                          // 入力が1-indexの場合
        g.add_edge(u, v);                  // u → v
    }

    auto groups = g.scc();      // SCCごとの頂点一覧．vector<vector<int>>．トポロジカル順
    int k = ssize(groups);      // SCCの個数

    vector<int> id(n);                     // id[v]：頂点vが属するSCC番号
    for (int i=0; i<k; i++)
        for (int v : groups[i]) id[v] = i;

    return 0;
}

#endif


// ============================================================
// 学習用実行例
// ============================================================
#if 1

#include <atcoder/scc>
using namespace atcoder;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 7;
    scc_graph g(n);

    // 0 → 1 → 2 → 3 ⇄ 4 → 5 → 6
    // ↑       ↓
    // └───────┘

    // {0,1,2} が1つのSCC
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);

    // {3,4} が1つのSCC
    g.add_edge(3, 4);
    g.add_edge(4, 3);

    // 2 → 3
    g.add_edge(2, 3);

    // 4 → 5 → 6
    g.add_edge(4, 5);
    g.add_edge(5, 6);

    auto groups = g.scc();

    cout << "===== 強連結成分 =====\n";
    cout << "SCC数: " << ssize(groups) << '\n';

    for (int i=0; i<ssize(groups); i++) {
        cout << "SCC " << i << ": ";
        for (int v : groups[i]) cout << v << ' ';
        cout << '\n';
    }

    cout << "\n===== 各頂点のSCC番号 =====\n";
    vector<int> id(n);
    for (int i=0; i<ssize(groups); i++)
        for (int v : groups[i]) id[v] = i;

    for (int v=0; v<n; v++)
        cout << "頂点" << v << ": SCC " << id[v] << '\n';

    return 0;
}

#endif


// ============================================================
// 各頂点が属するSCC番号
//
// auto groups = g.scc();
//
// vector<int> id(n);
// for (int i=0; i<ssize(groups); i++)
//     for (int v : groups[i]) id[v] = i;
//
// id[v] が，頂点vの属するSCC番号．
// groupsはトポロジカル順なので，異なるSCC間に辺 a → b があれば
// id[a] < id[b] となる．
//
// ============================================================
// 縮約グラフを作る場合
//
// 元の辺をedgesに保存しておき，SCC番号へ変換する．
//
// vector<vector<int>> dag(k);
// for (auto [u, v] : edges) {
//     int a = id[u], b = id[v];
//     if (a != b) dag[a].push_back(b);
// }
//
// 同じ2つのSCC間に複数の辺があると，dagにも重複辺が入る．
// 必要ならsort＋uniqueやsetなどで除去する．
//
// ============================================================
// SCCとサイクル
//
// 同じSCCに属する2頂点は，互いに到達可能．
//
// SCCの頂点数が2以上なら，そのSCC内にはサイクルがある．
// 頂点数が1の場合でも，自己ループ v → v があればサイクルになる．
//
// ============================================================