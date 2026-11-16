#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// AC-Library Fenwick Tree（BIT：Binary Indexed Tree）テンプレート
//
// 使用頻度：★★★★☆
// 主な用途：一点加算，累積和・区間和の取得
// キーワード：add，sum，BIT，Fenwick Tree，累積和
//
// 【特徴】
// 一点加算と区間和に特化したデータ構造．
// Segment Treeより機能は少ないが，合計だけ扱う場合はシンプルで軽い．
//
// fenwick_tree<T> fw(n);
//   長さnのFenwick Treeを作成する．初期状態では全要素が0．
//   segtree<ll, op, e> st(A); のようにvectorを直接渡すコンストラクタはない．
//   作成後に各要素に対して fw.add(p, A[p]); する．
//
// fw.add(p, x);
//   A[p] += x を行う．「A[p]をxに変更」ではないことに注意．
//   計算量 O(log N)．
//
// fw.sum(l, r);
//   半開区間A[l:r)，すなわちA[l]～A[r-1]の合計を返す．
//   l == r の場合は0を返す．計算量 O(log N)．
//
// fw.sum(0, r);
//   A[0:r)，すなわち先頭からA[r-1]までの累積和を返す．
//   計算量 O(log N)．
//
// fw.sum(p, p + 1);
//   A[p]の現在値を取得できる．専用のget()はない．
//   計算量 O(log N)．
//
// ============================================================
// Segment Treeとの主な違い
// ============================================================
// 【Fenwick Tree】
//   ・基本的に「合計」に特化．
//   ・一点更新は add(p, x)，つまり加算．
//   ・区間和を O(log N) で取得．
//   ・コード・内部構造が比較的シンプル．
//
// 【Segment Tree】
//   ・合計だけでなく最大値，最小値，gcdなども扱える．
//   ・set(p, x)で値そのものを変更できる．
//   ・max_right，min_leftによる境界探索も可能．
//
// 合計だけ必要
//   → Fenwick Treeが有力．
// 最大値・最小値なども必要
//   → Segment Tree．
//
// ============================================================


// ============================================================
// 実戦用テンプレート
//
// 入力形式
// N Q
// A_0 A_1 ... A_{N-1}
//
// クエリ
// type = 1：A[p] += x
// type = 2：A[l:r)の合計を出力
//
// 添字は0-index．
// ============================================================
#if 0
#include <atcoder/fenwicktree>
using namespace atcoder;
using ll = long long;

int main() {
    int n, q;   cin >> n >> q;
    fenwick_tree<ll> fw(n);

    // 初期値をBITへ登録
    for (int i=0; i<n; i++) {
        ll x;   cin >> x;
        fw.add(i, x);
    }

    while (q--) {
        int type;   cin >> type;

        if (type == 1) {
            int p;
            ll x;
            cin >> p >> x;
            fw.add(p, x);                 // A[p] += x
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << fw.sum(l, r) << '\n'; // A[l:r)の合計
        }
    }
    // その他の主な処理
    ll prefix = fw.sum(0, 3);      // A[0:3)の累積和
    ll value = fw.sum(1, 2);       // A[1]の現在値

    // A[1]を10へ「変更」する場合
    ll x = 10;
    fw.add(1, x - fw.sum(1, 2));

    return 0;
}
#endif

// ============================================================
// 学習用実行例
// ============================================================
#if 1

#include <atcoder/fenwicktree>
using namespace atcoder;
using ll = long long;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 5;
    cout << "#### 要素数を指定して初期化 ####\n";
    fenwick_tree<ll> fw(n);
    cout << "　長さ5のFenwick Treeを作成\n";
    cout << "　初期状態では全要素が0\n";

    cout << "\n===== add()による一点加算 =====\n";
    fw.add(0, 5);   // A[0] += 5
    fw.add(1, 2);   // A[1] += 2
    fw.add(2, 3);   // A[2] += 3
    fw.add(3, 4);   // A[3] += 4
    fw.add(4, 5);   // A[4] += 5
    cout << "　A = {5, 2, 3, 4, 5} の状態にする\n";

    cout << "\n===== sum()による区間和 =====\n";
    // A[1:4) = {2, 3, 4}
    cout << "　A[1:4)の合計: " << fw.sum(1, 4) << '\n';

    cout << "\n===== sum(0, r)による累積和 =====\n";
    // A[0:3) = {5, 2, 3}
    cout << "　A[0:3)の累積和: " << fw.sum(0, 3) << '\n';

    cout << "\n===== 一点の値を取得 =====\n";
    // A[2:3) = {3}
    cout << "　A[2]の値: " << fw.sum(2, 3) << '\n';

    cout << "\n===== add()でさらに加算 =====\n";
    fw.add(2, 10);  // A[2] += 10
    cout << "　A[2] += 10\n";
    cout << "　A[2]の現在値: " << fw.sum(2, 3) << '\n';

    cout << "\n===== 一点を指定した値へ変更 =====\n";
    // 現在 A[2] = 13
    // A[2]を7へ変更したいので，7 - 13 = -6 を加える．
    ll new_value = 7;
    fw.add(2, new_value - fw.sum(2, 3));

    cout << "　A[2]を7へ変更\n";
    cout << "　A[2]の現在値: " << fw.sum(2, 3) << '\n';

    cout << "\n===== 最後の配列内容 =====\n";
    cout << "　A: ";
    for (int i=0; i<n; i++) {
        cout << fw.sum(i, i + 1) << ' ';
    }
    cout << '\n';


    cout << "\n#### vectorの初期値から作成 ####\n";
    vector B{10, 20, 30, 40, 50};
    fenwick_tree<ll> fw2(B.size());
    for (int i=0; i<ssize(B); i++) {
        fw2.add(i, B[i]);
    }
    cout << "　B = {10, 20, 30, 40, 50} で初期化\n";
    cout << "　B[1:4)の合計: " << fw2.sum(1, 4) << '\n';
    cout << "　B[0:5)の合計: " << fw2.sum(0, 5) << '\n';

    return 0;
}

#endif