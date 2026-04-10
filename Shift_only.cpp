#include <iostream>
#include <cstdio>
using namespace std; 

int main(){
    short n; cin >> n;
    int numbers[n];
    for (int i = 0; i < n; i++){
        cin >> numbers[i];
    }
    short count = 0;
    while (true){
        for (int i = 0; i < n; i++){
            if (numbers[i] % 2 != 0){
                cout << count;
                return 0;
            }
            numbers[i] /= 2;
        }
        count += 1;
        cout << endl;
    }
    return 0;
}


/*
g++ Shift_only.cpp -o main.exe
@"
3
8 12 40
"@ | ./main.exe
*/