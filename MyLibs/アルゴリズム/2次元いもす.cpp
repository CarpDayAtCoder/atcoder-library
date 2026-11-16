#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ============================================================
// 2次元いもす・2次元累積和
//
// 使用頻度：★★☆☆☆
//
// 盤面は1-index．盤面h×wに対してimos，Sは(h+2)×(w+2)で作成する．
// 長方形はすべて半開区間 [r1,r2) × [c1,c2) で指定する．
//
// add_rect(imos, r1, r2, c1, c2, x);
//     長方形 [r1,r2) × [c1,c2) にxを加算する．差分のみ記録．
//
// build_imos(imos);
//     差分から各マスの値を復元する．
//
// auto S = build_sum(imos);
//     2次元累積和を作る．Sもimosと同じ大きさ．
//     S[r][c] = [1,r) × [1,c) の合計．
//
// rect_sum(r1, r2, c1, c2, S);
//     [r1,r2) × [c1,c2) の合計を求める．
//
// 問題文が閉区間 [r1,r2] × [c1,c2] なら，
// [r1,r2+1) × [c1,c2+1) として指定する．
//
// ============================================================

void add_rect(vector<vector<ll>>& imos, int r1, int r2, int c1, int c2, ll x) {  // 長方形に加算．差分のみ記録
    imos[r1][c1] += x;
    imos[r1][c2] -= x;
    imos[r2][c1] -= x;
    imos[r2][c2] += x;
}

void build_imos(vector<vector<ll>>& imos) {  // 差分 → 各マスの値を復元
    int h = ssize(imos), w = ssize(imos[0]);
    for (int r=1; r<h; r++) for (int c=1; c<w; c++) imos[r][c] += imos[r][c-1];
    for (int r=1; r<h; r++) for (int c=1; c<w; c++) imos[r][c] += imos[r-1][c];
}

vector<vector<ll>> build_sum(vector<vector<ll>>& imos) {  // 2次元累積和を作成
    int h = ssize(imos)-2, w = ssize(imos[0])-2;
    vector S(h+2, vector<ll>(w+2));
    for (int r=1; r<=h; r++) for (int c=1; c<=w; c++)
        S[r+1][c+1] = imos[r][c] + S[r][c+1] + S[r+1][c] - S[r][c];
    return S;
}

ll rect_sum(int r1, int r2, int c1, int c2, vector<vector<ll>>& S) {  // 長方形の合計
    return S[r2][c2] - S[r2][c1] - S[r1][c2] + S[r1][c1];
}

int main() {
    int h = 4, w = 5;
    vector imos(h+2, vector<ll>(w+2));             // 1-index＋右端・下端の差分用に+2

    add_rect(imos, 1, 3, 2, 5, 1);                 // [1,3)×[2,5) に+1．差分のみ記録
    add_rect(imos, 2, 5, 3, 6, 2);                 // [2,5)×[3,6) に+2．差分のみ記録
    build_imos(imos);                               // 差分 → 各マスの値を復元
    auto S = build_sum(imos);                       // 2次元累積和を作成
    cout << rect_sum(2, 5, 3, 6, S) << '\n';       // [2,5)×[3,6) の合計 → 20

    return 0;
}

// ============================================================
// add_rectの仕組み
//
// 1次元いもすでは，[l,r)にxを加えるとき，
// diff[l] += x，diff[r] -= x とする．
//
// 2次元ではこれを行方向・列方向の両方に適用するため，
// 長方形 [r1,r2) × [c1,c2) にxを加えるとき，
//
// imos[r1][c1] += x;
// imos[r1][c2] -= x;
// imos[r2][c1] -= x;
// imos[r2][c2] += x;
//
// の4点に差分を記録する．
//
// ============================================================
// build_imosの仕組み
//
// 横方向，縦方向の順に累積することで，
// 4点に記録した差分から各マスの値を復元する．
// 縦→横の順でも結果は同じ．
//
// ============================================================
// 2次元累積和
//
// S[r][c] = [1,r) × [1,c) の合計．
// したがって盤面全体の合計は S[h+1][w+1]．
//
// [r1,r2) × [c1,c2) の合計は，
//
// S[r2][c2] - S[r2][c1] - S[r1][c2] + S[r1][c1]
//
// 大きな長方形から上側と左側を引き，
// 二重に引いた左上部分を足し戻している．
//
// ============================================================