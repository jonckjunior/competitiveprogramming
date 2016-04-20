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

void heap(int *vetor, int n, int i){
	int left = i*2;
	int right = i*2+1;
	int greatest = i;
	if(left <=n && vetor[left] > vetor[i])
		greatest = left;
	if(right <=n && vetor[right] > vetor[greatest])
		greatest = right;
	if(greatest != i){
		swap(vetor[i], vetor[greatest]);
		heap(vetor, n, greatest);
	}
}


void create_heap(int *vetor, int n){
	for(int i=n/2;i>=1;i--){
		heap(vetor , n, i);
	}
}

void heap_sort(int *vetor, int n){
	int heap_size = n;
	int i;
	for(int i=2;i<=n;i++){
		swap(vetor[heap_size], vetor[1]);
		heap_size--;
		create_heap(vetor, heap_size);		
	}
	
}

int main(){
	int n;
	printf("Digite o numero de elementos: \n");
	cin >> n;
	int vetor[n+1];
	for(int i=1;i<=n;i++)
		cin >> vetor[i];
	create_heap(vetor,n);
	heap_sort(vetor,n);
	for(int i=1;i<=n;i++)
		printf("%d ",vetor[i]);
	cout << endl;
return 0;
}
