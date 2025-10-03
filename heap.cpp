#include <iostream>

/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION
*/


#include "heap.h"

// gives us the index of the parent for the element at index 'i'
int Heap::parent(int i) 
{
	if(i==0) return -1; // dummy return
	if(i%2==0) return (i-2)/2;
	return (i-1)/2;
}


// gives us the index of the left child for the element at index 'i'
int Heap::left(int i) 
{
	return 2*i+1; // dummy return
}


// gives us the index of the right child for the element at index 'i'
int Heap::right(int i) 
{
	return 2*i+2; //dummy
}


// gives us the maximum element in the heap
int Heap::max() 
{
	return store[0]; //dummy
}


//swaps the elements at indices 'i' and 'j' in the store array
// Do not forget to increment the swap_count
void Heap::swap(int i, int j) 
{
	std::swap(store[i],store[j]);
	swap_count++;
}


// inserts elements into the store array
// can use the helper function append in heap.h
void Heap::insert(int v) 
{
	append(v);
	int i=sz-1;
	while(parent(i)!=-1 && store[parent(i)]<v){
		Heap::swap(parent(i),i);
		i = parent(i);
	}
}

// makes the subtree rooted at index 'i' follow the Max Heap property
// HINT: calls the swap and recusively goes down the subtree
void Heap::heapify(int i) 
{		
	int siz = sz;
	if(i>=siz) return;
	int r,l,m;
	bool ry = false, ly=false;
	if (right(i)<siz) {r = store[right(i)]; ry=true;}
	if(left(i)<siz){ l = store[left(i)]; ly = true;}
	m = store[i];
	if(ry && ly){
		if( r>m && r>=l) {
			swap(right(i),i);
			heapify(right(i));
		} else if(l>m && l>=r){
			swap(left(i),i);
			heapify(left(i));
		}
	}else if (ly && l>m)
	{
		swap(left(i),i);
		heapify(left(i));
	} 
	return;
}

// deletes the maximum element and makes the remaining tree follow the max heap property
// HINT: calls the heapify
void Heap::deleteMax() 
{
	Heap::swap(0,sz-1);
	removeLast();
	heapify(0);
}


// rearranges the array such that it follows the max heap property
// HINT: calls the heapify
// HINT: for efiicient building follow a bottom-up approach
void Heap::buildHeap() 
{
	for(int i=sz-1; i>=0; i--){
		heapify(i);
	}
}


// used to arrange the elements in descending order
// The sorted elemendts must be stored in the 'store' array
// Can use a temporary vector to sort
// HINT: Since you are using a temporary vector to sort, make sure to apply the heapify logic on that temporary vector
// and also increment the swap count whenever you perform a swap
void Heap::heapSort() 
{	
	int siz = (int)sz;
	vector<int> a;
	while(sz>0){
		deleteMax();
		a.push_back(store[sz]);
	}
	for(int k=0; k<siz; k++){
		store[k]=a[k];
	}
	sz=unsigned(siz);
}


