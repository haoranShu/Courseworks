//
//  union-find.h
//  Week2
//
//  Created by 舒 浩然 on 16/7/21.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#ifndef union_find_h
#define union_find_h

#include <vector>

class UF{
private:
    std::vector<int> leader;
    std::vector<int> size;
public:
    int numGroups;
    UF(int n);
    int find(int node);
    void unite(int node1, int node2);
};

#endif /* union_find_h */
