#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// グラフBFSテンプレート
//
// 使用頻度：★★★★★
// 主な用途：重みなしグラフの最短距離，到達可能判定
// キーワード：BFS，graph，queue，dist，隣接リスト
//
// 【基本】
// dist[v] == -1：未訪問，または始点から到達できない
// dist[v] >= 0 ：始点から頂点vまでの最短距離
//
// BFSでは，各辺の移動コストがすべて同じ場合に最短距離を求められる．
// 無向グラフ，有向グラフのどちらでも使用できる．
//
// 【計算量】
// 隣接リストを使用する場合O(N + M)．
//
// ============================================================
// 注意
// 【1】queueへ追加する時点でdistを更新する．
//     dist[nv] = dist[v] + 1;
//     que.push(nv);
//   取り出した時点で更新すると，同じ頂点が複数回queueへ入ることがある．
//
// 【2】無向グラフと有向グラフ
//   無向グラフ： 両方向分，データを追加する．
//     adj[u].push_back(v);
//     adj[v].push_back(u);
//   有向グラフ： 片方向分，データを追加する．
//     adj[u].push_back(v);
//
// ============================================================
// 複数始点BFS
//
// 複数の始点すべてについて，最初にdist = 0としてqueueへ入れる．
// for (...) {
//     dist[s] = 0;
//     que.push(s);
// }
// その後のBFS処理は通常のBFSと同じ．
//
// ============================================================
// 木の場合
//
// 木でも通常のグラフBFSをそのまま使用できる．
// distによる訪問済み判定を残して問題ない．
//
// 木では閉路がないため，親parentを覚えて
//     if (nv == parent) continue;
// と判定する方法もある．
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
// 入力の頂点番号は1～Nの無向グラフとする．
// 内部では0-indexで扱う．
// 始点sから各頂点への最短距離を求める．
// ============================================================
#if 0

int main() {
    int n, m;   cin >> n >> m;      // 点数，枝数

    vector<vector<int>> adj(n);
    for (int i=0; i<m; i++) {
        int u, v;   cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);        // 有向グラフなら，この行は削除
    }

    vector dist(n, -1);
    queue<int> que;

    int s = 0;   // 始点の設定は，問題に応じて変更
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();

        for (int nv : adj[v]) {
            if (dist[nv] != -1) continue;   // 訪問済み
            dist[nv] = dist[v] + 1;
            que.push(nv);
        }
    }
    return 0;
}
#endif

// ============================================================
// 学習用実行例
//
// 次の無向グラフについて，頂点0から各頂点への最短距離を求める．
//
//     0 --- 1 --- 3
//     |     |
//     2 --- 4 --- 5
//
//     6   ← 孤立した頂点
//
// 辺：
// 0-1，0-2，1-3，1-4，2-4，4-5
//
// 最短距離：
// 頂点0 → 0
// 頂点1 → 1
// 頂点2 → 1
// 頂点3 → 2
// 頂点4 → 2
// 頂点5 → 3
// 頂点6 → -1（到達不能）
// ============================================================
#if 1

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 7;  // 点は0～6までの7点
    vector<vector<int>> adj(n);
    vector edges{
        pair{0, 1}, pair{0, 2}, pair{1, 3},
        pair{1, 4}, pair{2, 4}, pair{4, 5}
    };

    // 無向グラフを作成
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector dist(n, -1);
    queue<int> que;

    int s = 0;      // 始点
    dist[s] = 0;    // 始点から始点への距離＝0
    que.push(s);    // 始点をqueueへ追加

    while (!que.empty()) {
        int v = que.front();   // queueの先頭要素を取得
        que.pop();             // queueの先頭要素を削除

        for (int nv : adj[v]) {
            if (dist[nv] != -1) continue;   // 訪問済み
            dist[nv] = dist[v] + 1;         // 始点からの最短距離を確定
            que.push(nv);                   // queueへ追加
        }
    }

    cout << "===== グラフ =====\n";
    cout << "辺: ";
    for (auto [u, v] : edges) {
        cout << u << '-' << v << ' ';
    }
    cout << '\n';

    cout << "\n===== 始点からの最短距離 =====\n";
    cout << "始点: " << s << '\n';
    for (int v=0; v<n; v++) {
        cout << "　頂点" << v << ": " << dist[v] << '\n';
    }
    return 0;
}

#endif