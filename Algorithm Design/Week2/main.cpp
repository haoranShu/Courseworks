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
#include <cmath>

#include "union-find.h"

typedef struct hashtable{
    hashtable(int n){
        size = n;
        std::vector<std::vector<int>> t;
        for (int i = 0; i < size; i++){
            std::vector<int> tmp;
            t.push_back(tmp);
        }
        table = t;
    }
    
    int size;
    std::vector<std::vector<int>> table;
    
    void insert(int key, int value){
        if (key < size){
            table[key].push_back(value);
        }
    }
    
    std::vector<int> getValues(int key){
        return table[key];
    }
}hashtable;

int hammingdist(std::vector<int> position1, std::vector<int> position2){
    int length = int(position1.size());
    int dist = 0;
    for (int i = 0; i < length; i++){
        if (position1[i] != position2[i])
            dist ++;
    }
    return dist;
}

int fromDigits(std::vector<int> line){
    int length = int(line.size());
    int result = 0;
    for (int i = 0; i < length; i++){
        result += pow(2,i)*line[i];
    }
    return result;
}

std::vector<int> change1(std::vector<int> line){
    std::vector<int> result;
    int length = int(line.size());
    for (int i = 0; i < length; i++){
        std::vector<int> tmpLine = line;
        tmpLine[i] = (tmpLine[i]+1)%2;
        int tmp = fromDigits(tmpLine);
        result.push_back(tmp);
    }
    return result;
}

std::vector<int> change2(std::vector<int> line){
    std::vector<int> result;
    int length = int(line.size());
    for (int i = 0; i < length-1; i++){
        for (int j = i; j < length; j++){
            std::vector<int> tmpLine = line;
            tmpLine[i] = (tmpLine[i]+1)%2;
            tmpLine[j] = (tmpLine[j]+1)%2;
            int tmp = fromDigits(tmpLine);
            result.push_back(tmp);
        }
    }
    return result;
}

int main(){
    //read input
    std::fstream fin("q2.txt");
    int numNodes;
    fin >> numNodes;
    int lengthNode;
    fin >> lengthNode;
    
    //numNodes = 50000;
    
    std::vector<std::vector<int>> nodes;
    std::vector<int> nodesIndex;
    
    for (int i = 1; i <= numNodes; i++){
        std::vector<int> line;
        for (int j = 0; j < lengthNode; j++){
            int digit;
            fin >> digit;
            std::cout << digit << " ";
            line.push_back(digit);
        }
        nodes.push_back(line);
        nodesIndex.push_back(fromDigits(line));
        std::cout << nodesIndex.back() << std::endl;
    }
    
    int tablesize = pow(2,lengthNode);
    
    hashtable hashtable0(tablesize);
    hashtable hashtable1(tablesize);
    hashtable hashtable2(tablesize);
    
    //keys index from 0
    for (int i = 1; i <= numNodes; i++)
    {
        int buckets0 = fromDigits(nodes[i-1]);
        hashtable0.insert(buckets0, i);
        
        std::vector<int> buckets1 = change1(nodes[i-1]);
        for (auto& k : buckets1)
            if (nodesIndex[i-1] > k)
                hashtable1.insert(k, i);
        
        std::vector<int> buckets2 = change2(nodes[i-1]);
        for (auto& k : buckets2)
            if (nodesIndex[i-1] > k)
                hashtable2.insert(k, i);
        
        std::cout << "Hashed Node #" << i << std::endl;
    }
    
    std::vector<std::vector<int>> hamming0pairs;
    std::vector<std::vector<int>> hamming1pairs;
    std::vector<std::vector<int>> hamming2pairs;
    
    for (int i = 1; i <= numNodes; i++){
        std::vector<int> dist0 = hashtable0.getValues(nodesIndex[i-1]);
        for (auto k : dist0){
            if (i > k){
                std::vector<int> tmp;
                tmp.push_back(i);
                tmp.push_back(k);
                hamming0pairs.push_back(tmp);
                std::cout << "With distance 0: " << i << " " << k << std::endl;
            }
        }
        
        std::vector<int> dist1 = hashtable1.getValues(nodesIndex[i-1]);
        for (auto k : dist1){
            std::vector<int> tmp;
            tmp.push_back(i);
            tmp.push_back(k);
            hamming1pairs.push_back(tmp);
            std::cout << "With distance 1: " << i << " " << k << std::endl;
        }
        
        std::vector<int> dist2 = hashtable2.getValues(nodesIndex[i-1]);
        for (auto k : dist2){
            std::vector<int> tmp;
            tmp.push_back(i);
            tmp.push_back(k);
            hamming2pairs.push_back(tmp);
            std::cout << "With distance 2: " << i << " " << k << std::endl;
        }
    }
    
    UF cluster(numNodes);
    
    std::cout << hamming0pairs.size() << " pairs with distance 0" << std::endl;
    std::cout << hamming1pairs.size() << " pairs with distance 1" << std::endl;
    std::cout << hamming2pairs.size() << " pairs with distance 2" << std::endl;
    
    while (!hamming0pairs.empty()){
        if (cluster.find(hamming0pairs[0][0]) != cluster.find(hamming0pairs[0][1])){
            std::cout << "Merged cluster " << cluster.find(hamming0pairs[0][0]) << " and " << cluster.find(hamming0pairs[0][1]) <<std::endl;
            cluster.unite(cluster.find(hamming0pairs[0][0]), cluster.find(hamming0pairs[0][1]));
        }
        hamming0pairs.erase(hamming0pairs.begin());
        std::cout << "Hamming 0 now has " << hamming0pairs.size() << " pairs." << std::endl;
    }
    
    while (!hamming1pairs.empty()){
        //if (hammingdist(nodes[hamming1pairs[0][0]-1], nodes[hamming1pairs[0][1]-1])){
            if (cluster.find(hamming1pairs[0][0]) != cluster.find(hamming1pairs[0][1])){
                std::cout << "Merged cluster " << cluster.find(hamming1pairs[0][0]) << " and " << cluster.find(hamming1pairs[0][1]) <<std::endl;
                cluster.unite(cluster.find(hamming1pairs[0][0]), cluster.find(hamming1pairs[0][1]));
            }
        //}
        hamming1pairs.erase(hamming1pairs.begin());
        std::cout << "Hamming 1 now has " << hamming1pairs.size() << " pairs." << std::endl;
    }
    
    while (!hamming2pairs.empty()){
        //if (hammingdist(nodes[hamming2pairs[0][0]-1], nodes[hamming2pairs[0][1]-1])){
            if (cluster.find(hamming2pairs[0][0]) != cluster.find(hamming2pairs[0][1])){
                std::cout << "Merged cluster " << cluster.find(hamming2pairs[0][0]) << " and " << cluster.find(hamming2pairs[0][1]) <<std::endl;
                cluster.unite(cluster.find(hamming2pairs[0][0]), cluster.find(hamming2pairs[0][1]));
            }
        //}
        hamming2pairs.erase(hamming2pairs.begin());
        std::cout << "Hamming 2 now has " << hamming2pairs.size() << " pairs." << std::endl;
    }
    
    std::cout << cluster.numGroups << std::endl;
    
    return 0;
}


