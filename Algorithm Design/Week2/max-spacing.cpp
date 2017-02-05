//
//  main.cpp
//  Week2
//
//  Created by 舒 浩然 on 16/7/21.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#include "union-find.h"

const int k = 4;

bool sortEdge(std::vector<int> edge1, std::vector<int> edge2){
    return (edge1.back() < edge2.back());
}

int main(){
    //read in the input
    std::ifstream fin("q1.txt");
    int numNodes;
    fin >> numNodes;
    
    std::vector<std::vector<int>> edgeList;
    
    while (!fin.eof()){
        std::vector<int> newEdge;
        int start, end, length;
        fin >> start;
        fin >> end;
        fin >> length;
        newEdge.push_back(start);
        newEdge.push_back(end);
        newEdge.push_back(length);
        edgeList.push_back(newEdge);
    }
    
    std::sort(edgeList.begin(), edgeList.end(), sortEdge);
    
    //start Kruskal's
    UF cluster(numNodes);
    while (cluster.numGroups > k){
        if (cluster.find(edgeList[0][0]) != cluster.find(edgeList[0][1])){
            cluster.unite(edgeList[0][0], edgeList[0][1]);
            std::cout << edgeList[0][0] << " " << edgeList[0][1] << " " << edgeList[0][2] << std::endl;
        }
        edgeList.erase(edgeList.begin());
        std::cout << "Groups: " << cluster.numGroups << std::endl;
    }
    
    int length = int(edgeList.size());
    for (int i = 0; i < length; i++){
        std::cout << edgeList[0][0] << " " << edgeList[0][1] << " " << edgeList[0][2] << "     ";
        std::cout << cluster.find(edgeList[0][0]) << " " << cluster.find(edgeList[0][1]) << std::endl;
        if (cluster.find(edgeList[0][0]) != cluster.find(edgeList[0][1])){
            std::cout << "Max spacing: " << edgeList[0][2] << std::endl;
            break;
        }
        edgeList.erase(edgeList.begin());
    }
    
    return 0;
}
