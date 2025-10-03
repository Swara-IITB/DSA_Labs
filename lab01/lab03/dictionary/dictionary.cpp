#include "dictionary.h"

//Implement dictionary here

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
};

Dictionary::~Dictionary(){
    delete[] A;
}

#define p 31
#define alpha 0.6180339887
#define TOMBSTONE (char *)0xabcdabcdabcdabcd

int Dictionary::hashValue(char key[]){
    
    /*** For testcases compliance use factor: 31
    and alpha: 0.6180339887 in your implementation 
    but you are free to use other values and see variation in hash plots ***/
    
    double hashValue = 0;
    // compute hash
    for(int i=strlen(key)-1; i>=0; i--){
        hashValue *= p;
        hashValue += alpha*key[i];
        hashValue -= int(hashValue);
    }
    return int(N*hashValue);
}

int Dictionary::findFreeIndex(char key[]){
    int i = hashValue(key);
    int firsttomb = -1;
    for(int j=0; j<N; j++){
        int idx = (i+j)%N;
        if(A[idx].key == nullptr){
            return (firsttomb == -1) ? idx : firsttomb;
        } else if(A[idx].key == TOMBSTONE){
            if(firsttomb==-1){
                firsttomb = idx;
            }
        } else if(strcmp(A[idx].key,key)==0){
            return idx;
        }
    }
    return firsttomb;
}

struct Entry* Dictionary::get(char key[]){
    int i= hashValue(key);
    for(int j=0; j<N; j++){
        int idx = (i+j) %N;
        if(A[idx].key == nullptr){
            return nullptr;
        }else if(A[idx].key!=TOMBSTONE && strcmp(A[idx].key,key)==0){
            return &(A[idx]);
        }
    }
    return nullptr;
}

bool Dictionary::put(Entry e) {
    int idx = findFreeIndex(e.key);
    if(idx==-1){
        return false;
    }
    if(A[idx].key != nullptr && A[idx].key != TOMBSTONE){
        delete[] A[idx].key;
    }
    int l = strlen(e.key);
    A[idx].key = new char[l+1];
    strcpy(A[idx].key,e.key);
    A[idx].value = e.value;
    return true; // Dummy return
}

bool Dictionary::remove(char key[]){
    int i= hashValue(key);
    for(int j=0; j<N; j++){
        int idx = (i+j) %N;
        if(A[idx].key == nullptr){
            return false;
        } else if(A[idx].key != TOMBSTONE && strcmp(A[idx].key,key)==0){
            delete[] A[idx].key;
            A[idx].key = TOMBSTONE;
            return true;
        }
    }
    return false; // Dummy return
}



