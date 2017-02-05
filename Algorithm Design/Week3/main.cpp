//
//  main.cpp
//  Week3
//
//  Created by 舒 浩然 on 16/7/30.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

/*
//Question 1 (slower)
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

class knapsack{
public:
    knapsack(vector<vector<long>> dataInput, long numVert){
        data = dataInput;
        vector<vector<vector<long>>> emptyCache;
        for (int i = 0; i <= numVert; i++){
            vector<vector<long>> tmp_i;
            emptyCache.push_back(tmp_i);
        }
        cache = emptyCache;
    }
    
    vector<vector<vector<long>>> cache;
    vector<vector<long>> data;
    
    long searchCache(long n, long weight){
        for (auto& k : cache[n]){
            if (k[0] == weight)
                return k[1];
        }
        return -1;
    }
    
    void addToCache(long n, long weight, long v){
        vector<long> tmp;
        tmp.push_back(weight);
        tmp.push_back(v);
        cache[n].push_back(tmp);
    }
    
    long indicator = 0;
    
    long calculate(long n, long weight){
        if (n == 0) {
            addToCache(n, weight, 0);
            return 0;
        }
        else {
            long with, without;
            long search1 = searchCache(n-1, weight);
            long search2 = -1;
            if (weight >= data[n][1])
                search2 = searchCache(n-1, weight-data[n][1]);
            if (search1 != -1){
                without = search1;
            }
            else {
                without = calculate(n-1, weight);
            }
            with = 0;
            if (search2 != -1){
                with = search2 + data[n][0];
            }
            else if (weight >= data[n][1]) {
                with = calculate(n-1, weight-data[n][1]) + data[n][0];
            }
            long result = max(with, without);
            addToCache(n, weight, result);
            if (n > indicator) {
                cout << n << " " << weight << endl;
                indicator = n;
            }
            return result;
        }
    }
};

int main() {
    // read in data
    ifstream fin("q2.txt");
    long W, numVert;
    fin >> W;
    fin >> numVert;
    
    vector<vector<long>> data;
    vector<long> first;
    first.push_back(-1);
    first.push_back(-1);
    data.push_back(first);
    
    for (int i = 0; i < numVert; i++){
        vector<long> tmp;
        long value, weight;
        fin >> value;
        fin >> weight;
        tmp.push_back(value);
        tmp.push_back(weight);
        data.push_back(tmp);
    }
    
    knapsack thisproblem(data, numVert);
    long result = thisproblem.calculate(numVert, W);
    
    cout << result << endl;
    
    return 0;
}


*/

//question 2
 
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // read in data
    ifstream fin("q1.txt");
    long W, numVert;
    fin >> W;
    fin >> numVert;
    
    
    vector<vector<long>> data;
    
    for (int i = 0; i < numVert; i++){
        vector<long> tmp;
        long value, weight;
        fin >> value;
        fin >> weight;
        tmp.push_back(value);
        tmp.push_back(weight);
        data.push_back(tmp);
    }
    
    vector<vector<long>> form;
    
    for (int i = 0; i <= W; i++){
        vector<long> tmp;
        form.push_back(tmp);
        for (int j = 0; j < numVert; j++){
            if (i == 0)
                form[i].push_back(0);
            else{
                long with = 0, without = 0;
                if (j >= 1)
                    without = form[i][j-1];
                if (i >= data[j][1]){
                    if (j >= 1)
                        with = form[i-data[j][1]][j-1] + data[j][0];
                    else if (j == 0)
                        with = data[j][0];
                }
                long final = max(with, without);
                form[i].push_back(final);
            }
        }
    }
    
    cout << form[W][numVert-1] << endl;
    
    return 0;
}


