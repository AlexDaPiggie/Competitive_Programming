#include <iostream>
#include <cstdio>
using namespace std;

short n;
short mc = 0;
int* L;

void solve (short i, double p, short c) {
    if (i == n){
        mc = max(mc, c);
        return;
    }
    
    int s = L[i];

    //Right 
    double np = p + s;
    short nc = c;
    if ((np < 0 && p > 0) || (np > 0 && p < 0)) {
        nc += 1;
    }
    solve (i + 1, np, nc);

    //Left
    np = p - s;
    nc = c;    
    if ((np < 0 && p > 0) || (np > 0 && p < 0)) {
        nc += 1;
    }
    solve (i + 1, np, nc);    
}

int main() {
    cin >> n;
    L = new int [n];
    for (short i = 0; i < n; i ++) {
        cin >> L[i];
    }
    solve (0, 0.5, 0);
    cout << mc << endl;
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abc453/tasks/abc453_c
/*
g++ Sneaking_Glances.cpp -o main.exe
@"
5
2 5 2 2 1
"@ | ./main.exe
*/