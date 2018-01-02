#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
#include <functional>
#include <fstream>
#include <sstream>
#include <math.h>

#define N 50
#define MAX 9999
class node{
public:
    int start;
    int end;
    int number;
    int sum_of_distace;
    int sum_of_cost;
    int lb;
    std::vector<int> path;
    bool vis[N+1];

    node(){}
};

bool operator < (const node &t1, const node &t2){
    return t1.lb > t2.lb;
}

int distance[N+1][N+1], cost[N+1][N+1], min_dis[N+1][N+1], min_cost[N+1][N+1];
int up, low , result = MAX;
std::priority_queue<node> final_result;


void load_graph(){
    std::string str;
    std::ifstream infile;
    infile.open("m1.txt");
    if(!infile){
        std::cout << "error load m1.txt" << std::endl;
    }
    for(int i = 1 ; i <= N ; i++){
        getline(infile,str);
        std::istringstream is(str);
        for(int j = 1 ; j <= N ; j++){
            is >> distance[i][j];
        }
    }
    infile.close();

    infile.open("m2.txt");
    if(!infile){
        std::cout << "error load m2.txt" << std::endl;
    }
    for(int i = 1 ; i <= N ; i++){
        getline(infile,str);
        std::istringstream is(str);
        for(int j = 1 ; j <= N ; j++){
            is >> cost[i][j];
        }
    }
    infile.close();

    for(int i = 1; i <= N; i++){
        for(int j = 1 ; j <= N; j++){
            if(distance[i][j] == 9999){
                cost[i][j] = 9999;
            }
        }
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1 ; j <= N ; j++){
            min_dis[i][j] = distance[i][j];
            min_cost[i][j] = cost[i][j];
        }
    }
}

void floyd(){
    for(int k = 1 ; k <= N ;k++){
        for(int i = 1; i <= N ;i++){
            for(int j = 1; j <= N ;j++){
                if(min_dis[i][j]>(min_dis[i][k]+min_dis[k][j])){
                    min_dis[i][j] = min_dis[i][k] + min_dis[k][j];
                }
                if(min_cost[i][j]>(min_cost[i][k]+min_cost[k][j])){
                    min_cost[i][j] = min_cost[i][k] + min_cost[k][j];
                }
            }
        }
    }
    //对角线 处理一下
    for(int i = 1 ; i <= N ;i++){
        min_dis[i][i] = 0;
        min_cost[i][i] = 9999;
    }
}

void init(){
    up = 600;
    low = 200;

    node src;
    src.start = 1;
    src.end = 1;
    src.lb = low;
    src.number = 1;
    src.sum_of_cost = 0;
    src.sum_of_distace = 0;
    for(int i = 1; i <= N ;i++){
        src.vis[i] = 0;
    }
    src.vis[1] = 1;
    src.path.push_back(1);
    final_result.push(src);
}



int get_lb(node p){
  /*
    int low_bound = p.sum_of_distace * 2;
    int min1 = MAX; int min2 = MAX;

    //取low_bound的时候，已经用floyd算法，所以可以看成是无向图
    for(int i = 1; i <= N ; i++){
        if(p.vis[i] == 0 && min1 > min_dis[p.start][i]){
            min1 = min_dis[p.start][i];
        }
    }
    low_bound += min1;

    for(int i = 1; i <= N; i++){
        if(p.vis[i] == 0 && min2 > min_dis[p.end][i]){
            min2 = min_dis[p.end][i];
        }
    }
    low_bound += min2;

    for(int i = 1 ; i <= N ; i++){
        if(p.vis[i] == 0){
            min1 = min2 = MAX;
            for(int j = 1 ; j <= N ; j++){
                if(min1 > min_dis[i][j]) {min1 = min_dis[i][j];}
            }
            for(int j = 1 ; j <= N ; j++){
                if(min2 > min_dis[j][i]) {min2 = min_dis[j][i];}
            }
            low_bound += (min1+min2);
        }
    }
    //return ceil(low_bound/2);*/
    return (p.sum_of_distace + min_dis[p.end][N]);
}

void Tsp(){
  int ldz = 0;
    while(!final_result.empty()){
      ldz++;
        node temp = final_result.top();
        final_result.pop();

          /*if(ldz> 20 && ldz <=30){
            std::cout << "--------------------------------" <<std::endl;
            std::cout << "now kuozhan: " << temp.end << std::endl;
            std::cout << "kuozhan.lb: " << temp.lb << std::endl;
          }*/

        if(temp.end == N){
            //已经找到了num50.
            int answer = temp.sum_of_distace;
            node judge = final_result.top();
            if(answer <= judge.lb){
                result = std::min(answer,result);
                std::cout << "found a path from No.1->No.50: " << std::endl;
                std::cout << "the distace is: " << temp.sum_of_distace << std::endl;
                std::cout << "the cost is: " << temp.sum_of_cost << std::endl;
                std::cout << "the path is: " ;
                for(auto iter = temp.path.begin(); iter != temp.path.end() ; iter++){
                    std::cout << *iter << ", ";
                }
                std::cout << std::endl;
                break;
            }else{
                up = std::min(up,answer);
                result = std::min(answer,result);
                continue;
            }

        }

        for(int i = 1 ; i <= N ; i++){
            if(temp.vis[i] == 0 && distance[temp.end][i] != 9999){
                //保证 从目前节点开始，既要没有访问的节点，而且从目前节点还能到达的节点
                //if(ldz > 20 && ldz <= 30){
                //  std::cout << "dfs: " << i << std::endl;
                //}
                node next;
                next.start = temp.start;
                next.end = i;
                next.sum_of_distace = temp.sum_of_distace + distance[temp.end][i];
                next.sum_of_cost = temp.sum_of_cost + cost[temp.end][i];
                next.number = temp.number + 1;
                for(int j = 1 ; j <= N ; j++){
                    next.vis[j] = temp.vis[j];
                }
                next.vis[i] = 1;
                for(auto iter = temp.path.begin() ; iter != temp.path.end() ; iter++){
                    next.path.push_back(*iter);
                }
                next.path.push_back(i);
                next.lb = get_lb(next);
                //if(ldz > 20 && ldz <= 30){
                //  std::cout << "here2_end: "<<next.end << std::endl;
                //  std::cout << "here3_lb: "<<next.lb << std::endl;
                //  std::cout << "here4_sum_cost: " << next.sum_of_cost << std::endl;
                //}
                if(next.lb >= up){
                    continue;
                }
                if(next.sum_of_cost > 1500){
                    continue;
                }
                final_result.push(next);
            }
        }
    }
}

int main(){
    load_graph();
    floyd();
    init();
    Tsp();
    /*for(int i = 1 ; i <= N; i++){
        for(int j =1 ; j <= N ;j++){
            std::cout << min_dis[i][j] << ", ";
        }
        std::cout << std::endl;
    }*/
    //std::cout << result << std::endl;
    return 0;
}
