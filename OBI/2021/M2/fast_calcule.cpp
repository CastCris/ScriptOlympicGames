#include<algorithm>
#include<iostream>
#include<vector>

std::vector<int>number_decompose(int x){
    std::vector<int>num;
    while(x){
        num.push_back(x%10);
        x/=10;
    }
    std::reverse(num.begin(),num.end());
    return num;
}
int calcule_sum_digits_equal(std::vector<int>num,int trigget,size_t level,int sum,int equal){
    if(sum==equal)
        return 1;
    if(level>=num.size()||sum>equal)
        return 0;

    int range_max=(trigget)?num[level]:9;
    int num_level=num[level];
    int instance=0;
    for(int i=0;i<=range_max;++i){
        int new_trigget=(trigget&&i==num_level)?1:0;
        int new_sum=sum+i;

        instance+=calcule_sum_digits_equal(num,new_trigget,level+1,new_sum,equal);
    }
    return instance;
}
//
int main(){
    int s,a,b;
    std::scanf("%i",&s);
    std::scanf("%i",&a);
    std::scanf("%i",&b);

    std::vector<int>a_decompose=number_decompose(a-1);
    std::vector<int>b_decompose=number_decompose(b);

    int a_digits=calcule_sum_digits_equal(a_decompose,1,0,0,s);
    int b_digits=calcule_sum_digits_equal(b_decompose,1,0,0,s);
    
    printf("%i\n",b_digits-a_digits);

    return 0;
}
