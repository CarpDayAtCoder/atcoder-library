#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// std::queue / std::deque まとめ
//
// 使用頻度：★★★★★
// 主な用途：FIFO，BFS，両端からの要素追加・削除，0-1 BFS
// キーワード：queue，deque，push，pop，front，back，
//             push_front，push_back，pop_front，pop_back
//
// 【基本】
// queue<int> que;    // FIFO．先に入れた要素から取り出す
// deque<int> dq;     // 前後どちらからでも追加・削除できる
//
// 通常のBFS → queue
// 0-1 BFS   → deque
//
// ============================================================
// 【生成・初期化】
//
// 〇queue
//
// queue<int> que1;                         // 空のqueue
//
// C++23では，イテレータ範囲からまとめて初期化できる．
// vector<int> A{10, 20, 30};
// queue que2(A.begin(), A.end());      // 10, 20, 30の順．int型を推論
//
// ※ dequeのように，要素数や各要素を直接指定する
//    queue<int> que(n, -1);
//    queue<int> que{1, 2, 3};
//    のような初期化はできない．
//
// 〇deque
//
// deque<int> dq1;              // 空，size = 0
// deque<int> dq2(n);           // n要素，全要素0
// deque dq3(n, 0LL);           // n要素，全要素0．longlong型を推論
// deque dq4{1, 2, 3, 4, 5};    // 各要素を指定．int型を推論
//
// ============================================================
// 【queueの主なメソッド・操作】
// queue<int> que;
//
// 〇要素の追加・削除
//   ・que.push(x);       // xを末尾に追加
//   ・que.emplace(...);  // 引数から要素を直接作成
//   ・que.pop();         // 先頭要素を削除
//
// 〇要素の取得
//   ・que.front();       // 先頭要素
//   ・que.back();        // 末尾要素
//
// 〇要素数
//   ・que.size();        // 要素数
//   ・que.empty();       // 空ならtrue
//
// ※ front()，back()，pop()は空のqueueには使用しない．
//
// ============================================================
// 【dequeの主なメソッド・操作】
// deque<int> dq;
//
// 〇前後への追加
//   ・dq.push_front(x);       // 先頭にxを追加
//   ・dq.push_back(x);        // 末尾にxを追加
//   ・dq.emplace_front(...);  // 先頭に要素を直接作成
//   ・dq.emplace_back(...);   // 末尾に要素を直接作成
//
// 〇前後から削除
//   ・dq.pop_front();         // 先頭要素を削除
//   ・dq.pop_back();          // 末尾要素を削除
//
// 〇要素アクセス
//   ・dq[i]                   // i番目の要素
//   ・dq.front()              // 先頭要素
//   ・dq.back()               // 末尾要素
//
// 〇要素数
//   ・dq.size()               // 要素数
//   ・dq.empty()              // 空ならtrue
//
// 〇全要素を削除
//   ・dq.clear();
//
// 〇イテレータ
//   ・dq.begin()
//   ・dq.end()
//   ・dq.rbegin()
//   ・dq.rend()
//
// ※ front()，back()，pop_front()，pop_back()は
//    空のdequeには使用しない．
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "##### queue #####\n";
    vector A{10, 20, 30};
    queue que(A.begin(), A.end());  // まとめてqueueに追加

    cout << "vector A{10, 20, 30}からqueueを作成\n";
    cout << "front(): " << que.front() << '\n';
    cout << "back(): " << que.back() << '\n';
    cout << "size(): " << que.size() << '\n';

    cout << "空になるまで削除する．削除する順番: ";
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        cout << x << ' ';
    }
    cout << '\n';

    cout << "\n##### deque #####\n";
    deque<int> dq;

    cout << "後ろから20, 前から10, 後ろから30をこの順にdequeへ追加する\n";
    dq.push_back(20);
    dq.push_front(10);
    dq.push_back(30);

    cout << "dq: ";
    for (int x : dq) cout << x << ' ';
    cout << '\n';
    cout << "front(): " << dq.front() << '\n';
    cout << "back(): " << dq.back() << '\n';

    dq.pop_front();
    cout << "pop_front()後: ";
    for (int x : dq) cout << x << ' ';
    cout << '\n';

    dq.pop_back();
    cout << "pop_back()後: ";
    for (int x : dq) cout << x << ' ';
    cout << '\n';


    cout << "\n===== dequeの添字アクセス =====\n";
    deque dq2{10, 20, 30, 40, 50};
    cout << "dq2: ";
    for (int x : dq2) cout << x << ' ';
    cout << '\n';
    cout << "dq2[2]: " << dq2[2] << '\n';

    return 0;
}

