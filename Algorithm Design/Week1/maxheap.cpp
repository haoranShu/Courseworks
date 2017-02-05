//
//  maxheap.cpp
//  Week1
//
//  Created by 舒 浩然 on 16/7/15.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include "maxheap.h"

/*
 maxheap::maxheap(int* array, int length){
 for (int i = 0; i < length; i++)
 _vector.push_back(array[i]);
 
 Heapify();
 }
 */

maxheap::maxheap(const vector<vector<double>>& vector){
    _vector = vector;
    Heapify();
}

void maxheap::BubbleUp(int index){
    while (index > 0){
        int parent = (index+1)/2-1;
        if (_vector[parent][0] < _vector[index][0]){
            vector<double> tmp = _vector[parent];
            _vector[parent] = _vector[index];
            _vector[index] = tmp;
        }
        else
            break;
        index = parent;
    }
}

void maxheap::TrickleDown(int index){
    int length = int(_vector.size());
    if ((index+1)*2-1 <= length-1){
        double larger;
        int next;
        int lchild = (index+1)*2-1;
        int rchild = (index+1)*2;
        if ((index+1)*2 <= length-1 && _vector[lchild][0] < _vector[rchild][0]){
            larger = _vector[rchild][0];
            next = rchild;
        }
        else{
            larger = _vector[lchild][0];
            next = lchild;
        }
        if (larger > _vector[index][0]){
            vector<double> tmp = _vector[index];
            _vector[index] = _vector[next];
            _vector[next] = tmp;
        }
        TrickleDown(next);
    }
}

void maxheap::Heapify(){
    int length = int(_vector.size());
    for (int i = length-1; i>=0; i--){
        TrickleDown(i);
        //PrintHeap();
    }
}

void maxheap::Insert(double newValue){
    int length = int(_vector.size());
    vector<double> newPair;
    newPair.push_back(newValue);
    newPair.push_back(length+1);
    _vector.push_back(newPair);
    BubbleUp(int(_vector.size())-1);
}

vector<double> maxheap::GetMax(){
    return _vector[0];
}

void maxheap::DeleteMax(){
    int length = int(_vector.size());
    if (length == 0)
        return;
    
    _vector[0] = _vector[length-1];
    _vector.pop_back();
    
    TrickleDown(0);
}

/*
 void minheap::PrintHeap(){
 int length = int(_vector.size());
 for (int i = 0; i < length; i++)
 std::cout << _vector[i] << " ";
 std::cout << std::endl;
 }
 */
