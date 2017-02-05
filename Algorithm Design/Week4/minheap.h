//
//  minheap.h
//  Week1
//
//  Created by 舒 浩然 on 16/7/14.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#ifndef minheap_h
#define minheap_h

#include <vector>
using namespace std;

template<typename elt_type>
class minheap
{
private:
    void BubbleUp(int index);
    void TrickleDown(int index);
    
public:
    vector<elt_type> _vector;
    minheap(const vector<elt_type>& vector);
    minheap();
    
    void Heapify();
    void Insert(elt_type newValue);
    elt_type GetMin();
    void DeleteMin();
    
};


#endif /* minheap_h */
