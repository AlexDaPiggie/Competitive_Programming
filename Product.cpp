#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    int a, b;
    cin >> a >> b; 
    if ((a * b) % 2 == 0){
        cout << "Even";
    }
    else {
        cout << "Odd";
    }
    return 0;
}

/*
g++ Product.cpp -o main.exe
@"
1 10000
"@ | ./main.exe
*/