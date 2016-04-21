#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <sstream>
#include <iterator>
using namespace std;
#define MAX(a,b) (a) > (b) ? (a) : (b)
#define MIN(a,b) (a) < (b) ? (a) : (b)

int root(int A, vector<int>& id){
	int i = A;
	while(id[i] != i){
		id[i] = id[id[i]];
		i = id[i];
	}
	return i;
}

void union_find(int A, int B, vector<int>& id, vector<int>& size_union){
	int root_A = root(A,id);
	int root_B = root(B,id);
	if(size_union[A] > size_union[B]){
		id[root_B] = root_A;
		size_union[root_A] += size_union[root_B];
	}
	else{
		id[root_A] = root_B;
		size_union[root_B] += size_union[root_A];
	}
	
}

long long int kruskal(vector< pair< long long int, pair<int,int> > >& g, int e){
	vector< int > id(e+1);
	vector< int > size_union(e+1,1);
	for(int i=1;i<=e;i++)
		id.at(i) = i;
	sort(g.begin(),g.end());
	long long int cost,sum=0;
	int x, y;
	for(int i=0 ; i< e; i++){
		cost = g[i].first;
		x = g[i].second.first;
		y = g[i].second.second;
		if(root(x,id)!= root(y,id)){
			sum+=cost;
			union_find(x,y,id,size_union);
		}
	}
	
	return sum;
}

int main(){
	int v,e;
	while(1){
		cin >> v >> e;
		if(!v && !e) break;		
		vector< pair< long long int, pair<int,int> > > g;
		int x,y,cost;
		long long int total_cost=0;
		for(int i=0; i<e;i++){
			cin >> x >> y >> cost;
			total_cost+=cost;
			g.push_back(make_pair(cost, make_pair(x,y) ) );
		}
		
		cout << total_cost-kruskal(g,e) << endl;
	}
return 0;
}
