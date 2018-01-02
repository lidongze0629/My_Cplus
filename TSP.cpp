#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
#include <functional>
#include <math.h>

#define N 6
class node{
public:
    int path_start;
    int path_end;
    int number_of_path;
    int sum_of_distance;
    int lb;
    std::vector<int> path;
    bool vis[100];  

    node(){}
};

bool operator < (const node &t1, const node &t2){
    return t1.lb < t2.lb;
}

int up ,low = 0;
int number;
int ret = INT16_MAX;
std::priority_queue<node> final_result;


void get_up(){
    up = 16;
}

void get_low(int graph[N][N]){
    //get row + get column
    /*for(int i = 1 ; i <= number ; i++){
        std::priority_queue<int> row;
        for(int j = 1 ; j <= number ; j++){
            row.push(graph[i][j]);
        }
        low += row.top();
    }
    for(int j = 1; j <= number ; j++){
        std::priority_queue<int> column;
        for(int i = 1 ; i <= number ; i++){
            column.push(graph[i][j]);
        }
        low += column.top();
    }
    low = ceil(low/2);*/

    for(int i = 1 ; i <= number ; i++){
        std::priority_queue<int, std::vector<int>, std::greater<int> > row;
        for(int j = 1 ; j <= number ; j++){
            row.push(graph[i][j]);
        }
        low += row.top();
        row.pop();
        low += row.top();
    }
    low = ceil(low/2);    
}

int get_lb(node p, int graph[N][N]){
    int low_bound = p.sum_of_distance * 2;
    int min1 = INT16_MAX , min2 = INT16_MAX;

    for(int i = 1; i <= number ; i++){
        if(p.vis[i] == 0 && min1 > graph[p.path_start][i]){
            min1 = graph[p.path_start][i];
        }
    }
    low_bound += min1;

    for(int i = 1 ; i <= number ; i++){
        if(p.vis[i] == 0 && min2 > graph[p.path_end][i]){
            min2 = graph[p.path_end][i];
        }
    }
    low_bound += min2;

    for(int i = 1 ; i <= number ; i++){
        if(p.vis[i] == 0){
            min1 = min2 = INT16_MAX;
            for(int j = 1 ; j <= number ; j++){
                if(min1 > graph[i][j]) {min1 = graph[i][j];}
            }
            for(int j = 1 ; j <= number ; j++){
                if(min2 > graph[j][i]) {min2 = graph[j][i];}
            }
            low_bound += (min1+min2);
        }
    }
    return ceil(low_bound/2);
}

void Tsp(int graph[N][N]){

    while(!final_result.empty()){
        node temp = final_result.top();
        std::cout << "here is the temp: " << temp.path_end << std::endl;
        std::cout << "here is the temp_lb: " << temp.lb<< std::endl;
        final_result.pop();

        if(temp.number_of_path == number-1){
            //last
            int last_city = 0;

            for(int i = 1 ; i <= number ; i++){
                if(temp.vis[i] == 0){
                    last_city = i;
                    break;
                }
            }
            if(last_city == 0) {std::cout << "what the fuck!!!" << std::endl;}
            int answer_sum_of_path = temp.sum_of_distance +  graph[temp.path_end][last_city] + graph[last_city][temp.path_start];
            node judge = final_result.top();
            if(answer_sum_of_path <= judge.lb){
                std::cout << "dfjdj" << std::endl;
                ret = std::min(answer_sum_of_path,ret);
                std::cout << "the min distance path: ";
                for(auto iter = temp.path.begin() ; iter != temp.path.end() ; iter++){
                    std::cout << *iter << ", ";
                }
                std::cout << last_city << std::endl;
                break;
            }else{
                up = std::min(up,answer_sum_of_path);
                ret = std::min(answer_sum_of_path,ret);
                continue;
            }
        }

        for(int i = 1; i <= number; i++){
            if(temp.vis[i] == 0){
                node next;
                next.path_start = temp.path_start;
                next.path_end = i;
                next.sum_of_distance = temp.sum_of_distance + graph[temp.path_end][i];
                next.number_of_path = temp.number_of_path + 1;
                for(auto iter = temp.path.begin() ; iter != temp.path.end() ; iter++){
                    next.path.push_back(*iter);
                }
                next.path.push_back(i);
                for(int j=1;j<=number;j++) next.vis[j]=temp.vis[j];  
                next.vis[i]=1;
                next.lb = get_lb(next,graph);
                if(next.lb >= up) {continue;}
                final_result.push(next);
            }
        }
    }
}

void init(int source, int dist, int graph[N][N]){
    get_up();
    get_low(graph);

    node src;
    src.path_start = source;
    src.path_end = dist;
    src.lb = low;
    src.number_of_path = 1;
    src.sum_of_distance = 0;
    for(int i=1;i<=number;i++) src.vis[i]=0;  
    src.vis[source]=1; 
    src.path.push_back(source);
    final_result.push(src);

    Tsp(graph);

}

int main(){
    int source,dist;
    int graph[N][N] = {
        {0,0,0,0,0,0},
        {0,9999,3,1,5,8},
        {0,3,9999,6,7,9},
        {0,1,6,9999,4,2},
        {0,5,7,4,9999,3},
        {0,8,9,2,3,9999}
    };
    std::cout << "please input the number of the city" << std::endl;
    std::cin  >> number;
    std::cout << "please input the source of the TSP" << std::endl;
    std::cin >> source;
    std::cout << "please input the dist of the TSP" << std::endl;
    std::cin >> dist;

    init(source,dist,graph);

    std::cout << "the min distance is: " << ret << std::endl;

    return 0;
}
