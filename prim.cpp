#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>

int main(){

    std::unordered_map<int,bool> vMap;
    for(int i = 0 ; i <  6 ; i++ ){
        vMap.insert(std::make_pair(i,false));
    }

    int graph[][6] = {
        {0,1,4,0,0,0},
        {1,0,1,0,4,0},
        {4,1,0,3,0,0},
        {0,0,3,0,4,5},
        {0,4,0,4,0,0},
        {0,0,0,5,0,0}
    };

    //begin prim algo
    int finishVNum = 1 , weight_sum = 0;
    //begin in V.id = 0
    vMap.find(0)->second = true;

    while(finishVNum < 6){

    int source , dist , minWeight = 100;
    for(auto iter = vMap.begin() ; iter != vMap.end() ; iter++){
        if(iter->second){
            int tempid = iter->first;
            for(int j = 0 ; j < 6 ; j++){
                if(vMap.find(j)->second == false && graph[tempid][j] != 0 && minWeight >= graph[tempid][j]){
                    source = tempid;
                    dist = j;
                    minWeight = graph[tempid][j];
                }
            }
        }else{
            continue;
        }
    }

    //add v
    vMap.find(dist)->second = true;
    weight_sum += graph[source][dist];
    finishVNum++;
    std::cout << "edge : " << source << " -> " << dist << " = " << graph[source][dist] << std::endl;
    }//while

    std::cout << "weight_sum : " << weight_sum << std::endl;
    return 0;
}