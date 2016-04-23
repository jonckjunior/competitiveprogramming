#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iterator>
#include <queue>
#define MIN(a,b) (a) < (b) ? (a) : (b)
using namespace std;
int g[5][5];
int mark[5][5];
bool cops=false;
void bfs(int x, int y){
	if(x>=5 || y>=5 || x<0 || y < 0 || cops || g[x][y] == 1) return;
	if(x==4 && y==4){
		cops = true;
		return;
	}
	g[x][y] = 1;
	bfs(x,y+1); //one right
	bfs(x,y-1); // one left
	bfs(x+1,y); // one down
	bfs(x-1,y); // one up
}

int main(){
	int n;
	cin >> n;
	while(n--){
		cops = false;
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				cin >> g[i][j];
		bfs(0,0);
		if(cops) cout << "COPS" << endl;
		else cout << "ROBBERS" << endl;
		
	}
return 0;
}

