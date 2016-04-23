#include <iostream>
#include <vector>
#include <string.h>
#include <stack>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <iterator>
using namespace std;
#define BRANCO 0
#define CINZA 1
#define PRETO 2
bool cycle;

void BFS(vector<int> *g, int u, vector<int> &cor){
	cor[u] = CINZA;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end();it++){
		if(cor[*it] == BRANCO){
			BFS(g,*it,cor);
		}
		else if(cor[*it] == CINZA){
			cycle = true;
		}
	}
	cor[u] = PRETO;
}

int main(){
	int n,V,E,x,y;
	cin >> n;
	while(n--){
		cin >> V >> E;
		vector<int> g[V+1];
		for(int i=0;i<E;i++){
			cin >> x >> y;
			g[x].push_back(y);
		}
		cycle = false;
		vector<int> cor(V+1, BRANCO);
		for(int i=1;i<=V;i++){
				if(cor[i] == BRANCO)
					BFS(g,i,cor);
		}
		if(cycle) cout << "SIM" << endl;
		else cout << "NAO" << endl;
		
	}
}

