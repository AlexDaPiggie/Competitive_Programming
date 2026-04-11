#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
int main(){
    short n; cin >> n; 
    set<short> nums; 
    short number;
    for (int i = 0; i < n; i++) { 
        cin >> number;
        nums.insert(number); 
    }
    cout << nums.size();
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abs/tasks/abc085_b
/*
g++ Kagami_Mochi.cpp -o main.exe
@"
4
10
8
8
6
"@ | ./main.exe
*/