//
//  hashtable.h
//  Week2
//
//  Created by 舒 浩然 on 16/7/22.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#ifndef hashtable_h
#define hashtable_h

#include <vector>
#include <set>
typedef struct hashbin{
    hashbin(){
        std::vector<int> newValues;
        values = newValues;
    }
    std::vector<int> values;
}hashbin;

class hashtable{
public:
    hashtable(int tablesize);
    int size;
    std::vector<hashbin> bins;
    void insert(int key, int value);
    std::vector<int> getValues(int key);
};

#endif /* hashtable_h */
