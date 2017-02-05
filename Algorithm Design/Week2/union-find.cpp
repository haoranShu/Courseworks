//
//  union-find.cpp
//  Week2
//
//  Created by 舒 浩然 on 16/7/21.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <vector>

#include "union-find.h"

UF::UF(int n){
    std::vector<int> tmp;
    std::vector<int> tmpsize;
    for (int i = 0; i < n; i++){
        tmp.push_back(i+1);
        tmpsize.push_back(1);
    }
    leader = tmp;
    size = tmpsize;
    numGroups = n;
}

int UF::find(int node){
    while (leader[node-1] != node){
        leader[node-1] = leader[leader[node-1]-1];
        node = leader[node-1];
    }
    return node;
}

void UF::unite(int node1, int node2){
    int i = find(node1);
    int j = find(node2);
    
    if (i != j){
        if (size[i-1] <= size[j-1]){
            leader[i-1] = j;
            size[j-1] += size[i-1];
            numGroups --;
        }
        else
            unite(node2, node1);
    }
}