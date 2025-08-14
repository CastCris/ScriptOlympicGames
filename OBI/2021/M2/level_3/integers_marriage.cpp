#include<iostream>
#include<vector>
#include<cmath>

template<typename T>
using VECTOR = std::vector<T>;
//
VECTOR<int>num_decompose(int x){
    VECTOR<int>num;
    while(x){
        num.push_back(x%10);
        x/=10;
    }

    return num;
}

int num_from_vector(VECTOR<int>x){
    if(!x.size())
        return -1;
    int num=0;
    for(size_t i=0;i<x.size();++i){
        int digit=x[i]*pow(10,i);
        num+=digit;
    }

    return num;
}

int main(){
    int n,m;
    std::scanf("%i\n%i",&n,&m);

    VECTOR<int>x=num_decompose(n);
    VECTOR<int>y=num_decompose(m);

    while(x.size()<y.size())
        x.push_back(0);
    while(x.size()>y.size())
        y.push_back(0);

    VECTOR<int>x_new,y_new;
    for(size_t i=0;i<x.size();++i){
        int x_item=x[i];
        int y_item=y[i];

        if(x_item>y_item){
            x_new.push_back(x_item);
            continue;
        }
        if(x_item<y_item){
            y_new.push_back(y_item);
            continue;
        }

        x_new.push_back(x_item);
        y_new.push_back(y_item);
    }

    /*
    for(int i:x_new)
        printf("%i ",i);
    printf("\n");
    for(int i:y_new)
        printf("%i ",i);
    printf("\n");*/

    int x_num=std::max(num_from_vector(x_new),num_from_vector(y_new)),
        y_num=std::min(num_from_vector(x_new),num_from_vector(y_new));

    std::printf("%i %i\n",y_num,x_num);

    return 0;
}
