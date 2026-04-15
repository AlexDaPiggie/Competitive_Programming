#include <iostream>
#include <cstdio>
#include <unordered_set>
using namespace std;

int main() {
    short n; cin >> n;
    unordered_set<short> count;
    short number;
    for (short i = 0; i < n; i++) {
        cin >> number;
        count.insert (number);
    }
    cout << count.size() << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/abc085_b
/*
g++ .\Kagami_Mochi.cpp -o main.exe
@"
7
50
30
50
100
50
80
30
"@ | ./main.exe
*/