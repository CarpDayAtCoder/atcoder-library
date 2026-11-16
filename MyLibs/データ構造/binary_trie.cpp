#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
using ll = long long;

// ============================================================
// Binary Trie まとめ
//
// 使用頻度：★★★☆☆
// 主な用途：整数の順序付き管理，個数検索，k番目の値，XOR問題
//
// 0以上の整数を2進数のbit列として管理する．
// 同じ値を複数個保持できる．
//
// ------------------------------------------------------------
// 基本操作
//
// BinaryTrie bt;   // 非負のllを扱えるBinaryTrieを作成
//
// bt.insert(x)     // xを1個追加
// bt.erase(x)      // xを1個削除．【重要】xが存在すること前提
// int a = bt.count(x)      // xの個数
// int b = bt.count_less(x) // x未満の個数
// int c = bt.count_ge(x)   // x以上の個数
// int d = bt.count_gt(x)   // xより大きい個数
// ll e = bt.kth(k)         // 0-indexでk番目に小さい値
//
// 各操作：O(bit数) ≒ O(log A)
// A：値の最大値
//
// 【重要】
// ・各ノードは0側，1側の子と，部分木の要素数cntを持つ．
// ・子ノードはvector内の添字で管理する．
// ・削除ではノード自体は消さず，cntだけ減らす．
// ・負数は扱わない前提．
//
// ============================================================

// ============================================================
// 【パターン１：SortedList的な整数管理】
//
// SortedList的な操作       Binary Trie
// add(x)                  insert(x)
// remove(x)               erase(x)
// bisect_left(x)          count_less(x)
// bisect_right(x)         count_le(x)
// len(A)                  size()
// A[k]                    kth(k)
//
// データそのものを昇順配列として保持しているわけではない．
// 必要ならkth(0), kth(1), ... と取り出せる．
// ============================================================

#if 0

struct BinaryTrie {
    struct Node {
        array<int, 2> child{-1, -1};
        int cnt = 0;
    };

    // ビット数の設定
    static constexpr int MAX_BIT = 62;  // 対象：ll．約9.2×10^18 までの非負整数
    // static constexpr int MAX_BIT = 29; // 対象：int．約1.07×10^9 までの非負整数

    vector<Node> tr{Node{}};     // tr[0]がroot

    // 全要素数
    int size() {
        return tr[0].cnt;
    }

    // xの個数
    int count(ll x) {
        int v = 0;
        for (int b=MAX_BIT; b>=0; b--) {
            int bit = (x >> b) & 1;
            v = tr[v].child[bit];
            if (v == -1) return 0;
        }
        return tr[v].cnt;
    }

    // xを1個追加
    void insert(ll x) {
        int v = 0;
        tr[v].cnt++;
        for (int b=MAX_BIT; b>=0; b--) {
            int bit = (x >> b) & 1;
            if (tr[v].child[bit] == -1) {
                tr[v].child[bit] = ssize(tr);
                tr.push_back(Node{});
            }
            v = tr[v].child[bit];
            tr[v].cnt++;
        }
    }

    // xを1個削除
    // xが存在することを前提
    void erase(ll x) {
        int v = 0;
        tr[v].cnt--;
        for (int b=MAX_BIT; b>=0; b--) {
            int bit = (x >> b) & 1;
            v = tr[v].child[bit];
            tr[v].cnt--;
        }
    }

    // x未満の要素数
    int count_less(ll x) {
        int v = 0;
        int ret = 0;
        for (int b=MAX_BIT; b>=0; b--) {
            if (v == -1) break;
            int bit = (x >> b) & 1;
            if (bit == 1) {
                // 0側は，このbitでxより小さいことが確定
                int u = tr[v].child[0];
                if (u != -1) ret += tr[u].cnt;
                v = tr[v].child[1];
            }
            else    v = tr[v].child[0];
        }
        return ret;
    }

    // x以下の要素数
    int count_le(ll x) {
        return count_less(x) + count(x);
    }

    // x以上の要素数
    int count_ge(ll x) {
        return size() - count_less(x);
    }

    // xより大きい要素数
    int count_gt(ll x) {
        return size() - count_le(x);
    }

