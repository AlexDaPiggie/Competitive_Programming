#include <iostream>
#include <cstdio>
using namespace std;
struct Pair {
    short b, c;
};

Pair from_5_to_10 (short n, int y){
    for (short b = 0; b <= y / 5; b++) {
        short c = y - 5*b;
        if (b + c == n) {
            return Pair {b, c};
        }
        else if (b + c < n){
            return Pair {-1, -1};
        }
    }
    return Pair {-1, -1};
}

void print_result (short a, short b, short c) {
    cout << a << " " << b << " " << c << endl;
    return;
}
int main(){
    short n; cin >> n;
    int y; cin >> y;
    y /= 1000;
    if (y < 5) {
        if (n == y){
            print_result(0, 0, y);
        }
        else {
            print_result(-1, -1, -1);
        }
        return 0;
    }

    else if (y >= 5 && y < 10) {
        Pair bc = from_5_to_10(n, y);
        if (bc.b == -1){
            print_result(-1, -1, -1);
        }
        else {
            print_result(0, bc.b, bc.c);
        }
        return 0;
    }

    else {
        for (short a = 0; a <= y / 10 ; a++) {
            int remainder = y - 10 * a;
            Pair bc = from_5_to_10(n - a, remainder);
            if (bc.c == -1){continue;}
            else {
                print_result(a, bc.b, bc.c);
                return 0;
            }
        }
        print_result(-1, -1, -1);
        return 0;
    }
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/abc085_c
/*
g++ .\Otoshidama.cpp  -o main.exe
@"
20 196000
"@ | ./main.exe
*/