//
//  main.cpp
//  Week4
//
//  Created by 舒 浩然 on 16/8/7.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

/*
typedef struct vertex{
    int weight;
    std::vector<std::vector<int>> neighborList;
}vertex;

int isEdge(int i, int j, std::vector<vertex> graph){
    for (auto n:graph[i].neighborList){
        if (n[0] == j)
            return n[1];
    }
    return -1;
}

int main() {
    //read input
    std::ifstream fin("g1.txt");
    int numVert, numEdge;
    fin >> numVert;
    fin >> numEdge;
    
    std::vector<vertex> graph;
    
    vertex s;
    graph.push_back(s);
    for (int i = 0; i < numVert; i++){
        vertex newEdge;
        graph.push_back(newEdge);
        //link s with newEdge
        std::vector<int> tmp;
        tmp.push_back(0);
        tmp.push_back(0);
        graph[i+1].neighborList.push_back(tmp);
    }
    
    for (int i = 0; i < numEdge; i++){
        int head;
        int tail;
        int weight;
        fin >> head;
        fin >> tail;
        fin >> weight;
        std::vector<int> tmp;
        tmp.push_back(tail);
        tmp.push_back(weight);
        graph[head].neighborList.push_back(tmp);
    }

    //Floyd-Warshall Algorithm
    std::vector<std::vector<std::vector<int>>> A;
    for (int k = 0; k <= numVert; k++){
        std::vector<std::vector<int>> tmp1;
        for (int i = 1; i <= numVert; i++){
            std::vector<int> tmp2;
            for (int j = 1; j <= numVert; j++){
                std::cout << "Calculating for " << i << " " << j << " " << k << "." << std::endl;
                tmp2.push_back(0);
            }
            tmp1.push_back(tmp2);
        }
        A.push_back(tmp1);
    }
    
    for (int i = 1; i <= numVert; i++){
        for (int j = 1; j <= numVert; j++){
            std::cout << "Calculating for " << i << " " << j << "." << std::endl;
            if (i == j)
                A[i-1][j-1][0] = 0;
            else if (isEdge(i,j,graph) != -1)
                A[i-1][j-1][0] = isEdge(i,j,graph);
            else
                A[i-1][j-1][0] = INT_MAX;
        }
    }
    
    for (int k = 1; k <= numVert; k++){
        for (int i = 1; i <= numVert; i++){
            for (int j = 1; j <= numVert; j++){
                A[i-1][j-1][k] = std::min(A[i-1][j-1][k-1], A[i-1][k-1][k-1]+A[k-1][j-1][k-1]);
                std::cout << "Calculating for " << i << " " << j << " " << k << "." << std::endl;
            }
        }
    }
    
    int best = INT_MAX;
    for (int i = 1; i <= numVert; i++){
        if (A[i-1][i-1][numVert] < 0){
            std::cout << "Negative Cycle!" << std::endl;
            return 0;
        }
    }
    
    for (int i = 1; i <= numVert; i++){
        for (int j = 1; j <= numVert; j++){
            if (A[i-1][j-1][numVert] < best)
                best = A[i-1][j-1][numVert];
        }
    }

    std::cout << "Best is: " << best << std::endl;
    
    return 0;
}
 
*/
#include <set>

#include "minheap.h"

typedef struct vertex{
    int weight;
    std::vector<std::vector<int>> neighborList;
}vertex;

typedef struct vertexDij{
    int id;
    int key;
    std::vector<std::vector<int>> neighborList;
}vertexDij;

std::vector<int> dijkstra(std::vector<vertexDij> graphDij, int source, int numVert, std::vector<vertex> graph) {
    for (auto& k:graphDij){
        k.key = 1000000;
    }
    graphDij[source].key = 0;
    
    minheap<vertexDij> heap(graphDij);
    std::set<int> V;
    std::set<int> X;
    
    for (int i = 1; i <= numVert; i++){
        V.insert(i);
    }
    
    V.erase(source);
    X.insert(source);
    
    int shortest[numVert+1];
    shortest[0] = INT_MIN;
    
    while (!V.empty()){
        vertexDij v = heap.GetMin();
        V.erase(v.id);
        X.insert(v.id);
        shortest[v.id] = v.key;
        int r = v.key;
        heap.DeleteMin();
        for (auto& l:v.neighborList){
            for (auto& m:heap._vector){
                if (m.id == l[0]){
                    m.key = std::min(m.key, r + l[1]);
                    //std::cout << m.key << std::endl;
                }
            }
        }
        heap.Heapify();
    }

    int best = INT_MAX;
    int k;
    for (int i = 1; i <= numVert; i++){
        if (i != source){
            //std::cout << "shortest for " << i << " is " << shortest[i] << std::endl;
            if (best > shortest[i] + graph[i].weight - graph[source].weight){
                best = shortest[i] + graph[i].weight - graph[source].weight;
                k = i;
            }
            //std::cout << "Dij best: " << best << std::endl;
        }
    }
    
    std::vector<int> result;
    result.push_back(k);
    result.push_back(best);
    return result;
}


