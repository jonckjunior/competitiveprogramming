#include <iostream>
#include <vector>
#include <string.h>
#include <stack>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <cmath>
using namespace std;
int cont,max_v;

struct Tree{
	Tree* left;
	Tree* right;
	int info;
};

void insert_tree(Tree *t, int el){
	Tree *aux = t;
	while(1){
		if(aux->info > el){
			if(aux->left == 0){
				aux->left = (Tree*) malloc(sizeof(Tree));
				aux->left->left = 0;
				aux->left->right = 0;
				aux->left->info = el;
				break;
			}
			else
				aux = aux->left;
		}
		else{
			if(aux->right == 0){
				aux->right = (Tree*) malloc(sizeof(Tree));
				aux->right->left = 0;
				aux->right->right = 0;
				aux->right->info = el;
				break;
			}
			else
				aux = aux->right;
		}
	}
		
	
}

void print_tree_pre(Tree* t){ // node, left, right
	if(t==0)
		return;
	cont++;
	if(cont == max_v)
		printf("%d\n",t->info);
	else
		printf("%d ",t->info);
	print_tree_pre(t->left);
	print_tree_pre(t->right);
}

void print_tree_in(Tree *t){ //left, node, right
	if(t == 0)
		return;
	print_tree_in(t->left);
	cont++;
	if(cont == max_v)
		printf("%d\n",t->info);
	else
		printf("%d ",t->info);
	print_tree_in(t->right);
}

void print_tree_post(Tree *t){ // left, right, node
	if(t == 0)
		return;
	print_tree_post(t->left);
	print_tree_post(t->right);
	cont++;
	if(cont == max_v)
		printf("%d\n",t->info);
	else
		printf("%d ",t->info);
}

int main(){
	int n,e,x,c=0;
	cin >> n;
	while(++c<=n){
		cin >> e;
		Tree *t= (Tree*) malloc(sizeof(Tree));
		t->left = 0;
		t->right = 0;
		cont = 0;
		max_v = e;
		cin >> x;
		t->info = x;
		for(int i=1;i<e;i++){
			cin >> x;
			insert_tree(t,x);
		}
		printf("Case %d:\n",c);
		printf("Pre.: ");
		print_tree_pre(t);
		cont = 0;
		printf("In..: ");
		print_tree_in(t);
		cont = 0;
		printf("Post: ");
		print_tree_post(t);
		cout << endl;
	}
	
	return 0;
}
