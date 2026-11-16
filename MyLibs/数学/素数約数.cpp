#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
using ll = long long;

// ============================================================
// 約数・倍数・素数 まとめ
//
// 使用頻度：★★★★☆
//
// ------------------------------------------------------------
// ◎ 1つの数を調べる：前計算なし
// 【パターン1】素数判定                  O(√N)
// 【パターン2】約数列挙                  O(√N)
// 【パターン3】素因数分解                O(√N)
//
// ------------------------------------------------------------
// ◎多数の数を調べる：前計算を利用
// 【パターン4】エラトステネスの篩        O(N log log N)
//             1～Nの素数判定，素数一覧
// 【パターン5】最小素因数 SPF の前計算   O(N log log N)
//             多数の数の素因数分解      O(log N) / 1個
//
// ------------------------------------------------------------
// 【補足】
// ・gcd / lcm
// ・倍数の個数，列挙
// ・素因数分解から(1)約数の個数(2)約数の総和(3)Eulerのφ関数
// ・素因数分解から約数を列挙
// ・線形篩（パターン4でTLEになる非常事態用）
//
// ============================================================

// ============================================================
// 【パターン1】1つの数：素数判定 O(√N)
//     nが素数ならtrueを返す．
// ============================================================
#if 0

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (ll p=3; p<=n/p; p+=2) {
        if (n % p == 0) return false;
    }
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << boolalpha;
    cout << "2   : " << is_prime(2) << '\n';
    cout << "97  : " << is_prime(97) << '\n';
    cout << "100 : " << is_prime(100) << '\n';
    cout << "997 : " << is_prime(997) << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン2】1つの数：約数列挙 O(√N)
//     nの正の約数を昇順で返す．
// ============================================================
#if 0

vector<ll> divisors(ll n) {
    vector<ll> ret;

    for (ll d=1; d<=n/d; d++) {
        if (n % d != 0) continue;
        ret.push_back(d);
        if (d != n/d) ret.push_back(n/d);   // 平方根の重複を防ぐ
    }
    ranges::sort(ret);
    return ret;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    ll n = 120;
    vector<ll> D = divisors(n);
    cout << n << " の約数\n";
    for (ll x : D) cout << x << ' ';
    cout << '\n';

    return 0;
}

#endif

// ============================================================
// 【パターン3】1つの数：素因数分解 O(√N)
//     n = p1^e1 * p2^e2 * ...
//     戻り値：
//       {{p1,e1}, {p2,e2}, ...}
//     例：360 = 2^3 * 3^2 * 5
//             -> {{2,3}, {3,2}, {5,1}}
// ============================================================
#if 0

vector<pair<ll,int>> factorize(ll n) {
    vector<pair<ll,int>> ret;

    // 2の指数
    if (n % 2 == 0) {
        int e = 0;
        while (n % 2 == 0) {
            n /= 2;
            e++;
        }
        ret.push_back({2, e});
    }
    // 3以上の奇数
    for (ll p=3; p<=n/p; p+=2) {
        if (n % p != 0) continue;
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        ret.push_back({p, e});
    }
    // √nより大きい素因数が残っている場合
    if (n > 1) ret.push_back({n, 1});
    return ret;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    ll n = 360;
    auto factors = factorize(n);
    cout << n << " の素因数分解\n";
    for (auto [p, e] : factors) {
        cout << p << "^" << e << ' ';
    }
    cout << '\n';
    return 0;
}

#endif


// ============================================================
// 【パターン4】多数の数：エラトステネスの篩
//     0～Nについて素数かどうかを前計算する．
//     前計算：O(N log log N)
//     判定  ：O(1)
//    [注意] 1個だけ調べるならパターン1でよい．
//           1～Nを何度も素数判定するときに使う．
// ============================================================
#if 0

vector<bool> sieve(int n) {
    vector<bool> is_prime(n+1, true);   // 0～n

    is_prime[0] = is_prime[1] = false;
    for (ll p=2; p*p<=n; p++) {
        if (!is_prime[p]) continue;
        // pより小さい素因数を持つ倍数は処理済みなのでp*pから開始
        for (ll x=p*p; x<=n; x+=p) {
            is_prime[x] = false;
        }
    }
    return is_prime;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int n = 100;
    vector<bool> is_prime = sieve(n);
    cout << boolalpha;
    cout << "97は素数: " << is_prime[97] << '\n';
    cout << "99は素数: " << is_prime[99] << '\n';
    cout << "\n" << n << "以下の素数\n";
    for (int x=2; x<=n; x++) {
        if (is_prime[x]) cout << x << ' ';
    }
    cout << '\n';
    return 0;
}

#endif

// ============================================================
// 【パターン5】多数の数：SPF（最小素因数）
//     spf[x]：xの最小素因数
//     例：spf[12] = 2
//         spf[21] = 3
//         spf[49] = 7
//       1～NのSPFを前計算しておくと，
//       N以下の多数の整数を高速に素因数分解できる．
//     SPF前計算：O(N log log N)
//     素因数分解：O(log N) / 1個
//     ※ 分解する値はSPFを作成した上限N以下である必要がある．
// ============================================================
#if 1

vector<int> make_spf(int n) {
    vector<int> spf(n+1);

    iota(spf.begin(), spf.end(), 0);    // spf[i] = i (i=0,1,...,n)
    for (ll p=2; p*p<=n; p++) {
        if (spf[p] != p) continue;     // pは素数でなければスキップ
        for (ll x=p*p; x<=n; x+=p) {
            if (spf[x] == x) {
                spf[x] = p;            // 最初に見つかった素因数がSPF
            }
        }
    }
    return spf;
}

