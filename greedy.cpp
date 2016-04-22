#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iterator>
#include <queue>
#define MIN(a,b) (a) < (b) ? (a) : (b)
using namespace std;

bool func(const pair<double, pair<int,int> > &a, const pair<double, pair<int,int> > &b ){
	return a.first > b.first;
}

int mochila(vector< pair<double, pair<int,int> > > &m, int n, int wt){
	int wt_atual=0;
	int pontuacao=0;
	for(int i=0;i<n;i++){
		while(m[i].second.first <= wt - wt_atual){
			pontuacao+= m[i].second.second;
			wt_atual+= m[i].second.first;
		}
	}
	return pontuacao;
}

int main(){
	int n,wt,d,p,c=1;
	while(1){
		cin >> n >> wt;
		if(!n && !wt) break;
		vector< pair<double, pair<int,int> > > m;
		for(int i=0;i<n;i++){
			cin >> d >> p;
			m.push_back( make_pair( (double) p/d, make_pair(d,p) ) );
		}
		sort(m.begin(), m.end(), func);
		printf("Instancia %d\n",c++);
		cout << mochila(m,n,wt) << endl;
		cout << endl;
	}
return 0;
}

