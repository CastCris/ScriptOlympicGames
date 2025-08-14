#include<iostream>
#include<vector>
//
int main(){
    int n;
    std::scanf("%i",&n);
    std::vector<int>array;
    for(int i=0;i<n;++i){
        int temp;
        std::scanf("%i",&temp);
        array.push_back(temp);
    }

    int left=0,right=n-1,
        left_value=array[left],right_value=array[right],
        moves=0;
    while(1){
        if(left==right)
            break;
        if(left_value==right_value&&right-left==1)
            break;

        if(right_value==left_value){
            ++left;
            --right;
            left_value=array[left];
            right_value=array[right];
        }

        if(left_value<right_value){
            ++left;
            ++moves;
            left_value+=array[left];
            continue;
        }
        if(left_value>right_value){
            --right;
            ++moves;
            right_value+=array[right];
            continue;
        }
    }
    std::printf("%i\n",moves);


    return 0;
}

