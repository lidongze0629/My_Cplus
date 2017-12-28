#include <iostream>

int vNum = 5 , m_color = 3 ;

int color[6] = {0,0,0,0,0,0};

int graph[6][6] = {
         {0,0,0,0,0,0},
         {0,0,1,1,0,0},
         {0,1,0,1,1,1},
         {0,1,1,0,0,1},
         {0,0,1,0,0,1},
         {0,0,1,1,1,0}
        }; 

bool isOK(int v){
    for(int i = 1 ; i < 6 ; i++){
        if(graph[v][i] == 1 && color[i] == color[v]){
            return false;
        }
    }
    return true;
}

/*void GraphColor(){
    
    int k = 1 ;
    while (k >= 1){

        color[k] += 1;
        for(;color[k] <= m_color;color[k] += 1){
            if(isOK(k)){
                break;
            }
        }

        if(color[k] <= m_color && k == vNum){
            //todo result
            for(int i = 1 ; i <= vNum ; i++){
                std::cout << "map-" << i <<": "<< color[i] << std::endl;
            }
            std::cout << std::endl;
            return ;
        }

        if(color[k] <= m_color && k < vNum){
            k = k+1;
        }

        if(color[k] > m_color){
            color[k] = 0;
            k = k-1;
        }

    }

}*/

void GraphColor_iter(int k){
    
    if(k >= 1){
        color[k] += 1;
        for( ; color[k] <= m_color; color[k] += 1){
            if(isOK(k)){
                break;
            }
        }
        if(color[k] <= m_color){
            if(k == vNum){
                //todo result
                for(int i = 1 ; i <= vNum ; i++){
                    std::cout << "map-" << i << ": " << color[i] << std::endl;
                }
                //return 1;
            }else if(k < vNum){
                GraphColor_iter(k+1);
            }
        }
        
        if(color[k] > m_color){
            color[k] = 0;
            GraphColor_iter(k-1);
        }
    }
}

int main(){

    GraphColor_iter(1);
    return 1;

}