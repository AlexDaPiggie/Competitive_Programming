#include <iostream>
#include <cstdio>
using namespace std;
struct Position {
    int x, y;
};

int main(){
    int n; cin >> n;
    int x, y, t;
    int prev_t = 0;
    Position prev_pos = {0, 0};
    for (int i = 0 ; i < n; i++) {
        cin >> t >> x >> y;
        int dx = x - prev_pos.x;
        int dy = y - prev_pos.y;
        int steps = abs(dx) + abs(dy);
        int dt = t - prev_t;
        if (steps > dt || (steps - dt) % 2 != 0) {
            cout << "No" << endl;
            return 0;
        }
        prev_t = t;
        prev_pos = {x, y};
    }
    cout << "Yes" << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/arc089_a
/*
g++ .\Traveling.cpp -o main.exe
@"
2
3 1 2
6 1 1
"@ | ./main.exe
*/