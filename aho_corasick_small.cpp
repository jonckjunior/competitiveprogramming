#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

const int maxlen = 10 + 5;
const int maxsum = 500 + 5;

map<char,int> to[maxsum];
int nodos, leaf[maxsum], link[maxsum];
int adj[maxsum][maxlen];

void add_string(string& s){
    int u = 0;
    for(char c : s){
        if(!to[u].count(c)) to[u][c] = ++nodos;
        u = to[u][c];
    }
    leaf[u] = 1;
}

void build_aho(){
    queue<int> q;
    for(auto par : to[0]){
        adj[0][par.first-'a'] = par.second;
        q.push(par.second);
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = 0; i < maxlen; i++)
            adj[u][i] = adj[link[u]][i];
        for(auto par : to[u]){
            char c = par.first;
            int v = par.second;
            adj[u][c-'a'] = v;
            int j = link[u];
            while(j != 0 and !to[j].count(c)) j = link[j];
            if(to[j].count(c))
                link[v] = to[j][c];
            q.push(v);
        }
    }
}

int main(){
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        string s; cin >> s;
        add_string(s);
    }

    build_aho();
    for(int i = 0; i <= nodos; i++)
        cout << i << " " << link[i] << endl;
    
	return 0;
}
