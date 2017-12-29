#include <iostream>
#include <vector>

int graph[6][6] = {
        {0,0,0,0,0,0},
        {0,0,1,0,1,0},
        {0,1,0,1,1,1},
        {0,0,1,0,1,1},
        {0,1,1,1,0,1},
        {0,0,1,1,1,0}
    };

int vNum = 5;
int seen[6] = {0,0,0,0,0,0};
int final_result[6];
int do_not_know_name[6] = {0,0,0,0,0,0};
std::vector<int> path;

bool isOK(int source, int k){
    if(seen[k] == 0 && graph[source][k] != 0){
        return true;
    }else{
        return false;
    }
}

void Traceable(int source ,int k){

    if(k >= 1){
        seen[source] = 1;
        path.push_back(source);
        if(path.size() > 1 && path[path.size()-1] == path[path.size()-2]){
            path.pop_back();
        }

        do_not_know_name[source] += 1;
        for( ; do_not_know_name[source] <= vNum ; do_not_know_name[source] += 1){
            if(isOK(source,do_not_know_name[source])){
                break;
            }
        }

        if(do_not_know_name[source] <= vNum){
            if(k == vNum -1){
                if(graph[do_not_know_name[source]][path[0]] != 0){
                    //todo result
                    for(auto iter = path.begin() ; iter != path.end() ; iter++){
                        std::cout << *iter << ", ";
                    }
                    std::cout << do_not_know_name[source] << std::endl;
                }else{
                    path.pop_back();
                    Traceable(source,k);
                }
            }else if(k < vNum-1){
                Traceable(do_not_know_name[source],k+1);
            }
        }else{
            seen[source] = 0;
            path.pop_back();
            Traceable(path[path.size()-1],k-1);
        }
        //here is so important if code with if(do_not_know_name > vNum) ,it is wrong 
        //because 3->4 4->5(x) 5->4 4->6 4->3,3->5 5-4(ok), 5->3, 3->4, next is import 4->3 so satisfy the if
        
        //if(do_not_know_name[source] > vNum){
            //seen[source] = 0;
            //path.pop_back();
            //Traceable(path[path.size()-1],k-1);
        //}
    }
}

int main(){

    int source = 0;
    std::cout << "please input the source of the traceable" << std::endl;
    std::cin >> source;
    Traceable(source,1);
    return 0;    
    
}