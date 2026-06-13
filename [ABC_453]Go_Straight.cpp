#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char directions[] = {'L', 'R', 'U', 'D'};

struct Position {
    int x, y, dir;
};

int main () {
    int h, w; cin >> h >> w;
    vector<string> space(h);

    int sx, sy, gx, gy;
    
    for (int i = 0; i < h; i ++ ) {
        cin >> space[i];
        for (int j = 0; j < w; j ++ ) {
            if (space[i][j] == 'S') {sx = i; sy = j;}
            else if (space[i][j] == 'G') {gx = i; gy = j;}
        }
    }
        
    vector<int> parents (h * w * 5, -1);
    queue<Position> q;
    q.push ({sx, sy, 4});
    parents[(sx * w + sy) * 5 + 4] = -2;
    Position target = {-1, -1, -1};

    while (!q.empty()) {
        Position curr = q.front();
        q.pop();
        if (curr.x == gx && curr.y == gy) {
            target = curr;
            break;
        }
        
        char cond = space[curr.x][curr.y];
        for (int nd = 0; nd < 4; nd++) {
            int nx = curr.x + dx[nd];
            int ny = curr.y + dy[nd];
    
            bool can_move = false;
            if (cond == 'S' || cond == 'G' || cond == '.'){can_move = true;}
            else if (cond == 'o' && curr.dir == nd) {can_move = true;}
            else if (cond == 'x' && curr.dir != nd) {can_move = true;}

            if (can_move) {
                if (nx < 0 || nx >= h || ny < 0 || ny >= w || space[nx][ny] == '#') {continue;}
                int n_id = (nx * w + ny) * 5 + nd;
                if (parents [n_id] != -1) {continue;}
                parents[n_id] = (curr.x * w + curr.y) * 5 + curr.dir;
                q.push ({nx, ny, nd});
            }
        }
    }
    
    if (target.x == -1) {
        cout << "No" << endl;
    }
    else {
        string path = "";
        cout << "Yes" << endl;
        int curr_id = (target.x * w + target.y) * 5 + target.dir;
        while (true) {
            if (parents[curr_id] == -2) {break;}
            char curr_dir = directions[curr_id % 5];
            path += curr_dir;
            curr_id = parents[curr_id];
        }
        reverse (path.begin(), path.end());
        cout << path;
    }

    return 0;
}

//Link Problem:
/*
g++ Go_Straight.cpp -o main.exe
@"
3 5
.#...
.Sooo
..x.G
"@ | ./main.exe
*/