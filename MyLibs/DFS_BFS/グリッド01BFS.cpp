#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// グリッド0-1 BFSテンプレート
//
// 使用頻度：★★★☆☆
// 主な用途：グリッド上で，移動コストが0または1の場合の最短距離
// キーワード：0-1 BFS，01BFS，grid，deque，dist，0コスト，1コスト
//
// 【基本】
// H × W のグリッドを0-indexで扱う．
// 各移動のコストが0または1の場合に最短距離を求める．
//
// dist[r][c] == INF：まだ到達していない
// dist[r][c] <  INF：始点からの現在の最小コスト
//
// 通常BFSではqueueを使うが，0-1 BFSではdequeを使う．
//   移動コスト0 → push_front()
//   移動コスト1 → push_back()
// これにより，小さい距離の頂点から優先して処理できる．
//
// 【計算量】
// 4近傍・8近傍のグリッドではO(HW)．
//
// ============================================================
// 注意
//
// 【1】visitedではなくdistの更新判定を使う．
//     0-1 BFSでは，一度到達したマスでも，後からより小さいコストで
//     到達できる場合がある．
//     int nd = dist[r][c] + cost;
//     if (nd >= dist[nr][nc]) continue;
//     dist[nr][nc] = nd;
//
// 【2】移動コストによってdequeへの追加位置を変える．
//     if (cost == 0) dq.push_front({nr, nc});
//     else           dq.push_back({nr, nc});
//   コスト0なら現在位置と距離が同じなので先に処理し，
//   コスト1なら距離が1増えるので後ろへ追加する．
//
// 【3】front()を参照で受けてからpop_front()しない．
//     NG:
//       auto& [r, c] = dq.front();
//       dq.pop_front();      // r，cが無効な参照になる
//     OK:
//       auto [r, c] = dq.front();
//       dq.pop_front();
//
// 【4】4近傍と8近傍
//     for (auto [dr, dc] : DIR4) { ... }
//     for (auto [dr, dc] : DIR8) { ... }
//   必要な方へ変更するだけでよい．
//
// ============================================================
// 実戦用テンプレート
//
// 問題設定例：
// '.' のマスへ移動するコストは0．
// '#' のマスへ移動するコストは1．
// 上下左右へ移動できる．
//
// 始点(sr, sc)から各マスへの最小コストを求める．
// 添字は0-index．
// ============================================================
#if 0

constexpr int INF = 1 << 30;

// 4方向：右，上，左，下
constexpr array DIR4 = {pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}};

// 8方向：右，右上，上，左上，左，左下，下，右下
constexpr array DIR8 = {
    pair{0, 1}, pair{-1, 1}, pair{-1, 0}, pair{-1, -1},
    pair{0, -1}, pair{1, -1}, pair{1, 0}, pair{1, 1}
};

int main() {
    int h, w;   cin >> h >> w;

    vector<string> S(h);
    for (auto& s : S) cin >> s;

    int sr = 0, sc = 0;   // 始点の設定は，問題に応じて変更

    vector dist(h, vector(w, INF));
    deque<pair<int, int>> dq;

    dist[sr][sc] = 0;
    dq.push_front({sr, sc});

    while (!dq.empty()) {
        auto [r, c] = dq.front();
        dq.pop_front();

        for (auto [dr, dc] : DIR4) {
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;

            int cost = (S[nr][nc] == '#');
            int nd = dist[r][c] + cost;

            if (nd >= dist[nr][nc]) continue;   // 最短距離を更新しないならスキップ
            dist[nr][nc] = nd;

            if (cost == 0) dq.push_front({nr, nc});
            else           dq.push_back({nr, nc});
        }
    }

    return 0;
}

#endif

// ============================================================
// 学習用実行例
//
// '.'：移動コスト0
// '#'：移動コスト1
// '#' は通行不可ではなく，コスト1を払えば進めるものとする．
//
// 始点(0, 0)から各マスへ移動するときに，
// '#' を通る最小回数を求める．
// ============================================================
#if 1

constexpr int INF = 1 << 30;

// 4方向：右，上，左，下
constexpr array DIR4 = {pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}};

// 8方向：右，右上，上，左上，左，左下，下，右下
constexpr array DIR8 = {
    pair{0, 1}, pair{-1, 1}, pair{-1, 0}, pair{-1, -1},
    pair{0, -1}, pair{1, -1}, pair{1, 0}, pair{1, 1}
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vector<string> S{
        ".###.",
        "###..",
        "..###",
        "##..#",
        "....#"
    };

    int h = ssize(S), w = ssize(S[0]);  // 高さ，幅
    int sr = 0, sc = 0;                 // 始点の行No，列No

    // 始点からの最小コストdistと，探索用deque
    vector dist(h, vector(w, INF));
    deque<pair<int, int>> dq;

    dist[sr][sc] = 0;           // 始点から始点へのコスト＝0
    dq.push_front({sr, sc});    // 始点をdequeへ追加

    while (!dq.empty()) {
        auto [r, c] = dq.front();   // dequeの先頭要素をコピー
        dq.pop_front();             // dequeの先頭要素を削除

        for (auto [dr, dc] : DIR4) {        // 各方向
            int nr = r + dr, nc = c + dc;   // 移動先の行No，列No

            // グリッドの領域外なら移動できない
            if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;

            // 移動先が'.'ならコスト0，'#'ならコスト1
            int cost = (S[nr][nc] == '#');

            // 現在のマスを経由して移動した場合のコスト
            int nd = dist[r][c] + cost;

            // 現在記録されている距離以上なら更新する必要はない
            if (nd >= dist[nr][nc]) continue;

            // より小さいコストで到達できたので更新
            dist[nr][nc] = nd;

            // コスト0は前へ，コスト1は後ろへ追加
            if (cost == 0) dq.push_front({nr, nc});
            else           dq.push_back({nr, nc});
        }
    }

    cout << "===== グリッド =====\n";
    for (auto& s : S) cout << s << '\n';

    cout << "\n===== 始点からの最小コスト =====\n";
    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (dist[r][c] == INF) cout << " --";
            else                   cout << setw(3) << dist[r][c];
        }
        cout << '\n';
    }

    cout << "\n===== ゴールまでの最小コスト =====\n";
    int gr = h - 1, gc = w - 1;
    cout << "　始点: (" << sr << ", " << sc << ")\n";
    cout << "　終点: (" << gr << ", " << gc << ")\n";
    cout << "　最小コスト: " << dist[gr][gc] << '\n';

    return 0;
}

#endif