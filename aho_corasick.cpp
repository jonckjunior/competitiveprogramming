#include <bits/stdc++.h>
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1141
using namespace std;
typedef pair<int,int> ii;
typedef vector<int> vi;

struct Node{
    map<char,int> child;
    set<int> output;
    int mark, fail;
};

Node trie[1000005];
int nodes, dp[10005];
vector<vi> adj;

void addTrie(string& s, int i){
    int atual = 0;
    for(char c : s){
        if(trie[atual].child.count(c) == 0){
            trie[atual].child[c] = ++nodes;
            trie[nodes].child.clear();
            trie[nodes].mark = trie[nodes].fail = 0;
            trie[nodes].output.clear();
        }
        atual = trie[atual].child[c];
    }
    trie[atual].output.insert(i);
    trie[atual].mark = 1;
}

void build(){
    queue<int> q;
    for(ii chave: trie[0].child){
        int s = chave.second;
        q.push(s);
        trie[s].fail = 0;
    }
    while(!q.empty()){
        int r = q.front(); q.pop();
        for(ii chave : trie[r].child){
            int s = chave.second, state = trie[r].fail;
            char c = chave.first;
            while(trie[state].child.count(c) == 0 && state > 0)
                state = trie[state].fail;
            if(trie[state].child.count(c) == 0)
                state = 0;
            else
                state = trie[state].child[c];
            trie[s].fail = state;
            trie[s].output.insert(trie[state].output.begin(), trie[state].output.end());
            q.push(s);
        }
    }
}

set<int> process(string &s){
    int state = 0;
    set<int> res;
    for(char c : s){
        while(trie[state].child.count(c) == 0 && state > 0)
            state = trie[state].fail;
        if(trie[state].child.count(c) == 0)
            state = 0;
        else
            state = trie[state].child[c];
        res.insert(trie[state].output.begin(), trie[state].output.end());
    }
    return res;
}

int solve(int u){
    if(dp[u] != -1) return dp[u];
    int res = 1;
    for(int v : adj[u])
        if(v != u)
            res = max(res, solve(v)+1);
    return dp[u] = res;
}

int main(){
    ios::sync_with_stdio(false);
    int n;
    while(cin >> n, n != 0){

        trie[0].child.clear();
        trie[0].mark = trie[0].fail = 0;
        trie[0].output.clear();
        nodes = 0;

        vector<string> vs;
        adj.assign(n+5, vi());
        memset(dp, -1, sizeof dp);

        for(int i = 0; i < n; i++){
            string s; cin >> s;
            vs.push_back(s);
            addTrie(s, i);
        }
        build();
        for(int i = 0; i < n; i++){
            set<int> res = process(vs[i]);
            for(int v : res){
                //printf("%d %d\n", i, v);
                adj[i].push_back(v);
            }
        }
        int res = 0;
        for(int i = 0; i < n; i++)
            if(dp[i] == -1)
                res = max(res, solve(i));
        cout << res << endl;
    }
    return 0;
}
