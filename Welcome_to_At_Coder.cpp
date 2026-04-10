#include <iostream>
int main(){
    int a, b, c;
    using std::string;
    string s;
    std::cin >> a >> b >> c >> s;
    std::cout << (a + b + c) << " " << s << std::endl; 
    return 0;
}

/*
g++ Welcome_to_At_Coder.cpp -o main.exe
@"
1
2 3
test
"@ | .\main.exe

g++ Welcome_to_At_Coder.cpp -o main.exe
@"
72
128 256
myonmyon
"@ | .\main.exe
*/