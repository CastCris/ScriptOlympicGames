#include<stdio.h>
//
int main(){
    int n;
    scanf("%i",&n);

    int arr[n];
    for(size_t i=0;i<(size_t)n;++i)
        scanf("%i",&arr[i]);

    size_t left=0,right=n-1;
    int left_value=arr[left],
        right_value=arr[right],
        moves=0;
    while(1){
        if(left==right)
            break;
        if(left_value==right_value&&right-left==1)
            break;
        if(left_value==right_value){
            ++left;
            --right;

            left_value=arr[left];
            right_value=arr[right];
            continue;
        }

        if(left_value<right_value){
            ++left;
            ++moves;
            left_value+=arr[left];
            continue;
        }
        if(left_value>right_value){
            --right;
            ++moves;
            right_value+=arr[right];
            continue;
        }
    }

    printf("%i\n",moves);

    return 0;
}
