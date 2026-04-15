#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    short a,b,c; cin >> a >> b >> c;
    string s; cin >> s;
    cout << a + b + c << " " << s << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/practice_1
/*
g++ .\Welcome_to_AtCoder.cpp -o main.exe
@"
1
2 3
test
"@ | ./main.exe
*/