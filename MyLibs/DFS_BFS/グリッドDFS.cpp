#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ============================================================
// グリッドDFS まとめ
//
// 使用頻度：★★★★☆
// 主な用途：到達可能判定，連結成分探索，経路探索
//
// 【BFSとの使い分け】
// ・最短距離・最短経路が必要          → BFS
// ・到達できるか，どれか1経路でよい  → DFS
//
// 【重要】
// ・訪問済みは次のマスへ進む前に更新する．
// ・再帰DFSでは，深さが大きいとスタックオーバーフローに注意．
//   深くなりそうなら非再帰DFS（stack）を使う．
// ・状態が(r,c)だけでない場合は，visitedにも状態を追加する．
//   例：(r,c,dir) → visited[r][c][dir]
//
// 計算量：O(HW)（各マスを高々1回訪問する場合）
//
// ============================================================

// ============================================================
// 【実戦用1】再帰DFS：経路を1つ求める
//
// '#'：壁
// 'S'：始点
// 'G'：ゴール
//
// ゴールまでの経路が存在すれば，移動列をansに保存する．
// 最短経路である保証はない．
// ============================================================
#if 0

// 4方向：右，上，左，下
constexpr array DIR4 = {
    pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}
};
constexpr string DIR_CHAR = "RULD";

int h, w;
vector<string> S;
vector<vector<char>> visited;
string ans;

bool dfs(int r, int c) {
    if (S[r][c] == 'G') return true;

    for (int dir=0; dir<4; dir++) {
        auto [dr, dc] = DIR4[dir];
        int nr = r + dr, nc = c + dc;

        if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;
        if (S[nr][nc] == '#') continue;     // 問題ごとの移動不可条件
        if (visited[nr][nc]) continue;
        visited[nr][nc] = 1;
        if (dfs(nr, nc)) {
            // 再帰から戻る順なので，経路は逆順に追加される
            ans.push_back(DIR_CHAR[dir]);
            return true;
        }
    }
    return false;
}

int main() {
    cin >> h >> w;
    S.resize(h);
    for (auto& s : S) cin >> s;

    int sr = -1, sc = -1;       // 開始地点の設定
    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (S[r][c] == 'S') {
                sr = r;
                sc = c;
            }
        }
    }

    visited.assign(h, vector<char>(w));
    visited[sr][sc] = 1;
    if (dfs(sr, sc)) {
        ranges::reverse(ans);
        cout << "Yes\n";
        cout << ans << '\n';
    }
    else {
        cout << "No\n";
    }
    return 0;
}

#endif


// ============================================================
// 【実戦用2】非再帰DFS：stack＋経路復元
//
// 再帰が深くなりそうな場合はこちらを使用する．
//
// prev_dir[r][c]
//     そのマスへ移動するときに使った方向
//
// ゴールからprev_dirを逆にたどって経路を復元する．
// ============================================================
#if 0

// 4方向：右，上，左，下
constexpr array DIR4 = {
    pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}
};
constexpr string DIR_CHAR = "RULD";

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> S(h);
    for (auto& s : S) cin >> s;

    int sr = -1, sc = -1;   // 開始地点
    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (S[r][c] == 'S') {
                sr = r;
                sc = c;
            }
        }
    }

    vector visited(h, vector<char>(w));
    vector prev_dir(h, vector<int>(w, -1)); // この位置に移動したときの方向
    stack<pair<int,int>> st;    // LIFOでDFSを実装
    visited[sr][sc] = 1;
    st.push({sr, sc});      // 開始地点が1つの場合
    int gr = -1, gc = -1;   // ゴール地点．ゴール発見の判定に使用

    while (!st.empty()) {
        auto [r, c] = st.top();     // 読込
        st.pop();                   // 取り出し（削除）

        if (S[r][c] == 'G') {
            gr = r;
            gc = c;
            break;
        }

        // stackは後入れ先出しなので，
        // 右→上→左→下の順に調べたいなら逆順にpushする
        for (int dir=3; dir>=0; dir--) {
            auto [dr, dc] = DIR4[dir];
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;
            if (S[nr][nc] == '#') continue;     // 問題ごとの移動不可条件
            if (visited[nr][nc]) continue;
            visited[nr][nc] = 1;
            prev_dir[nr][nc] = dir;
            st.push({nr, nc});
        }
    }
    if (gr < 0) {
        cout << "No\n";
        return 0;
    }
    // ゴール → 始点へ逆向きに経路復元
    string ans;
    int r = gr, c = gc;
    while (r != sr || c != sc) {        // 始点に到着するまで
        int dir = prev_dir[r][c];       // 直前からここに移動したときの方向
        ans.push_back(DIR_CHAR[dir]);
        auto [dr, dc] = DIR4[dir];
        r -= dr;                        // 戻るので引く
        c -= dc;
    }
    ranges::reverse(ans);
    cout << "Yes\n";
    cout << ans << '\n';

    return 0;
}

