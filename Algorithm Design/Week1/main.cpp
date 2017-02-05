//
//  main.cpp
//  Week1
//
//  Created by 舒 浩然 on 16/7/14.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

#include "minheap.h"

typedef struct vertex{
    int id;
    int key;
    vector<vector<int>> adjacency;
}vertex;

int main() {
    std::ifstream fin("edges.txt");
    int numNodes, numEdges;
    fin >> numNodes;
    fin >> numEdges;
    
    vector<vertex> graph;
    
    for (int i = 1; i <= numNodes; i++){
        vertex a;
        a.id = i;
        graph.push_back(a);
        a.key = INT_MAX;
    }
    
    int a, b;
    int cost;
    for (int i = 1; i <= numEdges; i++){
        fin >> a; fin >> b;
        fin >> cost;
        vector<int> ab, ba;
        ab.push_back(b);
        ab.push_back(cost);
        ba.push_back(a);
        ba.push_back(cost);
        graph[a-1].adjacency.push_back(ab);
        graph[b-1].adjacency.push_back(ba);
    }
    
    set<int> X;
    set<int> V;
    for (int i = 1; i <= numNodes; i++){
        V.insert(i);
    }
    
    graph.erase(graph.begin());
    
    minheap<vertex> VmX(graph);
    
    int MST_length = 0;
    
    V.erase(1);
    X.insert(1);
    
    while (! V.empty()){
        //for (auto& k : VmX._vector){
        //    std::cout << k.id << " " << k.key << ",";
        //}
        //std::cout << std::endl;
        for (auto& k : VmX._vector){
            for (auto& n : k.adjacency){
                if (X.find(n[0]) != X.end())
                    k.key = std::min(k.key, n[1]);
            }
        }
        VmX.Heapify();
        vertex min = VmX.GetMin();
        V.erase(min.id);
        //for (auto& x: V)
        //    std::cout << x << " ";
        //std::cout << std::endl;
        X.insert(min.id);
        //for (auto& x: X)
        //    std::cout << x << " ";
        //std::cout << std::endl;
        VmX.DeleteMin();
        MST_length += min.key;
        std::cout << min.key << " ";
        std::cout << MST_length << std::endl;
    }
    
    std::cout << MST_length << std::endl;
    
    return 0;
}


/*
void sortWeight(vector<double>& sameScore, vector<double> weight){
    int length = int(sameScore.size());
    for (int i = 0; i < length-1; i++){
        for (int j = i+1; j < length; j++){
            if (weight[sameScore[i]] < weight[sameScore[j]]){
                double tmp = sameScore[i];
                sameScore[i] = sameScore[j];
                sameScore[j] = tmp;
            }
        }
    }
}

int main() {
    std::ifstream fin("jobs.txt");
    int length;
    int a,b;
    
    vector<double> weight;
    vector<double> joblength;
    
    fin >> length;
    for (int i = 0; i < length; i++){
        fin >> a;
        fin >> b;
        weight.push_back(a);
        joblength.push_back(b);
    }
    
    vector<vector<double>> difference;
    
    for (int i = 0; i < length; i++){
        vector<double> tmp;
        tmp.push_back(weight[i]-joblength[i]);
        tmp.push_back(i+1);
        difference.push_back(tmp);
    }
    
    maxheap differenceHeap(difference);
    
    long int accu = 0;
    long int currentCompletionTime = 0;
    
    vector<double> order;
    vector<double> newOrder;
    
    for (int i = 0; i < length; i++){
        vector<double> add = differenceHeap.GetMax();
        order.push_back(add[1]-1);
        differenceHeap.DeleteMax();
    }
    
    vector<double> sameScore;
    double position = 0;
    while (position < length){
        if (sameScore.size() == 0){
            sameScore.push_back(order[position]);
            position += 1;
        }
        else if (difference[order[position]][0] == difference[sameScore[0]][0]){
            sameScore.push_back(order[position]);
            position += 1;
        }
        else{
            sortWeight(sameScore, weight);
            newOrder.insert(newOrder.end(), sameScore.begin(), sameScore.end());
            sameScore.clear();
        }
    }
    if (position == length){
        sortWeight(sameScore, weight);
        newOrder.insert(newOrder.end(), sameScore.begin(), sameScore.end());
        sameScore.clear();
    }
    
    for (int i = 0; i < length; i++){
        double addWeight = weight[newOrder[i]];
        std::cout << difference[newOrder[i]][0] << " " << addWeight << " " << joblength[newOrder[i]] << " ";
        currentCompletionTime += joblength[newOrder[i]];
        accu += currentCompletionTime*addWeight;
        std::cout << accu << std::endl;
    }
    
    std::cout << currentCompletionTime << std::endl;
    std::cout << accu << std::endl;
    
    return 0;

}
 */
