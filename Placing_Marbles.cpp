#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    string s; cin >> s;
    int count = 0;
    for (int i = 0; i < s.length(); i++){
        if (static_cast<int> (s[i]) != '1') {continue;}
        count += 1;
    }
    cout << count << endl;
    return 0;
}

/*
g++ Placing_Marbles.cpp -o main.exe
@"
000
"@ | ./main.exe
*/