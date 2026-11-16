#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif

// ============================================================
// SortedList まとめ
//
// 使用頻度：★★★★☆
// 主な用途：値を昇順に保ちながら追加・削除，個数検索，k番目の値
//
// Pythonのsortedcontainers.SortedListと同様に，
// ソート済みの小さなvector（block）に分割して管理する．
// 同じ値を複数個保持できる．
//
// 【基本操作】
//
// SortedList<ll> sl;                 // 要素の型がll
// SortedList<string> sl;             // stringも使用可
// SortedList sl(A);              // vector Aから構築．型はAから推論，内部でソート
//
// sl.insert(x);                       // xを1個追加
// bool f = sl.erase(x);               // xを1個削除．なければfalse
// int a = sl.count(x);                // xの個数
// int b = sl.bisect_left(x);          // x未満の個数
// int c = sl.bisect_right(x);         // x以下の個数
// auto x = sl[k];                     // 0-indexでk番目に小さい値
// auto x = sl.kth(k);                 // 同上
// int n = sl.size();                  // 要素数．ssize(sl) でもOK
//
// Python SortedList             C++ SortedList
// add(x)                        insert(x)
// remove(x)                     erase(x)
// count(x)                      count(x)
// bisect_left(x)                bisect_left(x)
// bisect_right(x)               bisect_right(x)
// A[k]                          sl[k]
// len(A)                        size() or ssize(sl)
//
// 【重要】
// ・重複要素を保持できる．
// ・Tは通常の昇順比較ができる型を使用する．
// ・stringなら辞書順で管理される．
// ・kth(k), sl[k] は 0 <= k < size() を前提とする．
//
// ============================================================
using namespace std;
using ll = long long;

template <class T>
struct SortedList {
    // 1ブロックのおおよその大きさ
    static constexpr int LOAD = 700;

    vector<vector<T>> blocks;   // ソート済みの各ブロック
    vector<T> maxes;            // 各ブロックの最大値
    vector<int> fw{0};          // 各ブロックの要素数を管理するFenwick木
    int n = 0;

    SortedList() = default;

    // vectorから構築．元のvectorは変更しない
    SortedList(vector<T> a) {
        build(move(a));
    }

    // 全要素数
    int size() const { return n; }

    bool empty() const { return n == 0; }

    // vectorから構築
    void build(vector<T> a) {
        ranges::sort(a);        // ソートを実行
        n = ssize(a);
        blocks.clear();
        maxes.clear();
        for (int l=0; l<n; l+=LOAD) {
            int r = min(n, l + LOAD);
            blocks.emplace_back(
                make_move_iterator(a.begin() + l),
                make_move_iterator(a.begin() + r)
            );
            maxes.push_back(blocks.back().back());
        }
        rebuild_index();
    }

    // xを1個追加
    void insert(const T& x) {
        if (blocks.empty()) {
            blocks.push_back(vector<T>{x});
            maxes.push_back(x);
            n = 1;
            rebuild_index();
            return;
        }
        // xを入れるブロックを探す
        int bi = ranges::lower_bound(maxes, x) - maxes.begin();
        if (bi == ssize(blocks)) bi--;
        // ブロック内の適切な位置へ挿入
        auto it = ranges::lower_bound(blocks[bi], x);
        blocks[bi].insert(it, x);
        n++;
        // 大きくなりすぎたブロックを2分割
        if (ssize(blocks[bi]) > 2 * LOAD) {
            split(bi);
            rebuild_index();
        }
        else {
            maxes[bi] = blocks[bi].back();
            index_add(bi, 1);
        }
    }

    // xを1個削除
    // 削除できればtrue，xがなければfalse
    bool erase(const T& x) {
        if (blocks.empty()) return false;
        int bi = ranges::lower_bound(maxes, x) - maxes.begin();
        if (bi == ssize(blocks)) return false;
        auto it = ranges::lower_bound(blocks[bi], x);
        if (it == blocks[bi].end() || *it != x) return false;
        blocks[bi].erase(it);
        n--;
        // 空になったブロックは削除
        if (blocks[bi].empty()) {
            blocks.erase(blocks.begin() + bi);
            maxes.erase(maxes.begin() + bi);
            rebuild_index();
        }
        else {
            maxes[bi] = blocks[bi].back();
            index_add(bi, -1);
        }
        return true;
    }

    // x未満の要素数
    // Python SortedListのbisect_left(x)
    int bisect_left(const T& x) {
        if (blocks.empty()) return 0;
        // 最大値がx以上となる最初のブロック
        int bi = ranges::lower_bound(maxes, x) - maxes.begin();
        if (bi == ssize(blocks)) return n;
        auto it = ranges::lower_bound(blocks[bi], x);
        return index_sum(bi) + (it - blocks[bi].begin());
    }

    // x以下の要素数
    // Python SortedListのbisect_right(x)
    int bisect_right(const T& x) {
        if (blocks.empty()) return 0;
        // 最大値がxより大きくなる最初のブロック
        int bi = ranges::upper_bound(maxes, x) - maxes.begin();
        if (bi == ssize(blocks)) return n;
        auto it = ranges::upper_bound(blocks[bi], x);
        return index_sum(bi) + (it - blocks[bi].begin());
    }

    // xの個数
    int count(const T& x) {
        return bisect_right(x) - bisect_left(x);
    }

