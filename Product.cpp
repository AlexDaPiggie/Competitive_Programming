#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    short a,b; cin >> a >> b;
    if (a % 2 == 0 || b % 2 == 0) {
        cout << "Even" << endl;
        return 0;
    }
    cout << "Odd" << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/abc086_a
/*
g++ .\Product.cpp -o main.exe
@"
3 4 
"@ | ./main.exe
*/