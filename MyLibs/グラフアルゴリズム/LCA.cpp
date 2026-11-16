#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
#define rep(i, a, b) for (int i=(a); i<(b); i++)
template <class T>
void pr(const T& x) { cout << x << '\n'; }

// ============================================================
// LCA（最近共通祖先）まとめ
//
// 使用頻度：★★★☆☆
// 主な用途：最近共通祖先，2頂点間距離，木上のパス
// キーワード：LCA，ダブリング，ancestor，depth
//
// 【このファイル】
// ・実戦用：ダブリングによるLCA
// ・学習用：小さな木でLCA・距離を確認
// ・補足：ダブリング，LCAの求め方，2頂点間距離
//
// LCA lca(adj, root);
// lca.query(u, v);       // uとvのLCA
// lca.get_dist(u, v);    // uとvの距離（辺の本数）
//
// depth[v]：根から頂点vまでの深さ
// up[k][v]：頂点vから2^k個上の祖先
//
// 前処理：O(N log N)
// query：O(log N)
// get_dist：O(log N)
// メモリ：O(N log N)
//
// 頂点番号は0-indexの無向木とする．
//
// ============================================================
struct LCA {
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> up;

    LCA(vector<vector<int>>& adj, int root = 0) {
        n = ssize(adj);     // n: 点数

        LOG = 1;
        while ((1LL << LOG) <= n) LOG++;    // LOG: nのビット数

        depth.assign(n, 0);                 // 根からの深さ
        up.assign(LOG, vector<int>(n));
        dfs(root, root, adj);               // depthとup[0][v]を作成

        // up[k][v]：vから2^k個上の祖先
        for (int k=1; k<LOG; k++) {
            for (int v=0; v<n; v++) {
                up[k][v] = up[k-1][up[k-1][v]]; // ダブリング
            }
        }
    }

    void dfs(int v, int p, vector<vector<int>>& adj) {
        up[0][v] = p;               // vの1つ上はp
        for (int nv : adj[v]) {
            if (nv == p) continue;
            depth[nv] = depth[v] + 1;   // 深さ
            dfs(nv, v, adj);
        }
    }

    // uとvの最近共通祖先
    int query(int u, int v) {
        // uを深い方にする
        if (depth[u] < depth[v]) swap(u, v);

        // uの深さを，vの深さに揃える
        int diff = depth[u] - depth[v];
        for (int k=0; k<LOG; k++) {
            if ((diff >> k) & 1) u = up[k][u];
        }
        if (u == v) return u;   // LCA確定

        // LCAの直下まで同時に上げる
        for (int k=LOG-1; k>=0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];    // すぐ上がLCA
    }

    // uとvの距離（辺の本数）
    int get_dist(int u, int v) {
        int w = query(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};

#if 0

int main() {
    int n, q;   cin >> n >> q;
    vector<vector<int>> adj(n);

    rep(i, 0, n-1) {
        int u, v;   cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0;                       // 根は問題に応じて変更
    LCA lca(adj, root);

    while (q--) {
        int u, v;   cin >> u >> v;
        u--, v--;

        int w = lca.query(u, v);
        pr(w + 1);

        // 2頂点間距離を求める場合
        // pr(lca.get_dist(u, v));
    }

    return 0;
}

#endif
// ============================================================
// 【学習用】LCA
//
// 頂点0を根とする．
//
//         0
//       ┌─┴─┐
//       1   2
//     ┌─┴─┐ └─┐
//     3   4   5
//       ┌─┴─┐
//       6   7
//
// 辺：
// 0-1，0-2，1-3，1-4，2-5，4-6，4-7
//
// LCA(6,7) = 4
// LCA(3,6) = 1
// LCA(5,7) = 0
//
// dist(6,7) = 2
// dist(3,6) = 3
// dist(5,7) = 5
// ============================================================
#if 1

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 8;
    vector<vector<int>> adj(n);

    vector edges{
        pair{0, 1}, pair{0, 2}, pair{1, 3}, pair{1, 4},
        pair{2, 5}, pair{4, 6}, pair{4, 7}};

    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0;
    LCA lca(adj, root);

    cout << "===== LCA =====\n";
    cout << "LCA(6, 7) = " << lca.query(6, 7) << '\n';
    cout << "LCA(3, 6) = " << lca.query(3, 6) << '\n';
    cout << "LCA(5, 7) = " << lca.query(5, 7) << '\n';

    cout << "\n===== 距離 =====\n";
    cout << "dist(6, 7) = " << lca.get_dist(6, 7) << '\n';
    cout << "dist(3, 6) = " << lca.get_dist(3, 6) << '\n';
    cout << "dist(5, 7) = " << lca.get_dist(5, 7) << '\n';

    cout << "\n===== depth =====\n";
    for (int v=0; v<n; v++) {
        cout << "頂点" << v << ": depth = " << lca.depth[v] << '\n';
    }

    return 0;
}

#endif

// ============================================================
// ダブリング
//
// up[k][v] は，頂点vから2^k個上の祖先を表す．
//
// up[0][v]：1個上
// up[1][v]：2個上
// up[2][v]：4個上
// up[3][v]：8個上
// ...
//
// 2^(k-1)個上へ2回進めば2^k個上なので，
//
// up[k][v] = up[k-1][ up[k-1][v] ]
//
// と求められる．
//
// 根rootについては
//
// up[0][root] = root
//
// としている．
// そのため，根より上へ移動しようとしてもrootのままとなり，
// -1などの特別処理が不要になる．
//
// ============================================================
// LCAの求め方
//
// 1．u，vの深さをそろえる
//
// 深い方の頂点を，深さの差だけ上へ移動する．
// 1個ずつ移動するのではなく，差を2進数で考えて
// up[k]を使うことでO(log N)で移動できる．
//
// 例：深さの差が13の場合
//
// 13 = 8 + 4 + 1
//
// なので，8個上，4個上，1個上へ移動すればよい．
//
// 2．LCAの直下までu，vを同時に上げる
//
// 大きなkから順に見て，
//
// up[k][u] != up[k][v]
//
// なら，そこまで上がってもまだLCAを飛び越えていないので，
//
// u = up[k][u]
// v = up[k][v]
//
// とする．
//
// 最後にはuとvがLCAの直下にいるので，
//
// up[0][u]
//
// がLCAとなる．
//
// ============================================================
// 2頂点間の距離
//
// w = LCA(u,v) とすると，
//
// root
//   |
//   w
//  / \
// u   v
//
// rootからuまでの距離 depth[u] と
// rootからvまでの距離 depth[v] には，
// rootからwまでの部分が2回含まれている．
//
// したがって，
//
// dist(u,v)
//   = depth[u] + depth[v] - 2*depth[w]
//
// となる．
//
// ============================================================
// 再帰DFSについて
//
// このテンプレートでは前処理に再帰DFSを使用している．
// 木が一直線に近く，再帰が非常に深くなる問題では
// スタックオーバーフローに注意する．
//
// 必要なら，depthとup[0]を求める部分だけ
// stackを使った非再帰DFSに置き換えればよい．
// LCAのダブリング部分はそのまま使用できる．
//
// ============================================================