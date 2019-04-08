#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

const int maxn = 1e5+5;
const int logn = log2(maxn) + 5;

int sortIndex[maxn][logn], L[maxn][3], cnt[maxn], temp[maxn][3];
int LCP[maxn], suff[maxn];
int n;

void radixSort(int pos){
    memset(cnt, 0, sizeof cnt);
    for(int i = 0; i < n; i++) cnt[L[i][pos]+1]++;
    for(int i = 1; i <= max(300, n); i++) cnt[i] += cnt[i-1];
    for(int i = 0; i < n; i++){
        int idx = cnt[ L[i][pos] ]++;
        for(int j = 0; j < 3; j++)
            temp[idx][j] = L[i][j];
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 3; j++)
            L[i][j] = temp[i][j];
}

int findLCP(int x, int y, int k){
    int sum = 0;
    for(int i = k; i >= 0 and x < n and y < n; i--)
        if(sortIndex[x][i] == sortIndex[y][i]){
            x += (1 << i);
            y += (1 << i);
            sum += (1  << i);
        }
    return sum;
}

void suffixarray(string s){    
    n = s.size();
    for(int i = 0; i < n; i++)
        sortIndex[i][0] = s[i];
    int k, step;
    for(k = 1, step = 1; step < n; k++, step *= 2){
        for(int i = 0; i < n; i++){
            L[i][0] = sortIndex[i][k-1];
            L[i][1] = (i + step < n ? sortIndex[i+step][k-1] : 0);
            L[i][2] = i;
        }
        radixSort(1); radixSort(0);
        sortIndex[L[0][2]][k] = 0;
        int classes = 1;
        for(int i = 1; i < n; i++){
            if(L[i][0] != L[i-1][0] || L[i][1] != L[i-1][1])
                classes++;
            sortIndex[L[i][2]][k] = classes - 1;
        }
    }
    k--;
    for(int i = 0; i < n; i++)
        suff[ sortIndex[i][k] ] = i;
    for(int i = 1; i < n; i++)
        LCP[i] = findLCP(suff[i-1], suff[i], k);
}

int main(){

    int t; cin >> t;
    while(t--){
        string s; cin >> s;
        s += "$";
        suffixarray(s);
        int res = 0;
        for(int i = 1; i < n; i++){
            int len = n-suff[i]-1;
            res += len - LCP[i];
        }
        cout << res << endl;
    }

    
    return 0;
}
