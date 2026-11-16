#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// std::priority_queue まとめ
//
// 使用頻度：★★★★★
// 主な用途：最大値・最小値の高速取得，Dijkstra，貪欲法，イベント処理
// キーワード：priority_queue，最大ヒープ，最小ヒープ，
//             push，pop，top，greater，pair，tuple，比較関数
//
// 【最重要】
// priority_queue<int> pq;      // 最大ヒープ：大きい値から取り出す
// priority_queue<int, vector<int>, greater<>> pq;  // 最小ヒープ：小さい値から取り出す
// using P = pair<int, int>;
// priority_queue<P, vector<P>, greater<>> pq;      // pairの最小ヒープ
//
// push，pop：O(log N)
// top：O(1)
//
// ============================================================
// 【生成・初期化】
//
// 〇最大ヒープ
// priority_queue<int> pq1;     // 空．大きい値から取り出す
//
// vector A{5, 2, 8, 1, 4};
// priority_queue pq2(A.begin(), A.end());   // int型を推論
//
// 〇最小ヒープ
// priority_queue<int, vector<int>, greater<>> pq3;
//
// vector B{5, 2, 8, 1, 4};
// priority_queue pq4(B.begin(), B.end(), greater<int>{});  // int型を推論
//
// ============================================================
// 【主なメソッド・操作】
// priority_queue<int> pq;
//
// 〇要素の追加
//   ・pq.push(x);        // xを追加
//   ・pq.emplace(...);   // 引数から要素を直接作成
//
// 〇最優先要素の取得・削除
//   ・pq.top();          // 最優先の要素を取得
//   ・pq.pop();          // 最優先の要素を削除
//
// 〇要素数
//   ・pq.size();         // 要素数
//   ・pq.empty();        // 空ならtrue
//
// ※ top()，pop()は空のpriority_queueには使用しない．
// ※ pop()は削除するだけで，値を返さない．
//
// 値を取得してから削除する場合：
//   auto x = pq.top();
//   pq.pop();
//
// ============================================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "##### 最大ヒープ #####\n";
    vector A{5, 2, 8, 1, 4};
    priority_queue pq(A.begin(), A.end());   // int型を推論

    cout << "代入したvector A: ";
    for (auto a: A) cout << a << " ";
    cout << '\n';
    cout << "top(): " << pq.top() << '\n';
    cout << "size(): " << pq.size() << '\n';

    cout << "取り出す順番: ";
    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        cout << x << ' ';
    }
    cout << '\n';


    cout << "\n##### 最小ヒープ #####\n";
    priority_queue<int, vector<int>, greater<>> pq2;

    pq2.push(5);
    pq2.push(2);
    pq2.push(8);
    pq2.push(1);
    pq2.push(4);

    cout << "取り出す順番: ";
    while (!pq2.empty()) {
        int x = pq2.top();
        pq2.pop();
        cout << x << ' ';
    }
    cout << '\n';


    cout << "\n##### pairの最小ヒープ #####\n";
    using P = pair<int, int>;
    priority_queue<P, vector<P>, greater<>> pq3;

    pq3.push({3, 30});
    pq3.push({1, 20});
    pq3.push({2, 10});
    pq3.push({1, 10});

    cout << "取り出す順番: ";
    while (!pq3.empty()) {
        auto [a, b] = pq3.top();
        pq3.pop();
        cout << "(" << a << ", " << b << ") ";
    }
    cout << '\n';


    cout << "\n##### 独自の比較関数 #####\n";
    auto cmp = [](const P& a, const P& b) {
        // secondが大きいものを優先し，secondが同じならfirstが小さいものを優先
        if (a.second != b.second) return a.second < b.second;
        return a.first > b.first;
    };
    priority_queue<P, vector<P>, decltype(cmp)> pq4(cmp);

    pq4.push({3, 50});
    pq4.push({1, 80});
    pq4.push({2, 80});
    pq4.push({4, 30});

    cout << "取り出す順番: ";
    while (!pq4.empty()) {
        auto [id, score] = pq4.top();
        pq4.pop();
        cout << "(" << id << ", " << score << ") ";
    }
    cout << '\n';

    return 0;
}


