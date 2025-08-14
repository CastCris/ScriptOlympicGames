#include<iostream>
#include<cmath>
//
int main(){
    int n,m;
    std::scanf("%i %i",&n,&m);

    int n_range=std::ceil(std::pow(n,1.0/6.0));
    int m_range=std::floor(std::pow(m,1.0/6.0));

    int count=m_range-n_range+1;

    printf("%i\n",count);

    return 0;
}