int main() {
    //read input
    std::ifstream fin("small2.txt");
    int numVert, numEdge;
    fin >> numVert;
    fin >> numEdge;
    
    std::vector<vertex> graph;
    std::vector<vertexDij> graphDij;
    
    vertex s;
    graph.push_back(s);
    vertexDij sp;
    sp.id = 0;
    sp.key = INT_MAX;
    graphDij.push_back(sp);
    for (int i = 0; i < numVert; i++){
        vertex newEdge;
        graph.push_back(newEdge);
        vertexDij newEdgeDij;
        graphDij.push_back(newEdgeDij);
        graphDij[i+1].id = i+1;
        //link s with newEdge
        std::vector<int> tmp;
        tmp.push_back(0);
        tmp.push_back(0);
        graph[i+1].neighborList.push_back(tmp);
        if (i % 100 == 0){
            std::cout << "Processing..." << i << std::endl;
        }
    }
    
    for (int i = 0; i < numEdge; i++){
        int head;
        int tail;
        int weight;
        fin >> head;
        fin >> tail;
        fin >> weight;
        std::vector<int> tmp;
        tmp.push_back(head);
        tmp.push_back(weight);
        graph[tail].neighborList.push_back(tmp);
        std::vector<int> tmpDij;
        tmpDij.push_back(tail);
        tmpDij.push_back(weight);
        graphDij[head].neighborList.push_back(tmpDij);
        if (i % 100 == 0){
            std::cout << "Processing..." << i << std::endl;
        }
    }
    
    std::cout << "Initialization over" << std::endl;
    
    //Bellman
    int A[numVert][numVert];
    A[0][0] = 0;
    for (int i = 1; i < numVert; i++){
        A[0][i] = 1000000;
    }
    for (int i = 1; i < numVert; i++){
        for (int j = 0; j <= numVert; j++){
            A[i][j] = A[i-1][j];
            size_t length = graph[j].neighborList.size();
            for (int k = 0; k < length; k++){
                A[i][j] = std::min(A[i-1][graph[j].neighborList[k][0]] + graph[j].neighborList[k][1], A[i][j]);
                //std::cout << graph[j].neighborList[k][0] << " " << j << " " << graph[j].neighborList[k][1] << " may be added" << std::endl;
                //std::cout << i << " " << j << " " << A[i][j] << std::endl;
            }
        }
    }
    
    for (int j = 0; j < numVert; j++){
        size_t length = graph[j].neighborList.size();
        for (int k = 0; k < length; k++){
            if (A[numVert-1][j] > A[numVert-1][graph[j].neighborList[k][0]] + graph[j].neighborList[k][1]){
                std::cout << "Negative Cycle!"  << std::endl;
                return 0;
            }
        }
    }
    
    //Update weights
    for (int i = 1; i <= numVert; i++){
        graph[i].weight = A[numVert-1][i];
        //std::cout << "Vertex " << i << " has " << graph[i].weight << std::endl;
    }
    
    for (int k = 1; k <= numVert; k++){
        for (auto& l:graphDij[k].neighborList){
            l[1] = l[1] + graph[k].weight - graph[l[0]].weight;
        }
    }
    
    //for (auto n:graphDij){
    //    for (auto m:n.neighborList)
    //        std::cout << n.id << "--->" << m[0] << " " << m[1] << std::endl;
    //}
    
    std::cout << "Bellman over" << std::endl;
    
    //N * Dijiskra
    int minimum = INT_MAX;
    for (int i = 1; i <= numVert; i++){
        std::vector<vertexDij> graphDij_use = graphDij;
        std::vector<int> newDij = dijkstra(graphDij_use, i, numVert, graph);
        //int realDist = newDij[1] + graph[newDij[0]].weight - graph[i].weight;
        std::cout << "This is from " << i << " to " << newDij[0] << std::endl;
        std::cout << newDij[1] << std::endl;
        minimum = std::min(minimum, newDij[1]);
        std::cout << minimum << std::endl;
        std::cout << "NIJ round: " << i << std::endl;
    }
    
    std::cout << minimum << std::endl;
    return 0;
}
