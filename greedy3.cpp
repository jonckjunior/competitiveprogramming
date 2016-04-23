#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iterator>
#include <queue>
#define MIN(a,b) (a) < (b) ? (a) : (b)
using namespace std;

int main(){
	int n,wt,ing,qtdbolo,qtding,indice,qtd;
	cin >> n;
	while(n--){
		cin >> wt >> ing >> qtdbolo;
		int ingredientes[ing];
		for(int i=0;i<ing;i++)
			cin >> ingredientes[i];
		vector<long long int> bolos(qtdbolo);
		for(int i=0;i<qtdbolo;i++){
			long long custo=0;
			cin >> qtding;
			for(int j=0;j<qtding;j++){
				cin >> indice >> qtd;
				custo+= ingredientes[indice] * qtd;
			}
			bolos[i] = custo;
		}
		sort(bolos.begin(),bolos.end());
		int k=0,cBolo=0,numbolos=0;
		while(cBolo<wt){
			if(bolos[k] + cBolo <= wt){
				cBolo+=bolos[k];
				numbolos++;
			}
			else if(k<qtdbolo)
				k++;
			else
				break;

				
		}
		cout << numbolos << endl;
	}	
return 0;
}

