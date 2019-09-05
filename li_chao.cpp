// problem: https://atcoder.jp/contests/dp/tasks/dp_z
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct line{
    ll a, b;
    line(ll aa, ll bb){a = aa; b = bb;}
    line(){}
    ll get(ll x){return a*x + b;}
};

int left(int u){return (u << 1);}
int right(int u){return (u << 1) + 1;}

ll v[1000005], dp[1000005];
line tree[4000005];

void update(int u, int L, int R, line aux){
    ll a = aux.get(L);
    ll b = tree[u].get(L);
    ll c = aux.get(R);
    ll d = tree[u].get(R);
    if(a <= b and c <= d){ //aux is better than the tree[u] in the whole interval [L,R]
        tree[u] = aux;
        return;
    }
    if(a >= b and c >= d) //aux is worse than the tree[u] in the whole interval [L,R]
        return;
    // we will update at max O(log n) intervals
    // because, if the best interval for the aux line is some interval [x, y]
    // then we know by definition from segtree that we can break the interval [x, y]
    // into O(log n) nodes and update those nodes
    int mid = (L+R)/2;
    update(left(u), L, mid, aux);
    update(right(u), mid+1, R, aux);
}

ll query(int u, int L, int R, int pos){
    ll res = tree[u].get(pos);
    if(L == R) return res;
    int mid = (L+R)/2;
    if(pos <= mid) res = min(res, query(left(u), L, mid, pos));
    else           res = min(res, query(right(u), mid+1, R, pos));
    return res;
}

int main(){

    ll n, k; cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> v[i];
    for(int i = 1; i <= 4*n; i++)
        tree[i] = line(0, 1e18);
    
    
    update(1, 1, n, line(-2*v[1], v[1]*v[1]));
    for(int i = 2; i <= n; i++){
        // for every j < i
        // dp[i] = min(dp[i], EQ)
        // EQ = dp[j] + (v[i] - v[j])² + k
        // EQ = dp[j] + k + v[i]² -2.v[i].v[j] + v[j]²
        // EQ = v[i]² + k + (-2.v[j].v[i] + v[j]² + dp[j])
        // (-2.v[j].v[i] + v[j]² + dp[j]) is the equation of
        //      a line Y = -2.v[j].x + v[j]² + dp[j] evaluated at point x = v[i]
        //      see that Y(v[i]) = -2.v[j].v[i] + v[j]² + dp[j]
        // we want to find the line that evaluates the minium at point v[i]
        ll val = query(1, 1, 1e6, v[i]);
        dp[i] = v[i]*v[i] + k + val;
        line aux(-2*v[i], v[i]*v[i] + dp[i]);
        update(1, 1, 1e6, aux);
    }
    cout << dp[n] << endl;
    return 0;
}
