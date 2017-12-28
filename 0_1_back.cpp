#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 6

struct thing{
    thing(float v, float w, float v_w):value(v),weight(w),v_w(v_w){}
    float value;
    float weight;
    float v_w;
};

bool comp(thing &a, thing &b){
    return a.v_w > b.v_w;
}

float weight[MAX];
float value[MAX];
float v_w[MAX];
float residue = 0;
int number = 0;
int back_weight = 0;
int final_result[MAX];
int current_result[MAX];
int best_weight = 0;
int current_weight = 0;
int current_value = 0;
int best_value = 0;
std::vector<thing> value_weight;

void BackTrack(int k){

    residue -= value_weight[k-1].value;
    if(k > number){
        //todo result
        if(current_value > best_value){
            best_value = current_value;
            for(int i = 1 ; i <= number ; i++){
                final_result[i] = current_result[i];
            }
        }
        return;
    }

    if(current_weight + value_weight[k-1].weight <= back_weight){
        current_weight += value_weight[k-1].weight;
        current_value += value_weight[k-1].value;
        current_result[k] = 1;
        BackTrack(k+1);
        current_weight -= value_weight[k-1].weight;
        current_value -= value_weight[k-1].value;
    }

    if(current_value + residue > best_value){
        current_result[k] = 0;
        BackTrack(k+1);
    }

    residue += value_weight[k-1].value;
}

int main(){ 
   

    std::cout << "please input the number of the things" << std::endl;
    std::cin >> number;
    std::cout << "please input the weight of the things" << std::endl;
    for(int i = 1 ; i <= number ; i++){
        std::cin >> weight[i];
    }
    std::cout << "please input the value of the things" << std::endl;
    for(int i = 1 ; i <= number ; i++){
        std::cin >> value[i];
        residue += value[i];
    }
    std::cout << "please input the max_weight of the bag" << std::endl;
    std::cin >> back_weight;

    //compute the value/weight

    for(int i = 1 ; i <= number ; i++){
        v_w[i] = value[i] / weight[i];
        value_weight.push_back(thing(value[i],weight[i],v_w[i]));
    }
    std::sort(value_weight.begin(),value_weight.end(),comp);

    BackTrack(1);
    for(int i = 1 ; i <= number ; i++){
        std::cout << i << "-" << final_result[i] << " , " ; 
    }
    std::cout << std::endl;
    std::cout << "the best max_value is : " << best_value << std::endl;
    return 0;
}

