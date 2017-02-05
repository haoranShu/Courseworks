//
//  hashtable.cpp
//  Week2
//
//  Created by 舒 浩然 on 16/7/22.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <vector>
#include <algorithm>

#include "hashtable.h"

hashtable::hashtable(int tablesize){
    size = tablesize;
    std::vector<hashbin> emptybins;
    for (int i = 0; i < size; i++){
        hashbin tmp;
        emptybins.push_back(tmp);
    }
    bins = emptybins;
}

void hashtable::insert(int key, int value){
    if (key < size){
        if (std::find(bins[key].values.begin(), bins[key].values.end(), value) == bins[key].values.end())
            bins[key].values.push_back(value);
    }
}

std::vector<int> hashtable::getValues(int key){
    return bins[key].values;
}