// ============================================================
// 補足
// ============================================================
// queueとdeque
//
// 【queue】
//   ・FIFOの操作だけを行う
//   ・末尾にpush()し，先頭からpop()する
//   ・添字アクセスやrange-forはできない
//   ・BFSなどで使用
//
// 【deque】
//   ・前後両方から追加・削除できる
//   ・添字アクセス可能
//   ・range-for可能
//   ・0-1 BFSなどで使用
//
// ============================================================
// FIFO（First In First Out）
//
// queueは，最初に追加した要素を最初に取り出す．
//       front               back
//         ↓                   ↓
//       [ 1 ][ 2 ][ 3 ]
//         ↑                   ↑
//        pop                 push
//
// 例えば，
//   que.push(1);
//   que.push(2);
//   que.push(3);
// とすると，pop()で削除する順番は
//   1 → 2 → 3
// となる．
//
// ============================================================
// BFSとqueue
//
// BFSでは，これから処理する頂点をqueueに保存する．
// queue<int> que;
// que.push(s);
//
// while (!que.empty()) {
//     int v = que.front();
//     que.pop();
//     for (int nv : adj[v]) {
//         ...
//         que.push(nv);
//     }
// }
//
// queueは先に追加した頂点から処理するため，
// 始点から近い頂点を順番に探索するBFSに適している．
// 各辺のコストが同じグラフの最短距離などで使用する．
//
// ============================================================
// 0-1 BFSとdeque
//
// 0-1 BFSでは，辺のコストが0または1の場合にdequeを使う．
// deque<int> dq;
//
// コスト0の辺を通った場合：
//   dq.push_front(nv);
// コスト1の辺を通った場合：
//   dq.push_back(nv);
//
// 距離が小さい頂点を先に処理することで，最短距離を効率よく求めることができる．
//
// ============================================================
// front()を参照で受けてからpopしない
//
// NG：
// auto& x = que.front();   // 参照受け
// que.pop();
//
// pop()によって先頭要素が削除されるため，
// xは削除された要素を参照する無効な参照になる．
//
// OK：
// auto x = que.front();    // コピー
// que.pop();
//
// dequeでも同様：
// auto x = dq.front();
// dq.pop_front();
//
// ============================================================
// push()とemplace()
//
// queue<pair<int, int>> que;
// que.push({1, 2});
// que.emplace(1, 2);
//
// どちらもpair{1, 2}を末尾へ追加できる．
//
// deque<pair<int, int>> dq;
// dq.push_back({1, 2});
// dq.emplace_back(1, 2);
//
// 競プロではpush({a, b})，push_back({a, b})でも
// 十分短く，分かりやすい．
//
// ============================================================
// queueの中身を直接走査することはできない
//
// queueでは，
//   que[i]
//   que.begin()
//   for (auto x : que)
// のような操作はできない．
//
// 基本的にはfront()で先頭要素だけを取得し，pop()しながら処理する．
//
// 一方，dequeは
//   dq[i]
//   dq.begin()
//   for (auto x : dq)
// のような操作ができる．
//
// ============================================================
// stack，queue，deque
//
// stack
//   LIFO
//   最後に入れた要素を最初に取り出す
//   DFSで使用
//
// queue
//   FIFO
//   最初に入れた要素を最初に取り出す
//   BFSで使用
//
// deque
//   前後両方から追加・削除できる
//   0-1 BFSなどで使用
//
// ============================================================
// at()による範囲チェック
//
// dq.at(i)は，i番目の要素へアクセスする．
// dq[i]と異なり，範囲外ならout_of_range例外を投げる．
//
// deque<int> dq{10, 20, 30};
//
// dq[1];      // 20．範囲チェックなし
// dq.at(1);   // 20．範囲チェックあり
// dq.at(5);   // 範囲外なので例外
//
// 競プロでは通常dq[i]を使うことが多い．
//
// ============================================================
// queueの内部コンテナ
//
// std::queueは，別のコンテナを利用してFIFOの操作だけを
// 公開する「コンテナアダプタ」．
//
// queue<int> que;
// と書いた場合，内部ではデフォルトでdeque<int>が使用される．
//
// 通常の競技プログラミングでは
// queue<int>とだけ書けば十分．
//
// ============================================================