#include<iostream>
//
int main(){
    int n,m;
    std::cin>>n>>m;
    int set_invalids[401][2]={0};
    for(int i=0;i<m;++i){
        int x,y;
        std::cin>>x>>y;
        set_invalids[i][0]=x-1;
        set_invalids[i][1]=y-1;
    }
    int answer=0;
    for(int mask=1;mask<(1<<n);++mask){
        int valid=1;
        for(int j=0;j<m;++j){
            if((mask & (1<<set_invalids[j][0])) && (mask & (1<<set_invalids[j][1]))){
                valid=0;
                break;
            }
        }
        if(valid)
            ++answer;
    }
    std::cout<<answer<<"\n";

    return 0;
}
