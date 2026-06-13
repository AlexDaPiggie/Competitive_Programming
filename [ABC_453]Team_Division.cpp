#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

long long mod = 998244353;

long long power(long long base, int exp) {
    base %= mod;
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 != 0){result = (result * base) % mod;}
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

struct Pair {
    vector<long long> fact, inv_fact;
};

Pair precompute (int n) {
    vector<long long> fact(n + 1);
    fact[0] = fact[1] = 1;
    for (int i = 2; i < n + 1; i ++ ){
        fact[i] = (fact[i - 1] * i) % mod; 
    }
    vector <long long> inv_fact(n + 1);
    inv_fact[n] = power(fact[n], mod - 2) % mod;
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    }
    return {fact, inv_fact};
}

long long combination (int n, int k, vector<long long>& fact, vector <long long>& inv_fact) {
    return (fact[n] * inv_fact[k]) % mod * inv_fact[n - k] % mod;
}

int main () {
    int n; cin >> n;
    vector<long long> ft, invft;
    Pair something = precompute(n);
    ft = something.fact;
    invft = something.inv_fact;

    vector<int> L(n), R(n);
    L[0] = 0;
    R[0] = 0;
    for (int i = 0; i < n; i ++ ) {
        cin >> L[i] >> R[i];
    }

    vector<int> onlyA(n + 1, 0), onlyB(n + 1, 0), both(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int al = L[i], ar = R[i];
        int bl = n - R[i], br = n - L[i];

        //only a
        if (al < bl) {
            int end = min (ar, bl - 1);
            onlyA[al]++;
            onlyA[end + 1]--;
        }

        if (ar > br){
            int start = max(br + 1, al);
            onlyA[start]++;
            onlyA[ar + 1]--;
        }
        
        //only b 
        if (bl < al) {
            int end = min (br, al - 1);
            onlyB[bl]++;
            onlyB[end + 1]--;
        }

        if (br > ar){
            int start = max(ar + 1, bl);
            onlyB[start]++;
            onlyB[br + 1]--;
        }
        
        //both 
        int flstart = max (al, bl);
        int flend = min(ar, br);
        if (flstart <= flend){
            both[flstart]++; 
            both[flend + 1]--;
        }
    }

    int countA = 0, countB = 0, countBoth = 0;
    long long result = 0;
    for (int a = 0; a < n + 1; a ++ ){
        countA += onlyA[a];
        countB += onlyB[a];
        countBoth += both[a];
        
        if (countA + countB + countBoth != n)  {continue;}
        int b = n - a;
        if (countA > a || countB > b) {continue;}
        int a_missing = a - countA;
        if (a_missing > countBoth || a_missing < 0) {continue;}
        result = (result + combination (countBoth, a_missing, ft, invft)) % mod;
        
    }
    cout << result << endl;
    return 0;
}

/*
g++ Team_Division.cpp -o main.exe
@"
6
1 5
1 5
2 5
1 3
3 5
2 5
"@ | ./main.exe
*/