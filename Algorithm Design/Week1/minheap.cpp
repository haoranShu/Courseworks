//
//  minheap.cpp
//  Week1
//
//  Created by 舒 浩然 on 16/7/14.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include "minheap.h"

/*
minheap::minheap(int* array, int length){
    for (int i = 0; i < length; i++)
        _vector.push_back(array[i]);
    
    Heapify();
}
*/
typedef struct vertex{
    int id;
    int key;
    vector<vector<int>> adjacency;
}vertex;

template<typename elt_type>
minheap<elt_type>::minheap(const vector<elt_type>& vector){
    _vector = vector;
    
    Heapify();
}

template<typename elt_type>
void minheap<elt_type>::BubbleUp(int index){
    while (index > 0){
        int parent = (index+1)/2-1;
        if (_vector[parent].key > _vector[index].key){
            elt_type tmp = _vector[parent];
            _vector[parent] = _vector[index];
            _vector[index] = tmp;
        }
        else
            break;
        index = parent;
    }
}

template<typename elt_type>
void minheap<elt_type>::TrickleDown(int index){
    int length = int(_vector.size());
    if ((index+1)*2-1 <= length-1){
        int smaller;
        int next;
        int lchild = (index+1)*2-1;
        int rchild = (index+1)*2;
        if ((index+1)*2 <= length-1 && _vector[lchild].key > _vector[rchild].key){
                smaller = _vector[rchild].key;
                next = rchild;
        }
        else{
            smaller = _vector[lchild].key;
            next = lchild;
        }
        if (smaller < _vector[index].key){
            elt_type tmp = _vector[index];
            _vector[index] = _vector[next];
            _vector[next] = tmp;
        }
        TrickleDown(next);
    }
}

template<typename elt_type>
void minheap<elt_type>::Heapify(){
    int length = int(_vector.size());
    for (int i = length-1; i>=0; i--){
        TrickleDown(i);
        //PrintHeap();
    }
}

template<typename elt_type>
void minheap<elt_type>::Insert(elt_type newValue){
    _vector.push_back(newValue);
    BubbleUp(int(_vector.size())-1);
}

template<typename elt_type>
elt_type minheap<elt_type>::GetMin(){
    return _vector[0];
}

template<typename elt_type>
void minheap<elt_type>::DeleteMin(){
    int length = int(_vector.size());
    if (length == 0)
        return;
    
    _vector[0] = _vector[length-1];
    _vector.pop_back();
    
    TrickleDown(0);
}

template class minheap<vertex>;

/*
void minheap::PrintHeap(){
    int length = int(_vector.size());
    for (int i = 0; i < length; i++)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}
*/