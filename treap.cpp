#include <bits/stdc++.h>
using namespace std;

struct node{
    int key, prior, len;
    node *left, *right;
    int rev;
    node(int val){
        key = val;
        prior = rand();
        left = right = 0;
        len = 0;
    }
};
typedef node* pnode;

void update(pnode& root){
    if(root){
        root->len = 0;
        if(root->left) root->len += root->left->len+1;
        if(root->right) root->len += root->right->len+1;
    }
}

void updateRev(pnode &root){
    if(!root or !(root -> rev)) return;
    swap(root -> left, root -> right);
    if(root -> left) root -> left -> rev ^= 1;
    if(root -> right) root -> right -> rev ^= 1;
    root -> rev = 0;
}

pnode merge(pnode& esq, pnode& dir){
    updateRev(esq); updateRev(dir);
    if(esq == NULL) return dir;
    if(dir == NULL) return esq;
    if(esq->prior > dir->prior){
        pnode aux = merge(esq->right, dir);
        esq->right = aux;
        update(esq);
        return esq;
    }
    else{
        pnode aux = merge(esq, dir->left);
        dir->left = aux;
        update(dir);
        return dir;
    }
}

pair<pnode,pnode> split(pnode& root, int key){
    update(root);
    if(root == NULL) return {NULL, NULL};
    if(root->key < key){
        auto aux = split(root->right, key);
        root->right = aux.first;
        update(root); update(aux.second);
        return {root, aux.second};
    }
    else{
        auto aux = split(root->left, key);
        root->left = aux.second;
        update(aux.first); update(root);
        return {aux.first, root};
    }
}

pair<pnode,pnode> split(pnode& root, int key, int add){
    updateRev(root);
    if(root == NULL) return {NULL, NULL};
    int totL = root -> left ? root -> left -> len + 1 : 0;
    if(totL + add < key){
        auto aux = split(root -> right, key, add + totL + 1);
        root -> right = aux.first;
        update(root); update(aux.second);
        return {root, aux.second};
    } else {
        auto aux = split(root -> left, key, add);
        root -> left = aux.second;
        update(aux.first); update(root);
        return {aux.first, root};
    }
}

void insert(pnode& root, pnode novo){
    auto spl = split(root, novo->key);
    auto newroot = merge(spl.first, novo);
    root = merge(newroot, spl.second);
}

void insert(pnode& root, pnode novo, int idx){
    auto spl = split(root, idx, 0);
    auto newroot = merge(spl.first, novo);
    root = merge(newroot, spl.second);
}

void erase(pnode& root, int key){
    auto spl = split(root, key);
    auto spl2 = split(spl.second, key+1);
    root = merge(spl.first, spl2.second);
}

int findNth(pnode& root, int val, int add){
    if(root == NULL) return -1;
    updateRev(root);
    int totL = (root -> left ? root -> left -> len+1 : 0);
    if(totL + add == val) return root -> key;
    //int totR = root -> right ? root -> right -> len ? 0;
    if(totL + add < val){
        return findNth(root -> right, val, totL + add + 1);
    } else {
        return findNth(root -> left, val, add);
    }
}

void printTreeAux(pnode& root){
    if(root == NULL) return;
    updateRev(root);
    printTreeAux(root->left);
    cout << root->key << " " << root->len << endl;
    printTreeAux(root->right);
}


void printTree(pnode& root){
    printTreeAux(root);
    cout << endl;
}

void reverseseg(pnode& root, int esq, int dir){
    auto r1 = split(root, esq, 0);
    auto r2 = split(r1.second, dir+1-esq, 0);
    r2.first->rev ^= 1;
    auto r3 = merge(r2.first, r2.second);
    root = merge(r1.first, r3);
}

int main(){
    cout.sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));

    pnode root = NULL;
    int n, esq, dir; cin >> n >> esq >> dir;
    esq--; dir--;

    for(int i = 0; i < n; i++){
        char c; cin >> c;
        insert(root, new node(c), i);
    }
    int q; cin >> q;
    while(q--){
        string op; cin >> op;
        if(op == "S"){
            string s1, s2; cin >> s1 >> s2;
            if(s1 == "L"){
                if(s2 == "L") esq--;
                else esq++;
            }
            else{
                if(s2 == "L") dir--;
                else dir++;
            }
        }
        else if(op == "R"){
            reverseseg(root, esq, dir);        
        }
        else{
            string aux; cin >> aux;
            if(aux == "L") cout << (char)findNth(root, esq, 0);
            else cout << (char)findNth(root, dir, 0);
        }
    }
    cout << endl;
	return 0;
}
