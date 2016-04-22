#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iterator>
#include <queue>
#define MIN(a,b) (a) < (b) ? (a) : (b)
using namespace std;

long long int sum[100001];

int main(){
	long long int n,next,now,x;
	long long cost;
	while(1){
		cin >> n;
		if(!n) break;
		cost=0;
		sum[0] = 0;
		for(int i=1; i<=n;i++){
			cin >> x;
			sum[i] = x + sum[i-1];
			cost+= abs(sum[i]);
		}
		cout << cost << endl;
	}
return 0;
}