/*
typedef struct bkTreeNode{
    int node_id;
    std::vector<int> position;
}bkTreeNode;

int hammingdist(std::vector<int> position1, std::vector<int> position2){
    int length = int(position1.size());
    int dist = 0;
    for (int i = 0; i < length; i++){
        if (position1[i] != position2[i])
            dist ++;
    }
    return dist;
}

class bkTree{
public:
    bkTree(std::vector<std::vector<int>> nodes, int max){
        std::vector<int> IDs;
        max_dist = max;
        bkTreeNode newNode;
        newNode.node_id = nodes[0][0];
        IDs.push_back(newNode.node_id);
        std::cout << "Node #" << newNode.node_id << " already put on tree!" << std::endl;
        newNode.position = nodes[0];
        newNode.position.erase(newNode.position.begin());
        //std::cout << "With " << newNode.position.size() << " digits!" << std::endl;
        root = newNode;
        std::vector<int> subtreeD;
        int length = int(nodes.size());
        std::vector<std::vector<std::vector<int>>> subtreeMat;
        for (int i = 1; i <= max_dist; i++){
            std::vector<std::vector<int>> newSubtree;
            subtreeMat.push_back(newSubtree);
        }
        for (int j = 1; j < length; j++){
            int group = hammingdist(nodes[j], nodes[0]);
            subtreeMat[group-2].push_back(nodes[j]);
        }
        
        std::vector<bkTree> subtreestmp;
        for (int i = 1; i <= max_dist; i++){
            if (subtreeMat[i-1].size() != 0){
                bkTree subtree(subtreeMat[i-1], max);
                subtreestmp.push_back(subtree);
                subtreeD.push_back(i);
                std::cout << subtree.root.position.size() << " digits" << std::endl;
                std::cout << subtree.all_node_id.size() << std::endl;
                IDs.insert(IDs.end(),subtree.all_node_id.begin(), subtree.all_node_id.end());
            }
        }
        subtrees = subtreestmp;
        subtreeDist = subtreeD;
        all_node_id = IDs;
    }
    int max_dist;
    bkTreeNode root;
    std::vector<int> all_node_id;
    std::vector<bkTree> subtrees;
    std::vector<int> subtreeDist;
    std::vector<std::vector<int>> distanceKpairsSameTree(int k){
        std::vector<std::vector<int>> top;
        int numSubtree = int(subtreeDist.size());
        for (int i = 0; i < numSubtree; i++){
            //std::cout << numSubtree << std::endl;
            //std::cout << subtrees.size() << std::endl;
            //std::cout << subtreeDist[i] << std::endl;
            if (subtreeDist[i] == k){
                //std::cout << "counting..." << std::endl;
                //std::cout << subtrees[i].all_node_id.size() << std::endl;
                for (int r : subtrees[i].all_node_id){
                    std::vector<int> tmp;
                    tmp.push_back(root.node_id);
                    tmp.push_back(r);
                    top.push_back(tmp);
                    //std::cout << "Added one more..." << std::endl;
                }
            }
            std::vector<std::vector<int>> tmptop = subtrees[i].distanceKpairsSameTree(k);
            top.insert(top.end(), tmptop.begin(), tmptop.end());
        }
        return top;
    }
};

int main(){
    //read input
    std::fstream fin("test2.txt");
    int numNodes;
    fin >> numNodes;
    int lengthNode;
    fin >> lengthNode;
    
    std::vector<std::vector<int>> nodes;
    
    for (int i = 1; i <= numNodes; i++){
        std::vector<int> line;
        line.push_back(i);
        for (int j = 0; j < lengthNode; j++){
            int digit;
            fin >> digit;
            line.push_back(digit);
        }
        nodes.push_back(line);
    }
    
    bkTree myBKTree(nodes, lengthNode);
    
    std::cout << "Build BK-tree finished!" << std::endl;
    
    std::vector<std::vector<int>> hamming1pairs = myBKTree.distanceKpairsSameTree(1);
    std::vector<std::vector<int>> hamming2pairs = myBKTree.distanceKpairsSameTree(2);
    
    std::cout << "# of pairs with dist = 1: " << hamming1pairs.size() << std::endl;
    std::cout << "# of pairs with dist = 2: " << hamming2pairs.size() << std::endl;
    
    UF cluster(numNodes);
    
    for (auto& k : nodes){
        k.erase(k.begin());
    }
    
    while (!hamming1pairs.empty()){
        if (cluster.find(hamming1pairs[0][0]) != cluster.find(hamming1pairs[0][1])){
            cluster.unite(cluster.find(hamming1pairs[0][0]), cluster.find(hamming1pairs[0][1]));
        }
        hamming1pairs.erase(hamming1pairs.begin());
    }
    
    while (!hamming2pairs.empty()){
        if (cluster.find(hamming2pairs[0][0]) != cluster.find(hamming2pairs[0][1])){
            cluster.unite(cluster.find(hamming2pairs[0][0]), cluster.find(hamming2pairs[0][1]));
        }
        hamming2pairs.erase(hamming2pairs.begin());
    }

    std::cout << cluster.numGroups << std::endl;
    
    return 0;
}
 */
