#include <iostream>
#include <vector>
#include <string.h>
#include <stack>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <cmath>
using namespace std;

int root(vector<int> &emp,int A){
    int i = A;
    while(emp[i]!=i){
        emp[i] = emp[ emp[i] ] ;
        i = emp[i];
    }
    return i;
}

void union_find(vector<int>& size_emp,vector<int> &emp, int A, int B){
    int root_A, root_B;
    root_A = root(emp,A);
    root_B = root(emp,B);
    emp[root_B] = root_A;
    size_emp[root_A]+=size_emp[root_B];
}

//int find_at_union(int A, int B){
 //   return root(A) == root(B);
//}

int main(){
    int n,att,atk,def;
    cin >> n;
    cin >> att;
    vector<int> emp(n+1);
    vector<int> size_emp(n+1);
    for(int i=1;i<=n;i++){ // set the root of every node
        emp[i] = i;
        size_emp[i] = 1;
    }
    int aux = att;
    while(att--){
        cin >> atk >> def;
        union_find(size_emp,emp,atk,def);
    }
    int empires=0;
    vector<int> check(n+1, 0);
    for(int i=1;i<=n;i++){
       if(check[root(emp,i)] == 0)
            empires++;
       check[root(emp,i)] = 1;


    }
    if(empires==0) cout << 1 << endl;
    else cout << empires << endl;
return 0;
}