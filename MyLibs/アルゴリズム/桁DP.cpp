#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
using ll = long long;

// ============================================================
// 桁DP まとめ
//
// 使用頻度：★★★☆☆
// 主な用途：0～Nの整数を，桁に関する条件付きで数える
// キーワード：桁DP，digit DP，less，started，leading zero
//
// 【基本】
// 上位桁から順に決める．
//   less = 0：ここまでNと同じ
//   less = 1：すでにNより小さい
//
// int digit = S[i] - '0';          // 次の桁
// int limit = less ? 9 : digit;    // 次の桁のとり得る値の上限
//
// for (int x=0; x<=limit; x++) {
//     int nless = less || x < digit;
//     int nstate = ...;             // 問題に応じて次状態を計算
//     ndp[nless][nstate] += dp[less][state];
// }
// swap(dp, ndp);   // 各桁の処理後，dp <--> ndp：
//
// ------------------------------------------------------------
// 【パターン１】基本形
//    less + 問題固有の状態
//
// 【パターン２】先頭0を区別する形
//    less + started + 問題固有の状態
//
// 【パターン３】ビット列で使用する数字を表現
//    mask: ビット列．mask==0 ⇔ 0以外の数が登場していない
//
// ============================================================

// ============================================================
// 【パターン１】基本形
//
// 例：0～Nのうち，3で割り切れる整数の個数
// dp[less][mod]
//   mod：現在の数を3で割った余り　　※ 答えがllに収まる前提
// ============================================================
#if 0

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    string S = "100";     // 0～N の整数が対象

    using State = array<array<ll, 3>, 2>;   // State[less][mod]
    State dp{}, ndp{};
    dp[0][0] = 1;         // まだ1桁も選んでいない初期状態

    for (int i=0; i<ssize(S); i++) {
        ndp = State{};                      // 次の桁のDPを0クリア
        int digit = S[i] - '0';             // 今回の桁の値
        for (int less : {0,1}) {
            for (int mod=0; mod<3; mod++) {
                // すでにN未満なら0～9，そうでなければ0～digit
                int limit = less ? 9 : digit;
                for (int x=0; x<=limit; x++) {      // 追加する値．0～limit
                    int nless = less || x < digit;
                    int nmod = (mod * 10 + x) % 3;
                    // 現在の状態から次の状態へ遷移
                    ndp[nless][nmod] += dp[less][mod];
                }
            }
        }
        swap(dp, ndp);    // 次の桁のDPを現在のDPにする
    }
    ll ans = dp[0][0] + dp[1][0];   // mod=0を集計．0も含む
    cout << "0～" << S << "までの3の倍数は " << ans << "個\n";

    return 0;
}

#endif

// ============================================================
// 【パターン２】先頭0を区別する形
//
// 例：1～Nのうち，十進表記に0を1個以上含む整数の個数
//
// dp[less][started][has_zero]
//   started  ：有効な桁がすでに始まっているか
//   has_zero ：有効な桁に0を含んでいるか
//
// 例：005 → 5
//     先頭の00は「数字0を使った」とは数えない
// ============================================================
#if 0

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    string S = "100";     // 1～N の整数が対象

    using State = array<array<array<ll, 2>, 2>, 2>;
                               // State[less][started][has_zero]
    State dp{}, ndp{};
    dp[0][0][0] = 1;           // まだ1桁も選んでいない初期状態

    for (int i=0; i<ssize(S); i++) {
        ndp = State{};                      // 次の桁のDPを0クリア
        int digit = S[i] - '0';             // 今回の桁の値
        for (int less : {0,1}) {
            for (int started : {0,1}) {
                for (int has_zero : {0,1}) {
                    // すでにN未満なら0～9，そうでなければ0～digit
                    int limit = less ? 9 : digit;

                    for (int x=0; x<=limit; x++) {  // 追加する値．0～limit
                        int nless = less || x < digit;
                        int nstarted = started || x != 0;
                        // 数が始まった後に0を選んだらhas_zero=true
                        int nhas_zero = has_zero || (started && x == 0);
                        // 現在の状態から次の状態へ遷移
                        ndp[nless][nstarted][nhas_zero] += dp[less][started][has_zero];
                    }
                }
            }
        }
        swap(dp, ndp);    // 次の桁のDPを現在のDPにする
    }

    ll ans = dp[0][1][1] + dp[1][1][1];   // started=1のみを選んで，0を除外
    cout << "1～" << S << "までで0を含む整数は " << ans << "個\n";

    return 0;
}

