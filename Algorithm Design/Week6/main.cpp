//
//  main.cpp
//  Week6
//
//  Created by 舒 浩然 on 16/8/20.
//  Copyright © 2016年 舒 浩然. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef struct vertex{
    int index = -1;
    int lowlink;
    int scc = -1;
    bool onStack;
    std::vector<int> outward;
}vertex;

void strongconnect(int v, std::vector<vertex> & G, int & ind, std::vector<int> & S, int & scc){
    G[v].index = ind;
    G[v].lowlink = ind;
    ind ++;
    S.push_back(v);
    G[v].onStack = true;
    
    if (!G[v].outward.empty()){
        for (auto o:G[v].outward){
            if (G[o].index == -1){
                strongconnect(o, G, ind, S, scc);
                G[v].lowlink = std::min(G[v].lowlink, G[o].lowlink);
            }
            else if (G[o].onStack){
                G[v].lowlink = std::min(G[v].lowlink, G[o].index);
            }
        }
    }
    
    if (G[v].lowlink == G[v].index){
        if (S.back() == v){
            G[v].onStack = false;
            G[v].scc = scc;
            //std::cout << "!!Vertex " << v << ", scc: " << scc << std::endl;
            S.pop_back();
        }
        else {
            while (!S.empty() && S.back() != v){
                int w = S.back();
                G[w].onStack = false;
                G[w].scc = scc;
                //std::cout << "!!Vertex " << w << ", scc: " << scc << std::endl;
                S.pop_back();
            }
            G[v].onStack = false;
            G[v].scc = scc;
            //std::cout << "!!Vertex " << v << ", scc: " << scc << std::endl;
            S.pop_back();
        }
        scc ++;
    }
}


int main( ) {
    //read in data and construct the implication graph
    
    std::ifstream fin("q6.txt");
    int n;
    fin >> n;
    
    std::vector<vertex> graph;
    for (int i = 0; i <= 2*n; i++){
        vertex new_vertex;
        graph.push_back(new_vertex);
    }
    
    for (int i = 0; i < n; i++){
        int a, b;
        fin >> a;
        fin >> b;
        if (a < 0)
            a = n-a;
        if (b < 0)
            b = n-b;
        int not_a = (a+n)%(2*n);
        int not_b = (b+n)%(2*n);
        graph[not_a].outward.push_back(b);
        graph[not_b].outward.push_back(a);
    }
    
    std::cout << "Initialization over!!" << std::endl;
    
    /*
    //testing graph
    int n = 8;
    std::vector<vertex> graph;
    for (int i = 0; i <= n; i++){
        vertex new_vertex;
        graph.push_back(new_vertex);
    }
    
    
    graph[1].outward.push_back(2);
    graph[2].outward.push_back(3);
    graph[3].outward.push_back(1);
    graph[4].outward.push_back(2);
    graph[4].outward.push_back(3);
    graph[4].outward.push_back(5);
    graph[5].outward.push_back(4);
    graph[5].outward.push_back(6);
    graph[6].outward.push_back(3);
    graph[6].outward.push_back(7);
    graph[7].outward.push_back(6);
    graph[8].outward.push_back(5);
    graph[8].outward.push_back(7);
    graph[8].outward.push_back(8);
    
    
    graph[1].outward.push_back(2);
    graph[2].outward.push_back(1);
    */
    
    //run tarjan's algorithm once and get the SCC division
    std::vector<int> stack;
    int ind = 1;
    int scc = 1;
    for (int v = 1; v <= n; v++){
        if (graph[v].index == -1){
            strongconnect(v, graph, ind, stack, scc);
        }
        std::cout << "Processing vertex " << v << " over!!" << std::endl;
    }
    /*
    for (int v = 1; v <= n; v++){
        std::cout << "Vertex " << v << ", scc: " << graph[v].scc << std::endl;
    }
    */
    
    std::cout << "Start scanning now" << std::endl;
    
    //scan through to see if any one vertex has its counterpart inside
    bool sat = true;
    int pair;
    for (int i = 1; i <= n; i++){
        pair = i+n;
        if (graph[i].scc == graph[pair].scc){
            sat = false;
            std::cout << "Not Satisfied!!!!!!!" << std::endl;
            break;
        }
    }
    if (sat == true)
        std::cout << "Satisfied!!!!!!!" << std::endl;
    
    return 0;
}
