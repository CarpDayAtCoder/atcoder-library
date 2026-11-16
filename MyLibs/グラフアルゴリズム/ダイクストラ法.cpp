#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// ダイクストラ法テンプレート
//
// 使用頻度：★★★★★
// 主な用途：重み付きグラフの単一始点最短距離
// キーワード：ダイクストラ，最短距離，priority_queue，隣接リスト
//
// 【使用条件】
//   辺の重みがすべて0以上であること．負の重みを含むグラフには使用できない．
//
// 【計算量】
//   O((V + E) log V)．V：頂点数，E：辺数
//
// 【隣接リスト】
//   vector<vector<pair<int, ll>>> adj(n);
//   adj[u] に {v, cost} を格納する．
//
//   無向グラフ：
//     adj[u].push_back({v, cost});
//     adj[v].push_back({u, cost});
//
//   有向グラフ：
//     adj[u].push_back({v, cost});
//
// 【priority_queue】
//   template<class T>
//   using minpq = priority_queue<T, vector<T>, greater<T>>;
//   using P = pair<ll, int>;  // {距離, 頂点}
//   minpq<P> que;
//
//   小さいpairから取り出す最小ヒープ．
//   pairはfirst，secondの順に比較されるため，距離が小さいものが優先される．
//
//   que.push({dist, v});   // 追加
//   que.top();             // 最小要素を取得（削除はしない）
//   que.pop();             // 最小要素を削除
//   que.empty();           // 空ならtrue
//
// 【dist】
//   dist[v]：始点startから頂点vまでの最短距離
//   到達できない頂点はLINFのまま．
//
// ============================================================


// ============================================================
// 実戦用テンプレート
// ============================================================
#if 1

using ll = long long;
constexpr ll LINF = 1LL << 60;
template<class T>
using minpq = priority_queue<T, vector<T>, greater<T>>; // 最小ヒープ

int main() {
    int n, m;   cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n);  // adj[u] = {v, cost}
    for (int i=0; i<m; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        u--;    v--;

        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});       // 有向グラフなら削除
    }

    int start = 0;              // 始点の設定
    vector dist(n, LINF);       // 頂点数を指定．0-index
    dist[start] = 0;

    using P = pair<ll, int>;               // {距離, 頂点}
    minpq<P> que;   // 小さい要素優先のキュー
    que.push({0, start});

    while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (dist[u] < d) continue;         // 古い情報なら無視
        for (auto [v, cost] : adj[u]) {
            ll nd = d + cost;
            if (nd < dist[v]) {
                dist[v] = nd;
                que.push({nd, v});
            }
        }
    }

    // dist[v]：startからvまでの最短距離

    return 0;
}

#endif


// ============================================================
// 学習用実行例
// ============================================================
#if 1

using ll = long long;
constexpr ll LINF = 1LL << 60;
template<class T>
using minpq = priority_queue<T, vector<T>, greater<T>>; // 最小ヒープ

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    //  |V|=4, |E|=5 の無向グラフ
    //       2
    //   0 ----- 1
    //   |       |
    //  5|       |1
    //   |       |
    //   2 ----- 3
    //       2
    //
    // さらに 0 - 3 間にコスト10の辺がある．

    // 無向ネットワークの構築
    int n = 4;
    vector<vector<pair<int, ll>>> adj(n);
    auto add_edge = [&](int u, int v, ll cost) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    };
    add_edge(0, 1, 2);
    add_edge(0, 2, 5);
    add_edge(1, 3, 1);
    add_edge(2, 3, 2);
    add_edge(0, 3, 10);

    // 前処理
    int start = 0;
    vector dist(n, LINF);
    dist[start] = 0;
    using P = pair<ll, int>;               // {距離, 頂点}
    minpq<P> que;   // 小さい要素優先のキュー
    que.push({0, start});

    cout << "===== ダイクストラ法 =====\n";
    cout << "　始点: " << start << '\n';
    while (!que.empty()) {
        auto [d, u] = que.top();    // キューの先頭から1つ獲得
        que.pop();                  // キューから削除
        cout << "\n頂点" << u << "，距離" << d
             << " をpriority_queueから取得\n";
        if (dist[u] < d) {
            cout << "　→ 古い情報なので無視\n";
            continue;
        }
        // 最短距離が確定した点uから，隣接する点vへの距離をキューに格納
        for (auto [v, cost] : adj[u]) {
            ll nd = d + cost;
            if (nd < dist[v]) {     // 始点からの距離が短くなるなら
                cout << "　頂点" << v << ": ";
                if (dist[v] == LINF) cout << "INF";
                else                 cout << dist[v];
                cout << " → " << nd << '\n';
                dist[v] = nd;   // 距離を更新
                que.push({nd, v});     // キューに追加
            }
        }
    }
    cout << "\n===== 最短距離 =====\n";
    for (int v=0; v<n; v++) {
        cout << "　0 → " << v << ": " << dist[v] << '\n';
    }
    return 0;
}

#endif