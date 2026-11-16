#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// 木DFS まとめ
//
// 使用頻度：★★★★★
// 主な用途：部分木の集計，親子関係，木DP，連結成分サイズ，木の重心
// キーワード：DFS，tree，parent，subtree，帰りがけ
//
// 【このファイル】
// ・実戦用1：再帰DFSでparentとsubtreeを求める
// ・実戦用2：非再帰DFS（stack）でparentとsubtreeを求める
// ・学習用：再帰DFSの動作確認
// ・補足：辺削除時の連結成分，帰りがけ，再帰と非再帰など
//
// parent[v]：頂点vの親．根は-1．
// subtree[v]：頂点vを根とする部分木の頂点数．
//
// 辺 parent[v]-v を削除したとき，2つの連結成分の大きさは
// subtree[v] と N-subtree[v]．
//
// 計算量：O(N)
//
// ============================================================

// ============================================================
// 【実戦用1】再帰DFS：parent＋subtree
//
// 入力形式
// N
// u_1 v_1
// ...
// u_{N-1} v_{N-1}
//
// 入力の頂点番号は1～Nの無向木とする．
// 内部では0-indexで扱う．
// ============================================================
#if 0

vector<vector<int>> adj;
vector<int> parent;
vector<int> subtree;

int dfs(int v, int p) {
    parent[v] = p;
    subtree[v] = 1;   // 自分自身
    for (int nv : adj[v]) {
        if (nv == p) continue;
        subtree[v] += dfs(nv, v);
    }
    return subtree[v];
}

