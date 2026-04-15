#include <iostream>
#include <cstdio>
using namespace std;
short factor (int x){
    short f = 0;
    int n = 2;
    while (x % n == 0) {
        f += 1; 
        n *= 2;
    }
    return f;
}

int main () {
    short n; cin >> n;
    int number; cin >> number;
    short min_factor = factor (number);
    for (short i = 1; i < n; i++ ) {
        cin >> number;
        short cur_factor = factor (number);
        min_factor = (cur_factor < min_factor) ? cur_factor : min_factor;
    }
    cout << min_factor << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/abc081_b
/*
g++ .\Shift_only.cpp -o main.exe
@"
3
8 12 40
"@ | ./main.exe
*/