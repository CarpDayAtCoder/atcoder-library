#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;


// ============================================================
// AC-Library DSU（Union-Find）テンプレート
//
// 使用頻度：★★★★★
// 主な用途：無向グラフの連結判定・連結成分管理
// キーワード：merge，same，leader，size，groups
//
// dsu uf(n);
//   頂点0～n-1を持つDSUを作成する．
//
// uf.merge(a, b);
//   頂点aと頂点bが属する連結成分を結合する．
//   戻り値は，結合後の連結成分の代表元．
//
// uf.same(a, b);
//   頂点aと頂点bが同じ連結成分ならtrue，異なるならfalse．
//
// uf.leader(a);
//   頂点aが属する連結成分の代表元を返す．
//   直近の親ではなく，連結成分全体の代表元である．
//   代表元が最小頂点などになる保証はない．
//
// uf.size(a);
//   頂点aが属する連結成分の頂点数を返す．
//
// uf.groups();
//   すべての連結成分を vector<vector<int>> で返す．
//   連結成分の順番，各連結成分内の頂点の順番は保証されない．
//
// 【注意】
// DSUが扱う頂点番号は0～n-1．
// 入力が1～nなら，入力後にu--，v--とする．
// 頂点番号が飛び飛びなら，別途0～n-1へ座標圧縮する．
//
// ============================================================

// ============================================================
// 実戦用テンプレート
//
// 入力された無向グラフについて，辺をすべてDSUへ追加する．
// ============================================================
#if 0

#include <atcoder/dsu>
using namespace atcoder;

int main() {
    int n, m;   cin >> n >> m;

    dsu uf(n);                         // 頂点0～n-1を作成

    for (int i=0; i<m; i++) {
        int u, v;   cin >> u >> v;
        u--, v--;                      // 入力が1-indexの場合
        uf.merge(u, v);                // uとvを結合
    }

    int a, b;   cin >> a >> b;
    a--, b--;

    bool is_same = uf.same(a, b);      // aとbが連結しているか
    int root = uf.leader(a);           // aの連結成分の代表元
    int component_size = uf.size(a);   // aの連結成分の大きさ

    auto groups = uf.groups();         // すべての連結成分
    int component_count = ssize(groups); // 連結成分数

    return 0;
}

#endif


// ============================================================
// 学習用実行例
// ============================================================
#if 1

#include <atcoder/dsu>
using namespace atcoder;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 7;                         // 頂点は0～6
    dsu uf(n);                         // 最初は全頂点が別々の連結成分

    cout << boolalpha;                 // boolをtrue，falseで表示
    cout << "===== 初期状態 （" << n << "点独立状態） =====\n";

    cout << "\n===== merge()による頂点の結合 =====\n";
    uf.merge(0, 1);                    // {0}と{1}を結合
    uf.merge(2, 3);                    // {2}と{3}を結合
    uf.merge(4, 5);                    // {4}と{5}を結合
    cout << "　頂点0-1，2-3，4-5を結合\n";

    cout << "\n===== same()による連結判定 =====\n";
    cout << "　頂点0と頂点1は連結？: "
         << uf.same(0, 1) << '\n';
    cout << "　頂点0と頂点4は連結？: "
         << uf.same(0, 4) << '\n';

    cout << "\n===== leader()による代表元の取得 =====\n";
    cout << "　頂点0が属する連結成分の代表元: 頂点"
         << uf.leader(0) << '\n';
    cout << "　頂点3が属する連結成分の代表元: 頂点"
         << uf.leader(3) << '\n';

    cout << "\n===== さらに結合 =====\n";
    uf.merge(0, 2);                    // {0, 1}と{2, 3}を結合
    uf.merge(5, 6);                    // {4, 5}と{6}を結合
    cout << "　頂点0-2，5-6を結合\n";

    cout << "\n===== size()による連結成分の大きさ =====\n";
    cout << "　頂点0を含む連結成分の大きさ: "
         << uf.size(0) << '\n';
    cout << "　頂点4を含む連結成分の大きさ: "
         << uf.size(4) << '\n';

    cout << "\n===== groups()による全連結成分の取得 =====\n";
    auto components = uf.groups();
    cout << "　現在の連結成分数: "
         << components.size() << '\n';
    for (int i=0; i<ssize(components); i++) {
        cout << "　　連結成分" << i << ": ";
        for (int v : components[i]) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}
#endif

// ============================================================
// 連結成分の頂点一覧も管理する場合
//
// AC-Libraryのdsuは，各連結成分の頂点一覧を返すメソッドを持たない．
// 必要な場合は，DSUと並行して各代表元の頂点一覧を管理する．
//
// dsu uf(n);
// vector<vector<int>> member(n);
// for (int i=0; i<n; i++) member[i] = {i};
//
// int ru = uf.leader(u), rv = uf.leader(v);
// if (ru != rv) {
//     // merge前なら，member[ru]，member[rv]がそれぞれの連結成分
//     for (int a : member[ru]) {
//         for (int b : member[rv]) {
//             // compo(u) × compo(v) の処理
//         }
//     }
//
//     int r = uf.merge(ru, rv);          // 結合後の代表元
//     int old = (r == ru ? rv : ru);
//
//     // 小さいvectorを大きいvectorへ追加する
//     if (member[r].size() < member[old].size())  swap(member[r], member[old]);
//     member[r].insert(member[r].end(), member[old].begin(), member[old].end());
//     member[old].clear();
// }
//
// member[uf.leader(v)] が，現在vが属する連結成分の頂点一覧になる．
// ============================================================