#endif


// ============================================================
// 【パターン３】ビット列で使用する数字を表現
//
// 例：1～Nのうち，
// ・使用した数字がちょうどK種類
// ・Mの倍数
// を満たす整数の個数
//
// dp[mask][less][mod]
//   mask：使用した数字の集合．数字kを使った -> 下から位kビット目 = 1
//   mask==0：まだ0以外の数を選んでいない
//
// 例：005 → 5
//     先頭の00の段階では，mask=0のまま
// ============================================================
#if 1

#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    string S = "100";    // 1～N の整数が対象
    int K = 1;           // 使用する数字の種類数
    int M = 7;           // Mの倍数．2≦M≦9と仮定．
    int ALL_STATES = 1 << 10;

    using State = array<array<mint, 9>, 2>;   // State[less][mod]．modは9あれば足りる
    vector dp(ALL_STATES, State{});           // dp[mask][less][mod]
    vector ndp(ALL_STATES, State{});
    dp[0][0][0] = 1;                          // まだ1桁も選んでいない初期状態

    for (int i=0; i<ssize(S); i++) {
        fill(ndp.begin(), ndp.end(), State{});    // 次の桁のDPを0クリア
        int digit = S[i] - '0';                   // 今回の桁の値
        for (int mask=0; mask<ALL_STATES; mask++) {
            for (int less : {0,1}) {
                for (int mod=0; mod<M; mod++) {
                    // すでにN未満なら0～9，そうでなければ0～digit
                    int limit = less ? 9 : digit;
                    for (int x=0; x<=limit; x++) {    // 追加する値．0～limit
                        // 先頭0ならmaskは0のまま
                        int nmask = (mask == 0 && x == 0) ? 0 : mask | (1 << x);
                        int nless = less || x < digit;
                        int nmod = (mod * 10 + x) % M;
                        // 現在の状態から次の状態へ遷移
                        ndp[nmask][nless][nmod] += dp[mask][less][mod];
                    }
                }
            }
        }
        swap(dp, ndp);    // 次の桁のDPを現在のDPにする
    }

    mint ans = 0;
    for (int mask=1; mask<ALL_STATES; mask++) {   // mask=0は数値0なので除外
        if (popcount((unsigned)mask) != K) continue;    // 使用する数字が K種類
        for (int less : {0,1}) {
            ans += dp[mask][less][0];             // mod=0を集計
        }
    }
    cout << "1～" << S << "までで，使用数字が" << K
         << "種類の" << M << "の倍数は " << ans.val() << "個\n";

    return 0;
}

#endif

// ============================================================
// 補足
// ============================================================
// rolling DP
//
// 直前の桁しか参照しない場合は，dp / ndp の2層だけ持てばよい．
// 各桁の先頭でndpを0初期化し，最後に
//   swap(dp, ndp);
// とする．vectorのswap自体はO(1)．
//
// ============================================================
// less
//
// less = 0：ここまでNと一致
//   → 選べる数字は0～digit
// less = 1：すでにNより小さい
//   → 選べる数字は0～9
//
// int limit = less ? 9 : digit;
// int nless = less || x < digit;
//
// ============================================================
// 先頭0
//
// 000123を123として扱う場合，先頭の0を通常の数字0として
// 状態に反映してはいけないことがある．
//
// 方法：
// ・startedを別状態として持つ
// ・mask==0など，既存状態の特殊値で未開始を表す
//
// 後者で表現できるなら状態数を1次元減らせる．
//
// ============================================================
// mod状態
//
// 数そのものをMで割った余りなら
//   nmod = (mod * 10 + x) % M;
//
// 桁和をMで割った余りなら
//   nmod = (mod + x) % M;
//
// ============================================================
// 1～Nを数える
//
// 0を含むDPなら，最後に0の状態を除外する．
// startedを持つ場合：started==0を除外
// mask==0を未開始としている場合：mask==0を除外
//
// ============================================================
// L～Rを数える
//
// 0～Nで条件を満たす個数を数える関数を solve(N) として桁DPで実装．
// 求める答えは，累積和と同様に考えて
//   solve(R) - solve(L-1)
//
// ただし，L,Rをstringで持つほど大きい場合は，L-1が
// 計算できないため，stringのまま対応できる処理が必要．
//
// ============================================================
// 次元の順番
//
// 例： dp[mask][less][mod]
// 順番そのものに決まりはない．
// ループ順と合わせ，内側に小さい固定状態を置くと扱いやすい．
//
// ============================================================