// ============================================================
// 補足
// ============================================================
// priority_queueのテンプレート引数
//
// priority_queue<int, vector<int>, greater<>> pq;
//                ↑       ↑          ↑
//               要素型   内部コンテナ  比較方法
//
// デフォルトでは，
//   priority_queue<int>
// は概ね，
//   priority_queue<int, vector<int>, less<int>>
// と同じ意味になる．
//
// 通常の競技プログラミングでは内部コンテナをvector以外に変更する必要はほとんどない．
//
// ============================================================
// 【独自の優先順位】
//
// greater<>だけでは表せない順番にしたい場合は比較関数を使う．
//
// priority_queueでは，
//   cmp(a, b) == true
// なら，aはbより優先度が低いと考える．
//
// 例：pair<int, int>について，
//     secondが大きいものを優先し，
//     secondが同じならfirstが小さいものを優先する．
// using P = pair<int, int>;
// auto cmp = [](const P& a, const P& b) {
//     if (a.second != b.second) return a.second < b.second;
//     return a.first > b.first;
// };
// priority_queue<P, vector<P>, decltype(cmp)> pq(cmp);
//
// ※ ranges::sortなどの比較関数と同じく，
//    <=，>=ではなく，原則として<，>による厳密な比較を使う．
//
// ============================================================
// 比較関数の考え方
//
// ranges::sortの比較関数では，
//   cmp(a, b) == true
//       → aをbより前に並べる
// と考えた．
//
// priority_queueでも cmp自体の意味は同じで，
//   cmp(a, b) == true
//       → 比較順序では aより bの方が後ろ
// となる．
// priority_queueでは，この比較順序で一番後ろになる要素が top()となる．
//
// デフォルトのless<>では，
//   less<>(3, 8) == true
// なので，3より8の方が後になり，top()は最大値を獲得する．
//
// greater<>では，
//   greater<>(8, 3) == true
// なので，8より3の方が後になり，top()は最小値を獲得する．
//
// ============================================================
// top()を参照で受けてからpopしない
//
// NG：
// auto& x = pq.top();
// pq.pop();
//
// pop()によってtopの要素が削除されるため，
// xは削除された要素を参照する無効な参照になる．
//
// OK：
// auto x = pq.top();
// pq.pop();
//
// pair，tupleでも同様．
// auto [d, v] = pq.top();
// pq.pop();
//
// ============================================================
// top()の要素は直接変更できない
//
// priority_queueのtop()はconst参照を返すため，
//   pq.top() = 100;
// のように直接変更することはできない．
//
// 優先順位に使う値を変更するとヒープ構造を
// 作り直す必要があるため，直接変更できないようになっている．
//
// 値を変更したい場合は，必要に応じて
// pop()してから新しい値をpush()する．
//
// ============================================================
// priority_queueの中身を直接走査することはできない
//
// priority_queueでは，
//   pq[i]
//   pq.begin()
//   for (auto x : pq)
// のような操作はできない．
//
// 全要素を優先順位順に確認する場合は，
// top()とpop()を繰り返す必要がある．
//
// ============================================================
// push()とemplace()
//
// priority_queue<pair<int, int>> pq;
// pq.push({1, 2});
// pq.emplace(1, 2);
// どちらもpair{1, 2}を追加できる．
//
// 競プロではpush({a, b})でも十分短く，分かりやすい．
//
// ============================================================
// queue，priority_queue
//
// queue
//   FIFO
//   追加した順番に取り出す
//   BFSなどで使用
//
// priority_queue
//   優先度が高いものから取り出す
//   Dijkstra，貪欲法などで使用
//
// ============================================================