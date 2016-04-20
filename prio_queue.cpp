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

class prio_queue{
	   private:
       	   int *vetor;
       	   int max;
       	   int elements;
       public:
	       prio_queue(){
	       	   max = 11;
	       	   elements = 0;
			   vetor = (int*)calloc(max,sizeof(int));
		  }
 	   	  void add_element(int);
 	   	  int front_element(void);
 	   	  int empty_queue();
 	   	  int full_queue();
 	   	  void change_value(int,int);
 	   	  int get_front();
 	   	  void heap(int);

};

void prio_queue:: heap(int i){
	int left = i*2;
	int right = i*2+1;
	int greatest = i;
	if(left < elements && vetor[left] > vetor[i])
		greatest = left;
	if(right < elements && vetor[right] > vetor[greatest])
		greatest = right;
	if(greatest != i){
		swap(vetor[greatest],vetor[i]);
		heap(greatest);
	}
}
int prio_queue:: get_front(){
	if(prio_queue::empty_queue()){
		cout << "Queue is empty" << endl;
		return -1;
	}
	int x = vetor[1];
	cout << "Inside get_front() vetor[elements] : " << vetor[elements] << endl;
	vetor[1] = vetor[elements--];
	heap(1);
	return x;
}
void prio_queue:: change_value(int i,int el){
	if(el < vetor[i]){
		cout << "The value is lower than expected. \n" << endl;
		return;
	}
	vetor[i] = el;
	while(vetor[i] > vetor[i/2] && i >1){
		swap(vetor[i],vetor[i/2]);
		i/=2;
	}
	cout << "New element at " << i << " is " << el << endl;
}
int prio_queue:: empty_queue(){
	return elements==0;
}
int prio_queue:: full_queue(){
	return elements == max;
}
void prio_queue:: add_element(int el){
	if(prio_queue:: full_queue()){
		cout << "The queue is full" << endl;
		return;
	}
	vetor[++elements] = -1;
	cout << "elements = " << elements << endl;
	prio_queue::change_value(elements,el);
}

int prio_queue:: front_element(){
	cout << "inside front element element is " << elements << endl;
	if(prio_queue::empty_queue()){
		cout << "Queue is empty" << endl;
		return -1;
	}
	return vetor[1];
}
int main(){
	int n;
	prio_queue p;
	while(1){
		printf("What you up to ? \n");
		printf("0. Quit\n");
		printf("1. Add value\n");
		printf("2. See front\n");
		printf("3. Change value\n");
		printf("4. Remove front\n");
		cin >> n;
		if(!n) break;
		if(n==1){
			int x;
			cout << "Type the value that you want to add" << endl;
			cin >> x;
			p.add_element(x);
		}
		if(n==2)
			cout << "The front value is : " << p.front_element() << endl; 
		if(n==3){
			int index, nV;
			cout << "Type the position and the new value: " << endl;
			cin >> index >> nV;
			p.change_value(index,nV);
		}
		if(n==4)
			cout << p.get_front() << " was removed." << endl;
				
			
			
	}
	cout << endl;
return 0;
}
		