vector<pair<int,int>> factorize(int n, const vector<int>& spf) {
    vector<pair<int,int>> ret;

    while (n > 1) {
        int p = spf[n];     // nのSPF
        int e = 0;
        while (n % p == 0) {
            n /= p;         // nのSPFで割れるだけ割る
            e++;
        }
        ret.push_back({p, e});
    }
    return ret;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    constexpr int MAX = 10000;
    vector<int> spf = make_spf(MAX);

    // 素数判定
    // x >= 2 なら，spf[x] == x ⇔ xは素数
    cout << boolalpha;
    cout << "97は素数: " << (spf[97] == 97) << '\n';
    cout << "99は素数: " << (spf[99] == 99) << '\n';

    // 素因数分解
    int n = 9994;
    auto factors = factorize(n, spf);
    cout << "\n" << n << " の素因数分解\n";
    for (auto [p, e] : factors) {
        cout << p << "^" << e << ' ';
    }
    cout << '\n';

    // 素数一覧
    cout << "\n100以下の素数\n";
    for (int x=2; x<=100; x++) {
        if (spf[x] == x) cout << x << ' ';
    }
    cout << '\n';

    return 0;
}

#endif

// ============================================================
// 補足
// ============================================================
// gcd / lcm
//
// #include <numeric>    // bits/stdc++.hなら不要
// ll g = gcd(a, b);    // 最大公約数
// ll l = lcm(a, b);    // 最小公倍数
//
// gcd(a, b) == 1       // aとbは互いに素
// ※ lcmは値が大きくなりやすいのでオーバーフローに注意．
//
// ============================================================
// 倍数
//
// // N以下のKの倍数の個数
//     N / K
//
// // [L,R]内のKの倍数の個数
//     R / K - (L-1) / K
//
// // N以下のKの倍数を列挙
//     for (ll x=K; x<=N; x+=K) {
//         ...
//     }
//
// ============================================================
// 素因数分解から約数の個数を求める
//
// n = p1^e1 * p2^e2 * ... * pk^ek
//
// 約数の個数
//     (e1+1)(e2+1)...(ek+1)
//     例：360 = 2^3 * 3^2 * 5^1
//       約数の個数 = 4 * 3 * 2 = 24
//
// vector<pair<ll,int>> factors = factorize(n);
// ll cnt = 1;
// for (auto [p, e] : factors) {
//     cnt *= e + 1;
// }
//
// ============================================================
// 素因数分解から約数の総和を求める
//
// n = p1^e1 * p2^e2 * ... * pk^ek
//
// 約数の総和
//     (1 + p1 + p1^2 + ... + p1^e1)
//   * (1 + p2 + p2^2 + ... + p2^e2)
//   * ...
//
// 各項は等比級数なので
//     1 + p + p^2 + ... + p^e
//       = (p^(e+1) - 1) / (p - 1)
// 例：360 = 2^3 * 3^2 * 5^1
//   約数の総和
//     = (1+2+4+8)(1+3+9)(1+5)
//     = 15 * 13 * 6
//     = 1170
//
// vector<pair<ll,int>> factors = factorize(n);
// ll sum = 1;
// for (auto [p, e] : factors) {
//     ll s = 1;
//     ll pw = 1;
//     for (int i=1; i<=e; i++) {
//         pw *= p;
//         s += pw;
//     }
//     sum *= s;
// }
//
// ============================================================
// オイラーのφ関数
// φ(n)：1～nのうち，nと互いに素な整数の個数
//
// n = p1^e1 * p2^e2 * ... * pk^ek のとき
//     φ(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk)
//
// vector<pair<ll,int>> factors = factorize(n);
// ll phi = n;
// for (auto [p, e] : factors) {
//     phi = phi / p * (p - 1);
// }
//
// ============================================================
// 素因数分解結果から約数を列挙
//
// すでに素因数分解済みの場合は，各素因数の指数の組合せから約数を生成できる．
//
// vector<ll> divisors_from_factors(const vector<pair<ll,int>>& factors) {
//     vector<ll> ret{1};
//
//     for (auto [p, e] : factors) {
//         int sz = ssize(ret);         // 素因数 pを掛ける前での約数の個数
//         ll pw = 1;
//         for (int k=1; k<=e; k++) {
//             pw *= p;                 // p^kを pを掛ける前での約数に掛ける
//             for (int i=0; i<sz; i++) {
//                 ret.push_back(ret[i] * pw); 
//             }
//         }
//     }
//     ranges::sort(ret);
//     return ret;
// }
//
// ============================================================
// 【参考】線形篩
//
// 通常の篩では，同じ合成数を複数回調べる場合がある．
// 線形篩では，各合成数を1回だけ生成するようにしてO(N)で処理する．
// 素数一覧 primes と最小素因数 spf を同時に作れる．
//
// pair<vector<int>, vector<int>> linear_sieve(int n) {
//     vector<int> primes;
//     vector<int> spf(n+1);
//
//     for (int x=2; x<=n; x++) {
//         if (spf[x] == 0) {
//             spf[x] = x;
//             primes.push_back(x);
//         }
//         for (int p : primes) {
//             if (p > spf[x] || 1LL*p*x > n) break;
//             spf[p*x] = p;
//         }
//     }
//     return {primes, spf};
// }
//
// 通常のエラトステネス型SPFで十分なことが多い．
// 線形篩が必要になったときに使用する．
//
// ============================================================