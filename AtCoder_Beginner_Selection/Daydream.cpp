#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    string s; cin >> s;
    string words[4] = {"dream", "dreamer", "eraser", "erase"};
    int end = s.length() - 1;
    for (int start = s.length() - 2; start >= 0; start--) {
        int len = end - start + 1;
        string word = s.substr (start, len);
        for (string w : words){
            if (word == w) {
                end = start - 1;
            }
        }
    }
    if (end == -1) {
        cout << "YES" << endl;
        return 0;
    }
    cout << "NO" << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/arc065_a
/*
g++ .\Daydream.cpp -o main.exe
@"
dreameraser
"@ | ./main.exe
*/