#include <iostream>
#include <vector>

int best_value = 0;
int current_value = 0;
int number = 0;
std::vector<int> weight;
int final_result[50];
int currnt_result[50];

int boat_max_weight = 0;
int residue = 0;

int init(){
    std::cout << "please input the number of the container" << std::endl;
    std::cin >> number;
    std::cout << " please input the weight of each container " << std::endl;
    for(int i = 0 ; i < number ; i++){
        int temp;
        std::cin >> temp;
        weight.push_back(temp);
    }
    std::cout << "please input the max_weight of the boat" << std::endl;
    std::cin >> boat_max_weight;

    for(int i = 0 ; (unsigned int)i < weight.size() ; i++){
        residue += weight[i];
    }
    return 1;
}

void BackTrack(int k){

    residue -= weight[k-1];

    if(k > number){
        //todo for the result
        if(current_value > best_value){
            for(int i = 1 ; i <= number ; i++){
                final_result[i] = currnt_result[i];
                best_value = current_value;
            }
        }
        return;
    }

    if(current_value + weight[k-1] <= boat_max_weight){
        //todo left child
        current_value += weight[k-1];
        currnt_result[k] = 1;
        BackTrack(k+1);
        current_value -= weight[k-1];
    }
    
    if(current_value + residue > best_value){
        //todo right child 
        currnt_result[k] = 0;
        BackTrack(k+1);
    }

    residue += weight[k-1];
}



int main(){

    init();
    BackTrack(1);
    std::cout << "final result is: " ;
    for(int i = 1 ; i <= number ; i++){
        std::cout << i << "-" << final_result[i] << " , " ; 
    }
    std::cout << std::endl;
    std::cout << "for one boat, the best max_weight is : " << best_value << std::endl;
}