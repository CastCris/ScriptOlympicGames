#include<iostream>
#include<set>
//
int circle_rectangle(int*array,size_t n){
    int circo=0;
    for(size_t i=0;i<n;++i)
        circo+=array[i];
    if(circo%2)
        return 0;

    int half_circo=circo/2;


    int*prefix_sum=(int*)calloc((n+1),sizeof(int));
    for(size_t i=0;i<n;++i){
        prefix_sum[i+1]=prefix_sum[i]+array[i];
    }
    std::set<int>prefix_set(prefix_sum,prefix_sum+n);

    int sides=0;
    for(size_t i=0;i<n;++i){
        int oppose_side=(prefix_sum[i]+half_circo)%circo;
        auto element=prefix_set.find(oppose_side);
        if(element!=prefix_set.end())
            ++sides;
    }
    if(sides/2>=2)
        return 1;

    return 0;
}

int main(){
    size_t n;
    std::scanf("%li",&n);
    int*array=(int*)malloc(sizeof(int)*n);

    for(size_t i=0;i<n;++i)
        std::scanf("%i",&array[i]);

    if(circle_rectangle(array,n))
        std::printf("S\n");
    else
        std::printf("N\n");
}
