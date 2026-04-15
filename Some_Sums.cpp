#include <iostream>
#include <cstdio>
using namespace std;
short sum_digits (int x){
    short total = 0;
    while (x != 0){
        total += x % 10;
        x /= 10;
    }
    return total;
}
int main() {
    short n; cin >> n;
    short a, b; cin >> a >> b;
    short total;
    int result = 0;
    for (short i = 0; i <= n; i++) {
        short total = sum_digits (i);
        if (total < a || total > b) {continue;}
        result += i;
    }
    cout << endl;
    cout << result << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/abc083_b
/*
g++ .\Some_Sums.cpp -o main.exe
@"
20 2 5
"@ | ./main.exe
*/