/*
#include "union-find.h"
#include "hashtable.h"

int main(){
    //read input
    std::fstream fin("q2.txt");
    int numNodes;
    fin >> numNodes;
    int lengthNode;
    fin >> lengthNode;
    
    int hashLength1 = lengthNode/2;
    int hashLength2 = lengthNode/3;
    int tableSize1 = pow(2,hashLength1);
    int tableSize2 = pow(2,hashLength2);
    hashtable hashtable11(tableSize1);
    std::cout << hashtable11.size << std::endl;
    hashtable hashtable12(tableSize1);
    std::cout << hashtable12.size << std::endl;
    hashtable hashtable21(tableSize2);
    std::cout << hashtable21.size << std::endl;
    hashtable hashtable22(tableSize2);
    std::cout << hashtable22.size << std::endl;
    hashtable hashtable23(tableSize2);
    std::cout << hashtable23.size << std::endl;
    
    std::vector<std::vector<int>> nodes;

    for (int i = 1; i <= numNodes; i++){
        std::vector<int> line;
        for (int j = 0; j < lengthNode; j++){
            int digit;
            fin >> digit;
            line.push_back(digit);
        }
        nodes.push_back(line);
        
        int code11 = 0, code12 = 0, code21 = 0, code22 = 0, code23 = 0;
        for (int l = 0; l < hashLength1; l++){
            code11 += pow(2,l)*line[l];
            code12 += pow(2,l)*line[l+hashLength1];
        }
        for (int l = 0; l < hashLength2; l++){
            code21 += pow(2,l)*line[l];
            code22 += pow(2,l)*line[l+hashLength2];
            code23 += pow(2,l)*line[l+2*hashLength2];
        }
        hashtable11.insert(code11, i);
        hashtable12.insert(code12, i);
        hashtable21.insert(code21, i);
        hashtable22.insert(code22, i);
        hashtable23.insert(code23, i);
        
        code11 = 0, code12 = 0, code21 = 0, code22 = 0, code23 = 0;
        std::cout << "loop 1: " << i << std::endl;
    }
    
    UF cluster(numNodes);
    
    std::set<std::vector<int>> hamming1candidate;
    std::set<std::vector<int>> hamming2candidate;
    
    for (int i = 0; i < tableSize1; i++){
        std::vector<int> tabletmp;
        tabletmp = hashtable11.getValues(i);
        int length = int(tabletmp.size());
        if (length >= 2)
            for (int j = 0; j < length-1; j++){
                for (int l = j+1; l < length; l++){
                    std::vector<int> tmp;
                    tmp.push_back(tabletmp[j]);
                    tmp.push_back(tabletmp[l]);
                    hamming1candidate.insert(tmp);
                }
            }
        tabletmp = hashtable12.getValues(i);
        length = int(tabletmp.size());
        if (length >= 2)
            for (int j = 0; j < length-1; j++){
                for (int l = j+1; l < length; l++){
                    std::vector<int> tmp;
                    tmp.push_back(tabletmp[j]);
                    tmp.push_back(tabletmp[l]);
                    hamming1candidate.insert(tmp);
                }
            }
        std::cout << "loop 2: " << i << std::endl;
    }
    
    for (int i = 0; i < tableSize2; i++){
        std::vector<int> tabletmp;
        tabletmp = hashtable21.getValues(i);
        int length = int(tabletmp.size());
        if (length >= 2)
            for (int j = 0; j < length-1; j++){
                for (int l = j+1; l < length; l++){
                    std::vector<int> tmp;
                    tmp.push_back(tabletmp[j]);
                    tmp.push_back(tabletmp[l]);
                    hamming2candidate.insert(tmp);
                }
            }
        tabletmp = hashtable22.getValues(i);
        length = int(tabletmp.size());
        if (length >= 2)
            for (int j = 0; j < length-1; j++){
                for (int l = j+1; l < length; l++){
                    std::vector<int> tmp;
                    tmp.push_back(tabletmp[j]);
                    tmp.push_back(tabletmp[l]);
                    hamming2candidate.insert(tmp);
                }
            }
        tabletmp = hashtable23.getValues(i);
        length = int(tabletmp.size());
        if (length >= 2)
            for (int j = 0; j < length-1; j++){
                for (int l = j+1; l < length; l++){
                    std::vector<int> tmp;
                    tmp.push_back(tabletmp[j]);
                    tmp.push_back(tabletmp[l]);
                    hamming2candidate.insert(tmp);
                }
            }
        std::cout << "loop 3: " << i << std::endl;
    }
    
    std::cout << hamming1candidate.size() << std::endl;
    std::cout << hamming2candidate.size() << std::endl;
    
    while (!hamming1candidate.empty()){
        int a = (*hamming1candidate.begin())[0];
        int b = (*hamming1candidate.begin())[1];
        if (nodes[a] == nodes[b]){
            if (cluster.find(a) != cluster.find(b)){
                cluster.unite(cluster.find(a), cluster.find(b));
            }
        }
        hamming1candidate.erase(hamming1candidate.begin());
        std::cout << "loop 4: " << hamming1candidate.size() << std::endl;
    }
    
    while (!hamming2candidate.empty()){
        int a = (*hamming2candidate.begin())[0];
        int b = (*hamming2candidate.begin())[1];
        if (nodes[a] == nodes[b]){
            if (cluster.find(a) != cluster.find(b)){
                cluster.unite(cluster.find(a), cluster.find(b));
        }
        }
        hamming2candidate.erase(hamming2candidate.begin());
        std::cout << "loop 5: " << hamming2candidate.size() << std::endl;
    }
    
    std::cout << cluster.numGroups << std::endl;
    
    return 0;
}
 */


/* Question 1
 
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
    //std::cout << numNodes << std::endl;
    
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
        //std::cout << newEdge[0] << std::endl;
    }
    
    //sort the edges
    std::sort(edgeList.begin(), edgeList.end(), sortEdge);
    
    //start Kruskal's
    UF cluster(numNodes);
    while (cluster.numGroups > k){
        if (cluster.find(edgeList[0][0]) != cluster.find(edgeList[0][1])){
            cluster.unite(edgeList[0][0], edgeList[0][1]);
            std::cout << edgeList[0][0] << " " << edgeList[0][1] << " " << edgeList[0][2] << std::endl;
            //std::cout << cluster.find(409) << std::endl;
        }
        edgeList.erase(edgeList.begin());
        std::cout << "Groups: " << cluster.numGroups << std::endl;
    }
 
 
    //for (int i = 0; i < numNodes; i++){
    //    std::cout << i+1 << "     "  << cluster.find(i+1) << std::endl;
    //}
 
    
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

*/