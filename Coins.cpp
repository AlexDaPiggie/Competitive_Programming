#include <iostream>
#include <cstdio>
using namespace std;

int from_2_to_10(int b, int c, int x){
    int divisor_2 = x / 2;
    if (b < divisor_2){divisor_2 = b;}
    short count = 0;
    for (short divisor = divisor_2; divisor > -1; divisor--){
        short remain = x - 2 * divisor;
        if (remain > c){return count;}
        count += 1;
    }
    return count;
}

int from_10_above(int a, int b, int c, int x){
    int divisor_10 = x / 10;
    if (divisor_10 > a){divisor_10 = a;}
    short count = 0;
    for (short divisor = divisor_10; divisor > -1; divisor--){
        short remain = x - 10 * divisor;
        short ways = from_2_to_10(b, c, remain);
        if (ways == 0){return count;}
        count += ways;
    }
    return count;
}

int main(){
    short a,b,c; cin >> a >> b >> c;
    int x; cin >> x;
    x /= 50;
    if (x < 2){
        cout << 1;
        return 0;
    }
    else if ((x > 1) & (x < 10)){
        cout << from_2_to_10(b, c, x);
        return 0;
    }
    else {
        cout << from_10_above(a, b, c, x);
        return 0;
    }
    return 0;
}

/*
g++ Coins.cpp -o main.exe
@"
2
2
2
100
"@ | ./main.exe
*/