#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    short count = 0;
    string s; cin >> s;
    for (short i =0; i < 3; i++) {
        if (s[i] == '1') {
            count += 1;
        }
    }
    cout << count << endl;
    return 0;
}


//Link Problem: https://atcoder.jp/contests/abs/tasks/abc081_a
/*
g++ .\Placing_Marbles.cpp -o main.exe
@"
101
"@ | ./main.exe
*/