#endif


// ============================================================
// 【学習用】再帰DFS
//
// 始点から到達できるすべてのマスを探索する．
// ============================================================
#if 1

// 4方向：右，上，左，下
constexpr array DIR4 = {
    pair{0, 1}, pair{-1, 0}, pair{0, -1}, pair{1, 0}
};

int h, w;
vector<string> S;
vector<vector<char>> visited;

void dfs(int r, int c) {
    visited[r][c] = 1;

    for (auto [dr, dc] : DIR4) {
        int nr = r + dr, nc = c + dc;

        if (nr < 0 || h <= nr || nc < 0 || w <= nc) continue;
        if (S[nr][nc] == '#') continue;
        if (visited[nr][nc]) continue;

        dfs(nr, nc);
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    S = {
        ".....",
        ".###.",
        "...#.",
        ".#...",
        "....."
    };

    h = ssize(S);
    w = ssize(S[0]);

    int sr = 0, sc = 0;

    visited.assign(h, vector<char>(w));

    dfs(sr, sc);

    cout << "===== グリッド =====\n";
    for (auto& s : S) cout << s << '\n';

    cout << "\n===== 到達可能 =====\n";
    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (S[r][c] == '#')      cout << '#';
            else if (visited[r][c])  cout << 'o';
            else                     cout << '.';
        }
        cout << '\n';
    }

    return 0;
}

#endif


// ============================================================
// 補足
// ============================================================
// 【再帰DFSと非再帰DFS】
//
// 再帰DFS
// ・コードが短く，書きやすい．
// ・再帰から戻る処理を利用して経路を作りやすい．
// ・深い探索ではスタックオーバーフローに注意．
//
// 非再帰DFS
// ・stackを自分で管理する．
// ・再帰の深さを気にしなくてよい．
// ・経路復元にはparentやprev_dirなどを保存する．
//
// ============================================================
// 【訪問済みにするタイミング】
//
// 次の状態へ進むことを決めた時点でvisitedを更新する．
//
// visited[nr][nc] = 1;
// dfs(nr, nc);
//
// または
//
// visited[nr][nc] = 1;
// st.push({nr, nc});
//
// stackから取り出した時点で訪問済みにすると，
// 同じ状態が複数回stackへ入る場合がある．
//
// ============================================================
// 【経路復元：再帰DFS】
//
// 子からゴールへ到達できた場合，戻りながら方向を記録する．
//
// if (dfs(nr, nc)) {
//     ans.push_back(DIR_CHAR[dir]);
//     return true;
// }
//
// ゴール→始点の順に追加されるので，最後にreverseする．
//
// ============================================================
// 【経路復元：非再帰DFS】
//
// 各マスについて「どの方向から来たか」を保存する．
//
// prev_dir[nr][nc] = dir;
//
// ゴールから
//
// auto [dr, dc] = DIR4[dir];
// r -= dr;
// c -= dc;
//
// と逆向きにたどる．
//
// ============================================================
// 【状態が位置だけでない場合】
//
// 今回のように，
//   (r, c, dir)
// が1状態なら，visitedも3次元にする．
//
// vector<vector<array<char, 4>>> visited;
//
// visited[r][c][dir]
//
// 同じマスでもdirが異なれば別状態として探索する．
//
// ============================================================
// 【連結成分の個数】
// 全マスを走査し，未訪問マスからDFSするたびに +1
//
// int cnt = 0;
//
// for (int r=0; r<h; r++) {
//     for (int c=0; c<w; c++) {
//         if (S[r][c] == '#') continue;
//         if (visited[r][c]) continue;
//         dfs(r, c);
//         cnt++;
//     }
// }
//
// 【連結成分のサイズ】
// 1回のDFS中に訪問したマス数を数える
//
// ============================================================
// 【8近傍】
//
// constexpr array DIR8 = {
//     pair{0, 1}, pair{-1, 1}, pair{-1, 0}, pair{-1, -1},
//     pair{0, -1}, pair{1, -1}, pair{1, 0}, pair{1, 1}
// };
//
// DIR4をDIR8へ変更すればよい．
//
// ============================================================