int main() {
    int n;   cin >> n;
    adj.resize(n);
    parent.resize(n);
    subtree.resize(n);

    for (int i=0; i<n-1; i++) {
        int u, v;   cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0;                       // 根は問題に応じて変更
    dfs(root, -1);

    return 0;
}

#endif

// ============================================================
// 【実戦用2】非再帰DFS：stack＋parent＋subtree
//
// 再帰が深くなりそうな場合はこちらを使用する．
// 1．DFSしてparentと探索順orderを求める
// 2．orderを逆順に処理してsubtreeを親へ加える
// ============================================================
#if 0

int main() {
    int n;   cin >> n;
    vector<vector<int>> adj(n);

    for (int i=0; i<n-1; i++) {
        int u, v;   cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0;                       // 根は問題に応じて変更
    vector parent(n, -1);
    vector<int> order;

    stack<int> st;
    st.push(root);

    while (!st.empty()) {
        int v = st.top();
        st.pop();
        order.push_back(v);

        for (int nv : adj[v]) {
            if (nv == parent[v]) continue;
            parent[nv] = v;
            st.push(nv);
        }
    }

    vector subtree(n, 1);
    ranges::reverse(order);
    for (int v : order) {
        if (v == root) continue;
        subtree[parent[v]] += subtree[v];
    }

    return 0;
}

#endif

// ============================================================
// 【学習用】再帰DFS
//
// 頂点0を根として，parentとsubtreeを求める．
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
// 親・部分木サイズ：
// 頂点0：親 -1，   部分木サイズ 8
// 頂点1：親 0，    部分木サイズ 5
// 頂点2：親 0，    部分木サイズ 2
// 頂点3：親 1，    部分木サイズ 1
// 頂点4：親 1，    部分木サイズ 3
// 頂点5：親 2，    部分木サイズ 1
// 頂点6：親 4，    部分木サイズ 1
// 頂点7：親 4，    部分木サイズ 1
// ============================================================
#if 1

vector<vector<int>> adj;
vector<int> parent;  // 親
vector<int> subtree; // 根付き木における部分木の大きさ（自点含む）
vector<int> dist;    // 根からの距離

int dfs(int v, int p)
{
    parent[v] = p;
    subtree[v] = 1;
    for (int nv : adj[v])
    {
        if (nv == p)
            continue; // 親には戻らない
        dist[nv] = dist[v] + 1;
        subtree[v] += dfs(nv, v);
    }
    return subtree[v];
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 8;
    adj.resize(n);
    parent.resize(n);
    subtree.resize(n);
    dist.resize(n);

    vector edges{
        pair{0, 1}, pair{0, 2}, pair{1, 3}, pair{1, 4},
        pair{2, 5}, pair{4, 6}, pair{4, 7}};

    for (auto [u, v] : edges)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0;
    cout << "===== 木DFS =====\n";
    cout << "根: " << root << '\n';
    dfs(root, -1);

    cout << "\n===== 親・部分木サイズ =====\n";
    for (int v = 0; v < n; v++)
    {
        cout << "　頂点" << v
             << ": parent = " << parent[v]
             << "，subtree = " << subtree[v]
             << ", distance = " << dist[v] << '\n';
    }

    return 0;
}

#endif

// ============================================================
// 補足
// ============================================================
// 辺を削除したときの2つの連結成分
//
// 根を決めると，各辺は parent[v]-v の形で親子関係を持つ．
// この辺を削除すると，
//
//   子v側：subtree[v]
//   根側  ：N-subtree[v]
//
// となる．各辺を1回ずつ調べるなら，根以外の各頂点vを見ればよい．
//
// for (int v=0; v<n; v++) {
//     if (v == root) continue;
//     int child_side = subtree[v];
//     int root_side = n - subtree[v];
//     // 辺 parent[v]-v を削除したときの2成分
// }
//
// 元のedgesを順番どおり調べたい場合は，子側を判定する．
//
// for (auto [u, v] : edges) {
//     int c = (parent[u] == v ? u : v);
//     int child_side = subtree[c];
//     int root_side = n - subtree[c];
// }
//
// ============================================================
// 木の重心
//
// 頂点vを取り除いたとき，残るすべての連結成分の大きさが
// N/2以下となるような頂点vを「木の重心」という．
//
// 木の重心は必ず存在し，1個または2個．点数奇数ならば常に1個．
//
// 根付き木としてparent，subtreeを求めておけば，頂点vを除いたとき，
// ・子c側の連結成分：subtree[c]
// ・親側の連結成分  ：N-subtree[v]
// となる．したがって，
//   すべての子cについて subtree[c] <= N/2
//   かつ N-subtree[v] <= N/2
// を満たす頂点vが重心．
//
// vector<int> centroid;
// for (int v=0; v<n; v++) {
//     bool ok = (n - subtree[v] <= n/2);
//     for (int nv : adj[v]) {
//         if (parent[nv] == v && subtree[nv] > n/2) ok = false;
//     }
//     if (ok) centroid.push_back(v);
// }
//
// 計算量：O(N)
//
// ============================================================
// 木DFSの基本
//
// 木は根を1つ決めることで，親子関係を持つ根付き木として扱える．
// 部分木とは，ある頂点とそのすべての子孫からなる部分を表す．
// したがって，parentやsubtreeは選んだ根によって変わる．
//
// 無向木では辺を両方向に登録するため，親への辺もadj[v]に含まれる．
//
// if (nv == p) continue;
//
// として親へ戻る辺だけを除外すればよく，visitedは必要ない．
//
// ============================================================
// 帰りがけの処理
//
// 子のDFSが終了すると，その子の計算結果が親へ返ってくる．
// その結果を集計することで，部分木の情報などを求められる．
//
// subtree[v] = 1;              // 自分自身
// subtree[v] += dfs(nv, v);    // 子の部分木サイズを加える
//
// ============================================================
// 再帰DFSと非再帰DFS
//
// 再帰DFS
// ・コードが短く，帰りがけの処理を書きやすい．
// ・木が一直線に近い場合，再帰が深くなりスタックオーバーフローに注意．
//
// 非再帰DFS
// ・stackを自分で管理するため，再帰の深さを気にしなくてよい．
// ・部分木サイズは，探索順orderを逆順に処理して子から親へ加える．
//
// ============================================================
// 一般グラフではparentだけでは不十分
//
// 木では閉路がないため，親へ戻る辺だけ除外すればよい．
// 一般グラフではvisitedなどによる訪問済み判定が必要．
//
// ============================================================
