#include <iostream>
#include <cstdio>
using namespace std;

int main () {
    short n; cin >> n;
    string s; cin >> s;
    string result = "";
    for (short i = 0; i < n; i++) {
        if (s[i] != 'o') {
            result = s.substr (i);
            break;
        }
    }
    cout << result;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abc453/tasks/abc453_a
/*
g++ Trimo.cpp -o main.exe
@"
7
ooparts
"@ | ./main.exe
*/