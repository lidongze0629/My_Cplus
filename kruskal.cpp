#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>

struct edges{
    edges(int s , int d , int w):source(s),dist(d),weight(w){}
    int source;
    int dist;
    int weight;
};

bool comp(edges &a , edges &b){
    return a.weight < b.weight;
}

int main(){

    std::vector<edges> edge_array;
    int graph[][6] = {
        {0,1,4,0,0,0},
        {1,0,1,0,4,0},
        {4,1,0,3,0,0},
        {0,0,3,0,4,5},
        {0,4,0,4,0,0},
        {0,0,0,5,0,0}
    };

    std::unordered_map<int,int> vTree;
    for(int i = 0 ; i < 6 ; i++){
        vTree.insert(std::make_pair(i,i));
    }

    for(int i = 0 ; i < 6 ; i++){
        for(int j = i+1 ; j < 6 ; j++){
            if(graph[i][j] != 0){
                edge_array.push_back(edges(i,j,graph[i][j]));
                edge_array.push_back(edges(j,i,graph[i][j]));
            }
        }
    }

    std::sort(edge_array.begin(),edge_array.end(),comp);

    //krusal algorithm begin
    int weight_sum = 0;
    int i = 0;
    for(auto iter = edge_array.begin(); iter != edge_array.end() ; iter++){
        if(i >= 5){
            break;
        }else{
            if( vTree.find(iter->source)->second == vTree.find(iter->dist)->second ){
                continue;
            }else{
                i++;
                weight_sum += iter->weight;
                if(iter->source < iter->dist){
                    vTree.find(iter->dist)->second = vTree.find(iter->source)->second;
                }else{
                    vTree.find(iter->source)->second = vTree.find(iter->dist)->second;
                }
                std::cout << "edge: " << iter->source << " -> " << iter->dist << " = " << iter->weight << std::endl; 
             }
        }
    }
    std::cout << "the MST result is : " << weight_sum << std::endl;

    return 0;
}