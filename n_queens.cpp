#include <iostream>
#include <math.h>
#include <stdlib.h>

int final_sum = 0;

bool place(int k, int *final_result){
    for(int i = 1 ; i < k ; i ++){
        if(final_result[i] == final_result[k] || abs(final_result[k] - final_result[i]) == abs(k-i)){
            return false;
        }
    }
    return true;
}
void n_queens(int *final_result , int number , int k){
    
    if(k >= 1){
        final_result[k] += 1;
        for( ; final_result[k] <= number ; final_result[k] += 1){
            if(place(k,final_result)){ 
                break;
            }
        }

        if(final_result[k] <= number){
            if(k == number){
                //todo result
                final_sum++;
                for(int i = 1 ; i <= number ; i++){
                    std::cout << "queen-" << i << ": " << final_result[i] << std::endl;
                }
                //return;
                final_result[k] = 0;
                n_queens(final_result,number,k-1);
            }else if(k < number){
                n_queens(final_result,number,k+1);
            }
        }else{
            //backTrack
            final_result[k] = 0;
            n_queens(final_result,number,k-1);
        }

    }

}


int main(){

    int number = 0;
    int final_result[100];
    std::cout << "please input the number of the queens" << std::endl;
    std::cin >> number;

    for(int i = 1 ; i <= number ; i++){
        final_result[i] = 0;
    }

    n_queens(final_result,number,1);
    std::cout << "final_sum: " << final_sum << std::endl;
    return 0;
}