    // 0-indexでk番目に小さい値
    // 0 <= k < size() を前提
    const T& kth(int k) {
        int bi = index_kth(k);
        int pos = k - index_sum(bi);
        return blocks[bi][pos];
    }

    // sl[k]でもアクセス可能
    const T& operator[](int k) { return kth(k); }

    // bi番目のブロックを2分割
    void split(int bi) {
        int mid = ssize(blocks[bi]) / 2;

        vector<T> right(
            make_move_iterator(blocks[bi].begin() + mid),
            make_move_iterator(blocks[bi].end())
        );
        blocks[bi].erase(
            blocks[bi].begin() + mid,
            blocks[bi].end()
        );
        blocks.insert(
            blocks.begin() + bi + 1,
            move(right)
        );
        maxes[bi] = blocks[bi].back();
        maxes.insert(
            maxes.begin() + bi + 1,
            blocks[bi + 1].back()
        );
    }

    // 各ブロックの要素数からFenwick木を作り直す
    void rebuild_index() {
        fw.assign(ssize(blocks) + 1, 0);
        for(int i=0; i<ssize(blocks); i++) {
            index_add(i, ssize(blocks[i]));
        }
    }

    // bi番目のブロックの要素数をdeltaだけ変更
    void index_add(int i, int delta) {
        for (i++; i<ssize(fw); i+=i&-i) {
            fw[i] += delta;
        }
    }

    // 0～r-1番目のブロックに含まれる要素数
    int index_sum(int r) {
        int ret = 0;
        for (; r>0; r-=r&-r)    ret += fw[r];
        return ret;
    }

    // k番目の要素が入っているブロック番号
    // kは0-index
    int index_kth(int k) {
        int idx = 0;
        int bit = 1;
        while ((bit << 1) < ssize(fw)) {
            bit <<= 1;
        }
        for (; bit>0; bit>>=1) {
            int nxt = idx + bit;
            if (nxt < ssize(fw) && fw[nxt] <= k) {
                k -= fw[nxt];
                idx = nxt;
            }
        }
        return idx;
    }
};


// ============================================================
// 【パターン1：SortedList的な順序付き管理】
// ============================================================
#if 1

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    SortedList<ll> sl;

    sl.insert(5);
    sl.insert(2);
    sl.insert(5);
    sl.insert(7);
    sl.insert(1);
    sl.insert(3);
    sl.insert(5);

    cout << "要素数: " << sl.size() << '\n';

    cout << "\n昇順:\n";
    for(int k=0; k<sl.size(); k++) {
        cout << sl[k] << ' ';
    }
    cout << '\n';

    cout << "\n5の個数: " << sl.count(5) << '\n';
    cout << "5未満の個数: " << sl.bisect_left(5) << '\n';
    cout << "5以下の個数: " << sl.bisect_right(5) << '\n';

    cout << "0-indexで3番目: " << sl[3] << '\n';

    sl.erase(5);       // 5を1個だけ削除

    cout << "\n5を1個削除:\n";
    for(int k=0; k<sl.size(); k++) {
        cout << sl[k] << ' ';
    }
    cout << '\n';

    return 0;
}

#endif


// ============================================================
// 補足
// ============================================================
//
// 【内部構造】
//
// データ全体を1本の巨大なvectorにはせず，
//   [1 2 3 5] [5 5 7 10] [12 15 20]
// のような複数のソート済みvectorに分割して持つ．
//
// blocks：各ソート済みブロック
// maxes ：各ブロックの最大値
// fw    ：各ブロックの要素数を管理するFenwick木
//
// 例：
// blocks = {
//     {1, 2, 3, 5},
//     {5, 5, 7, 10},
//     {12, 15, 20}
// };
// maxes = {5, 10, 20};
//
// ============================================================
// 【insert】
//
// まずmaxesを二分探索して，xを入れるブロックを決める．
// 次に，そのブロック内をlower_boundしてxを挿入する．
// ブロックが大きくなりすぎたら2つに分割する．
//
// ============================================================
// 【bisect_left】
//
// x未満の個数を返す．
//   1．maxesを二分探索して対象ブロックを探す
//   2．それ以前のブロックの要素数をFenwick木で求める
//   3．対象ブロック内をlower_boundする
//
// Python:
//     sl.bisect_left(x)
// と同じ意味．
//
// ============================================================
// 【bisect_right】
//
// x以下の個数を返す．
//
// Python:
//     sl.bisect_right(x)
// と同じ意味．
//
// ============================================================
// 【kth / operator[]】
//
// Fenwick木を使って，k番目の要素がどのブロックに入っているかを高速に求める．
//
// sl.kth(k)
// sl[k]
// は同じ意味．
//
// ============================================================
// 【stringも使用可能】
//
// SortedList<string> sl;
// sl.insert("00101");
// sl.insert("11100");
//
// 固定長の0/1文字列なら，辞書順と2進数としての大小が一致する．
// したがって，200bitなどllに収まらない整数もstringのままSortedListで管理できる．
//
// ============================================================
// 【計算量の目安】
//
// B：ブロック数
// L：1ブロックの大きさ（LOAD ≒ 700）
//
// bisect_left/right
//     ブロック探索＋ブロック内探索＋Fenwick木 → おおむね O(log B + log L)
//
// kth → O(log B)
//
// insert / erase
//     二分探索に加え，vector内の要素移動 → おおむね O(L + log B)
//
// ブロック分割時には追加の処理が発生する．
// T=stringなどの場合，比較自体の計算量も別途かかる．
//
// ============================================================