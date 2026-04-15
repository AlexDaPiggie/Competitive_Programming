#include <iostream>
#include <cstdio>
using namespace std;
short from_2_to_10 (int t, short b, short c) {
    short count = 0;
    short b_range = (t / 2 < b)  ? t / 2 : b;
    for (short i = 0 ; i <= b_range; i++){
        short remainder = t - 2 * i;
        if (c >= remainder) {count += 1;}
    }
    return count; 
}

int main(){
    short a,b,c; cin >> a >> b >> c;
    int y; cin >> y;
    y /= 50;

    if (y < 2) {
        if (c < y) {cout << 0 << endl;}
        else {cout << 1 << endl;}
        return 0;
    }

    else if (y >= 10) {
        short a_range = (y / 10 < a) ? y / 10 : a;
        short count = 0;
        for (short i = 0; i <= a_range; i++) {
            short remainder = y - 10 * i;
            count += from_2_to_10(remainder, b, c);
        }
        cout << count << endl;
        return 0;
    }

    else {
        cout << from_2_to_10(y, b, c);
        return 0;
    }

    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/practice_1
/*
g++ .\Coins.cpp -o main.exe
@"
2
2
2
100
"@ | ./main.exe
*/