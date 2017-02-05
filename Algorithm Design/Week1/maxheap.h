//
//  maxheap.h
//  Week1
//
//  Created by 舒 浩然 on 16/7/15.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#ifndef maxheap_h
#define maxheap_h

#include <vector>
using namespace std;

class maxheap
{
private:
    vector<vector<double>> _vector;
    void BubbleUp(int index);
    void TrickleDown(int index);
    void Heapify();
    vector<double> _weight;
    
public:
    //maxheap(int* array, int length);
    maxheap(const vector<vector<double>>& vector);
    maxheap();
    
    void Insert(double newValue);
    vector<double> GetMax();
    void DeleteMax();
    
    //void PrintHeap();
};


#endif /* maxheap_h */
