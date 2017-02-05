//
//  main.cpp
//  Week5
//
//  Created by 舒 浩然 on 16/8/14.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <climits>
#include <algorithm>

float dist(std::pair<float, float> p1, std::pair<float, float> p2){
    float distance;
    distance += pow(p1.first - p2.first, 2);
    distance += pow(p1.second - p2.second, 2);
    distance = float(sqrt(distance));
    
    return distance;
}

int nchoosek (int n, int k){
    if (k == 0)
        return 1;
    else
        return (nchoosek(n-1,k-1)*n)/k;
}

int lookforcomb (int k, int n, std::vector<int> comb){
    //chosen k from n
    //return the ranking of comb
    if (k == 1){
        return comb[0];
    }
    std::vector<int> comb1 = comb;
    comb1.erase(comb1.begin());
    for (int i = 0; i < k-1; i++){
        comb1[i] -= comb[0];
    }
    int head = 0;
    for (int i = 1; i < comb[0]; i++){
        head += nchoosek(n-i, k-1);
    }
    return (lookforcomb(k-1, n-comb[0], comb1)+head);
}

std::vector<int> lthcomb(int k, int n, int l){
    std::vector<int> comb;
    if (k == 1){
        comb.push_back(l);
        return comb;
    }
    else if (l <= nchoosek(n-1, k-1)) {
        comb.push_back(1);
        std::vector<int> comb1 = lthcomb(k-1, n-1, l);
        for (auto & r:comb1){
            r++;
        }
        comb.insert(comb.end(), comb1.begin(), comb1.end());
        //std::cout << "1111" <<std::endl;
        return comb;
    }
    else {
        int l1 = l-nchoosek(n-1, k-1);
        std::vector<int> comb1 = lthcomb(k, n-1, l1);
        for (auto & r:comb1){
            r++;
        }
        //std::cout << "2222" <<std::endl;
        return comb1;
    }
}

int main() {
    /*
    std::vector<int> vec = lthcomb(4, 6, 9);
    for (auto k:vec){
        std::cout << k << std::endl;
    }
    
    std::cout << lookforcomb(4, 6, vec) << std::endl;
    */
    // read in the data
    std::ifstream fin("tsp.txt");
    int numVert;
    fin >> numVert;
    
    const int n = 19;
    const int sizeS = pow(2, n-1);
    
    std::vector<std::pair<float, float>> position;
    for (int i = 0; i < numVert; i++){
        float x, y;
        fin >> x;
        fin >> y;
        std::pair<float, float> tmp(x, y);
        position.push_back(tmp);
    }
    std::cout << "read in data done!" << std::endl;
    
    //initiate distance chart
    std::vector<std::vector<float>> distChar;
    for (int i = 0; i < numVert; i++){
        std::vector<float> tmp_i;
        for (int j = 0; j < numVert; j++){
            if (i == j)
                tmp_i.push_back(0);
            else
                tmp_i.push_back(dist(position[i], position[j]));
        }
        distChar.push_back(tmp_i);
    }
    //distance from point k to point j is distChar[k-1][j-1]
    
    /*
    for(auto vec:distChar){
        for (auto r:vec){
            std::cout << r << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    */
    std::cout << "initiate distance chart done!" << std::endl;
    
    //prepare two tables to store different combinations
    std::vector<std::vector<int>> combtable;
    std::vector<std::vector<int>> indextable;
    int end = 0;
    int start = 0;
    int laststart;
    for (int m = 2; m <= n; m++){
        laststart = start;
        start = end+1;
        end = start+nchoosek(n-1, m-1)-1;
        for (int i = start; i <= end; i++){
            std::vector<int> tmpcomb = lthcomb(m, n, i+1-start);
            combtable.push_back(tmpcomb);
            std::vector<int> tmp;
            for (int j = 0; j < m; j++){
                std::vector<int> tmpcombj = tmpcomb;
                tmpcombj.erase(tmpcombj.begin()+j);
                tmp.push_back(lookforcomb(m-1, n, tmpcombj)+laststart);
            }
            indextable.push_back(tmp);
        }
    
    std::cout << "m = " << m << " done!" << std::endl;
    }
    
    std::cout << "prepare two tables done!" << std::endl;
    /*
    
    for(auto vec:combtable){
        for (auto r:vec){
            std::cout << r << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for(auto vec:indextable){
        for (auto r:vec){
            std::cout << r << " ";
        }
        std::cout << std::endl;
    }
    
    
    */
    std::vector<std::vector<std::pair<int, float>>> A;
    
    //initialisation
    std::pair<int, float> tmp(1, 0);
    std::vector<std::pair<int, float>> tmp1;
    tmp1.push_back(tmp);
    A.push_back(tmp1);
    for (int i = 1; i < sizeS; i++){
        std::pair<int, float> tmp(1, 100000000);
        std::vector<std::pair<int, float>> tmp1;
        tmp1.push_back(tmp);
        A.push_back(tmp1);
    }
    
    //induction
    end = 0;
    start = 0;
    for (int m = 2; m <= n; m++){
        laststart = start;
        start = end+1;
        end = start+nchoosek(n-1, m-1)-1;
        for (int i = start; i <= end; i++){
            for (int l=1; l<m; l++){
                int j = combtable[i-1][l];
                std::pair<int, float> tmp(j, 10000000);
                A[i].push_back(tmp);
                for (auto k:A[indextable[i-1][l]-1]){
                    if (k.first != j){
                        //std::cout << k << " " << indextable[i-1][l] << " " << A[indextable[i-1][l]][k-1] << std::endl;
                        A[i].back().second = std::min(k.second+distChar[k.first-1][j-1], A[i].back().second);
                    }
                }
                //std::cout << i+1 << " " << j << " " << A[i][j-1] << std::endl;
            }
        }
    std::cout << "m = " << m << " done!" << std::endl;
    }
    
    float result = 10000000;
    for (int j = 2; j <= n; j++){
        result = std::min(A[sizeS-1][j-1].second+distChar[j-1][0], result);
    }
    
    std::cout << result << std::endl;
    
    /*
    for(auto vec:A){
        for (int i = 0; i < n; i++){
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */
    return 0;
}
