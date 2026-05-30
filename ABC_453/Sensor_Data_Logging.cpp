#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int main () {
    short t, x; cin >> t >> x;
    short a; cin >> a;
    map<short, short> result;
    result[0] = a;
    short prev_idx = 0;
    for (short i = 1; i <= t; i++) {
        cin >> a;
        if (abs(a - result[prev_idx]) >= x) {
            result[i] = a;
            prev_idx = i; 
        }
    }
    for (auto& [key, value]: result) {
        cout << key << " " << value << endl;
    }
    return 0;
}

//Link Problem: https://atcoder.jp/contests/abc453/tasks/abc453_b
/*
g++ .\Sensor_Data_Logging.cpp -o main.exe
@"
6 10
30 35 40 21 30 12 31
"@ | ./main.exe
*/