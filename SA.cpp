#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> iii;

int sortIndex[100015][50], freq[100015], LCP[100015], SA[100015], DP[100015], n;
vector<iii> L, temp;

void solve(int pos){
	memset(freq, 0, sizeof freq);
	int maxi = max(300, n+5);
	for(int i = 0; i < n; i++){
		int x;
		if(pos == 0) x = get<0>(L[i]);
		else if(pos == 1) x = get<1>(L[i]);
		else x = get<2>(L[i]);
		freq[x]++;
	}
	int sum = 0;
	for(int i = 0; i < maxi; i++){
		int aux = freq[i];
		freq[i] = sum;
		sum += aux;
	}
	for(int i = 0; i < n; i++){
		int x;
		if(pos == 0) x = get<0>(L[i]);
		else if(pos == 1) x = get<1>(L[i]);
		else x = get<2>(L[i]);
		temp[freq[x]++] = L[i];
	}
	for(int i = 0; i < n; i++)
		L[i] = temp[i];
}

int findLCP(int x, int y){
	int maxi = log2(n)+1;
	int len = 0;
	for(int k = maxi; k >= 0 and x < n and y < n; k--)
		if(sortIndex[x][k] == sortIndex[y][k]){
			x += (1 << k);
			y += (1 << k);
			len += (1 << k);
		}
	return len;
}


int main(){
    cout.sync_with_stdio(false);
    cin.tie(nullptr);
	string s; cin >> s;
	n = s.size();
	L.resize(n);
	temp.resize(n);
	memset(LCP, 0, sizeof LCP);
	memset(DP, 0, sizeof DP);
	memset(SA, 0, sizeof SA);
	
	int maxi = log2(n) + 1;

	for(int i = 0; i < n; i++)
		sortIndex[i][0] = s[i];

	for(int k = 1, step = 1; k <= maxi; k++, step *= 2){

		for(int i = 0; i < n; i++){
			if(i+step < n)
				L[i] = iii(sortIndex[i][k-1], sortIndex[i+step][k-1], i);
			else
				L[i] = iii(sortIndex[i][k-1], 0, i);
		}

		solve(2);
		solve(1);
		solve(0);
		// sort(L.begin(), L.end());

		int pos = 0;
		for(int i = 0; i < n; i++){
			int x = get<0>(L[i]), y = get<1>(L[i]), idx = get<2>(L[i]);
			if(i > 0 and get<0>(L[i-1]) == x and get<1>(L[i-1]) == y)
				sortIndex[idx][k] = pos;
			else
				sortIndex[idx][k] = ++pos;
		}
	}

	for(int i = 0; i < n; i++)
		SA[ sortIndex[i][maxi]-1 ] = i;

	int res = 0, idx = 0;
	for(int i = 0; i < n-1; i++)
		LCP[i] = findLCP(SA[i], SA[i+1]);

    return 0;
}