    // 0-indexでk番目に小さい値
    // 0 <= k < size() を前提
    ll kth(int k) {
        int v = 0;
        ll ret = 0;
        for (int b=MAX_BIT; b>=0; b--) {
            int u = tr[v].child[0];
            int cnt0 = (u == -1 ? 0 : tr[u].cnt);
            if (k < cnt0)   v = u;
            else {
                k -= cnt0;
                ret |= 1LL << b;
                v = tr[v].child[1];
            }
        }
        return ret;
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    BinaryTrie bt;          // BinaryTrieの構築．上限ll（約9.2×10^18）

    // 2, 3, 5, 6 を追加
    bt.insert(2);
    bt.insert(3);
    bt.insert(5);
    bt.insert(6);

    cout << "要素数: " << bt.size() << '\n';

    cout << "3の個数: " << bt.count(3) << '\n';
    cout << "5未満: " << bt.count_less(5) << '\n';
    cout << "5以下: " << bt.count_le(5) << '\n';
    cout << "5以上: " << bt.count_ge(5) << '\n';
    cout << "5より大きい: " << bt.count_gt(5) << '\n';

    cout << "\n昇順:\n";
    for (int k=0; k<bt.size(); k++) {
        cout << bt.kth(k) << ' ';
    }
    cout << '\n';

    // 同じ値も複数保持できる
    bt.insert(3);
    cout << "\n3を追加:\n";
    for (int k=0; k<bt.size(); k++) {
        cout << bt.kth(k) << ' ';
    }
    cout << '\n';
    cout << "3の個数: " << bt.count(3) << '\n';

    // 3を1個削除
    bt.erase(3);
    cout << "\n3を1個削除:\n";
    for (int k=0; k<bt.size(); k++) {
        cout << bt.kth(k) << ' ';
    }
    cout << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン2：長い2進数をstringで管理】
//
// ll(64bit)に収まらない固定長の2進数をstringとして管理する．
// 例：200bitの整数など
//
// BinaryTrieString bt(200);     // 200bitのBinary Trieを作成
//
// bt.insert(x)                  // xを1個追加
// bt.erase(x)                   // xを1個削除．【重要】xが存在すること前提
// int a = bt.count(x)           // xの個数
// int b = bt.count_less(x)      // x未満の個数
// int c = bt.count_le(x)        // x以下の個数
// int d = bt.count_ge(x)        // x以上の個数
// int e = bt.count_gt(x)        // xより大きい個数
// string x = bt.kth(k)          // 0-indexでk番目に小さい値
//
// 【重要】
// ・すべて同じ長さの0/1文字列を扱う．
// ・文字列の先頭を最上位bitとする．
// ・固定長なので，数値の大小と文字列の辞書順が一致する．
// ・桁数に上限はないが，1回の操作にO(B)かかる．B：bit数
//
// ============================================================
#if 1

struct BinaryTrieString {
    struct Node {
        array<int, 2> child{-1, -1};
        int cnt = 0;
    };

    int B;                       // ビット数
    vector<Node> tr{Node{}};     // tr[0]がroot

    BinaryTrieString(int bits) : B(bits) {} // コンストラクタ．B=bit

    // 全要素数
    int size() {
        return tr[0].cnt;
    }

    // xの個数
    int count(string& x) {
        int v = 0;
        for (char c : x) {
            int bit = c - '0';
            v = tr[v].child[bit];
            if (v == -1) return 0;
        }
        return tr[v].cnt;
    }

    // xを1個追加
    void insert(string& x) {
        int v = 0;
        tr[v].cnt++;
        for (char c : x) {
            int bit = c - '0';
            if (tr[v].child[bit] == -1) {
                tr[v].child[bit] = ssize(tr);
                tr.push_back(Node{});
            }
            v = tr[v].child[bit];
            tr[v].cnt++;
        }
    }

    // xを1個削除
    // xが存在することを前提
    void erase(string& x) {
        int v = 0;
        tr[v].cnt--;
        for (char c : x) {
            int bit = c - '0';
            v = tr[v].child[bit];
            tr[v].cnt--;
        }
    }

    // x未満の要素数
    int count_less(string& x) {
        int v = 0;
        int ret = 0;
        for (char c : x) {
            if (v == -1) break;
            int bit = c - '0';
            if (bit == 1) {
                // 0側は，このbitでxより小さいことが確定
                int u = tr[v].child[0];
                if (u != -1) ret += tr[u].cnt;
                v = tr[v].child[1];
            }
            else    v = tr[v].child[0];
        }
        return ret;
    }

    // x以下の要素数
    int count_le(string& x) {
        return count_less(x) + count(x);
    }

    // x以上の要素数
    int count_ge(string& x) {
        return size() - count_less(x);
    }

    // xより大きい要素数
    int count_gt(string& x) {
        return size() - count_le(x);
    }

    // 0-indexでk番目に小さい値
    // 0 <= k < size() を前提
    string kth(int k) {
        int v = 0;
        string ret;
        for (int b=0; b<B; b++) {
            int u = tr[v].child[0];
            int cnt0 = (u == -1 ? 0 : tr[u].cnt);
            if (k < cnt0) {
                ret += '0';
                v = u;
            }
            else {
                k -= cnt0;
                ret += '1';
                v = tr[v].child[1];
            }
        }
        return ret;
    }
};


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    BinaryTrieString bt(6);     // 6bitの2進数を管理

    string a = "000010";        // 2
    string b = "000011";        // 3
    string c = "000101";        // 5
    string d = "000110";        // 6

    bt.insert(a);
    bt.insert(b);
    bt.insert(c);
    bt.insert(d);

    cout << "要素数: " << bt.size() << '\n';

    string x = "000101";        // 5

    cout << "5の個数: " << bt.count(x) << '\n';
    cout << "5未満: " << bt.count_less(x) << '\n';
    cout << "5以下: " << bt.count_le(x) << '\n';
    cout << "5以上: " << bt.count_ge(x) << '\n';
    cout << "5より大きい: " << bt.count_gt(x) << '\n';

    cout << "\n昇順:\n";
    for (int k=0; k<bt.size(); k++) {
        cout << bt.kth(k) << '\n';
    }

    // 同じ値も複数保持できる
    bt.insert(b);

    cout << "\n3を追加:\n";
    for (int k=0; k<bt.size(); k++) {
        cout << bt.kth(k) << '\n';
    }

    bt.erase(b);

    return 0;
}

#endif

// ============================================================
// 補足
// ============================================================
// 【ノード】
//
// struct Node {
//     array<int, 2> child{-1, -1};
//     int cnt = 0;
// };
//
// child[0]：次のbitが0の子ノード
// child[1]：次のbitが1の子ノード
// cnt     ：このノード以下に存在する要素数
//
// childにはNodeそのものではなく，vector tr の添字を保存する．
// tr[0]がroot．
//
// ============================================================
// 【insert】
//
// xのbitを上位から順にたどる．
// int bit = (x >> b) & 1;
//
// 必要な子ノードが存在しなければ新しく作る．
// if (tr[v].child[bit] == -1) {
//     tr[v].child[bit] = ssize(tr);
//     tr.push_back(Node{});
// }
//
// 通過したノードのcntを+1する．
//
// ============================================================
// 【erase】
//
// insertと同じ経路をたどり，cntを-1する．
//
// ノードそのものは削除しない．
// cnt == 0 なら，その部分木には現在有効な値がないとみなす．
//
// このテンプレートではxが存在することを前提とする．
//
// ============================================================
// 【count_less(x)】
//
// xのbitを上位から見る．
//
// xの現在のbitが0：
//     0側へ進む．
// xの現在のbitが1：
//     0側にある値はすべてx未満なので，
//     0側のcntを答えに加えて1側へ進む．
//
// 例： x = 1xxxx...
//         0xxxx... はすべてx未満．
//
// ============================================================
// 【kth(k)】
//
// 0-indexでk番目に小さい値を探す．
//
// 0側の要素数をcnt0とすると，
// k < cnt0
//     → 求める値は0側
// k >= cnt0
//     → k -= cnt0 として1側
// を各bitについて繰り返す．
//
// ============================================================
// 【計算量】
//
// B：見るbit数（long longなら最大63程度）
//
// insert       O(B)
// erase        O(B)
// count        O(B)
// count_less   O(B)
// count_ge     O(B)
// kth          O(B)
//
// Bはほぼ定数なので，実戦上かなり高速．
//
// メモリ：作成されたノード数に比例．
// 最悪では「追加した値の個数 × bit数」程度のノードができる．
//
// ============================================================
// 【intだけでよい場合】
//
// 値が0以上2^30未満なら，
// static constexpr int MAX_BIT = 29;
// とすれば十分．
// 0以上10^9程度も29～0の30bitで表せる．
//
// ============================================================