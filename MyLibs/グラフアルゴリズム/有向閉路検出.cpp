#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// 有向グラフの閉路検出（DFS）テンプレート
//
// 使用頻度：★★★★☆
// 主な用途：有向グラフにサイクル（閉路）が存在するか判定
// キーワード：DFS，cycle，directed graph，state，閉路検出
//
// 【基本】
// DFS中の各頂点を3つの状態で管理する．
//  ・state[v] == 0：未探索
//  ・state[v] == 1：現在DFSで探索中
//  ・state[v] == 2：探索完了
//
// 頂点vから頂点nvへの辺を調べたとき，
// state[nv] == 1なら，現在のDFS経路上の頂点へ戻ったことになる．
// したがって，有向サイクルが存在する．
//     state[nv] == 0 → まだ未探索なのでDFSする
//     state[nv] == 1 → 閉路を発見
//     state[nv] == 2 → すでに探索完了なので何もしない
//
// 【計算量】
// 各頂点，各辺を定数回しか処理しないためO(N + M)．
//
// ============================================================
// 注意
// 【1】visitedだけでは不十分
//   「一度訪問したか」だけではなく，「現在のDFS経路上にあるか」を区別する必要がある．
//   そのため0，1，2の3状態を使用する．
//
// 【2】state == 1への辺が閉路
//   state == 1は現在探索中，つまり現在のDFS経路上にある頂点．
//   そこへ戻る辺を発見したら閉路が存在する．
//
// 【3】state == 2への辺は閉路とは限らない
//   state == 2の頂点はすでに探索を完了しているため，
//   その頂点への辺を見つけても閉路とは判定しない．
//
// 【4】グラフ全体を探索する
//   有向グラフが複数の連結部分に分かれている場合があるため，
//   すべての未探索頂点を始点としてDFSする必要がある．
//
// 【5】無向グラフの閉路検出とは方法が異なる
//   このテンプレートは有向グラフ用．無向グラフでは親への辺を考慮する必要がある．
//
// 【6】再帰の深さ
//   DFSの深さは最大O(N)になる．
//   Nが大きい場合はスタックオーバーフローに注意する．
//
// ============================================================
// 実戦用テンプレート
//
// 入力形式
// N M
// u_1 v_1
// ...
// u_M v_M
//
// u -> v の有向辺が与えられる．
// 入力の頂点番号は1～Nとし，内部では0-indexで扱う．
// 有向グラフに閉路が存在すればYes，なければNoを出力する．
// ============================================================
#if 0

vector<vector<int>> adj;
vector<int> state;

bool dfs(int v) {
    state[v] = 1;   // 探索中
    for (int nv : adj[v]) {
        if (state[nv] == 1) return true;               // 閉路を発見
        if (state[nv] == 0 && dfs(nv)) return true;    // 未探索ならDFS
    }
    state[v] = 2;   // 探索完了
    return false;
}

bool has_cycle() {
    state.assign(adj.size(), 0);
    for (int v=0; v<ssize(adj); v++) {
        if (state[v] == 0 && dfs(v)) return true;
    }
    return false;
}

int main() {
    int n, m;   cin >> n >> m;   // 点数，枝数

    adj.resize(n);
    for (int i=0; i<m; i++) {
        int u, v;   cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);      // u -> v の有向辺
    }

    cout << (has_cycle() ? "Yes" : "No") << '\n';
    return 0;
}

#endif

// ============================================================
// 学習用実行例
//
// 最初は次の閉路を持たない有向グラフを考える．
//
//       0
//      ↙ ↘
//     1   2
//      ↘ ↙ ↘
//       3   5
//       ↓
//       4
//
// 有向辺：
// 0→1，0→2，1→3，2→3，3→4，2→5
// この状態では閉路は存在しない．
//
// ここへ　4→1　を追加すると，
//     1→3→4→1
// という閉路ができる．
// ============================================================
#if 1

// main外の関数をシンプルにするために，グローバル変数を使用
vector<vector<int>> adj;    // ここでは大きさは指定しない
vector<int> state;          // 最大数指定しておく手もある

bool dfs(int v) {
    state[v] = 1;   // 現在DFSで探索中
    for (int nv : adj[v]) {
        // 現在探索中の頂点へ戻る辺を発見したら閉路
        if (state[nv] == 1)     return true;

        // 未探索の頂点なら，さらにDFSする
        if (state[nv] == 0 && dfs(nv)) return true;
    }
    state[v] = 2;   // この頂点から先の探索がすべて完了
    return false;
}

bool has_cycle() {
    // 現在の頂点数に合わせてstateを作り直し，全頂点を未探索にする
    state.assign(adj.size(), 0);

    // グラフ全体について調べる
    for (int v=0; v<ssize(adj); v++) {
        if (state[v] == 0 && dfs(v)) return true;
    }
    return false;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 6;   // 点は0～5までの6点
    vector edges{   // 有向枝
        pair{0, 1}, pair{0, 2}, pair{1, 3},
        pair{2, 3}, pair{3, 4}, pair{2, 5}
    };

    // 有向グラフを作成
    adj.resize(n);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
    }

    cout << boolalpha;      // boolの結果を true/false で表示
    cout << "===== 辺を追加する前 =====\n";
    cout << "有向辺: ";
    for (auto [u, v] : edges) {
        cout << u << "->" << v << ' ';
    }
    cout << '\n';
    cout << "閉路が存在する？: " << has_cycle() << '\n';

    cout << "\n===== 4 -> 1 を追加 =====\n";
    adj[4].push_back(1);
    cout << "閉路が存在する？: " << has_cycle() << '\n';
    cout << "1 -> 3 -> 4 -> 1 の閉路ができる\n";

    return 0;
}

#endif