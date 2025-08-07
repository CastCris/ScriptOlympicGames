#include<iostream>
#include<cmath>

#define BLUR_CHAR '#'

int comp(const void*a,const void*b){
    return (*(char*)a-*(char*)b);
}

void clear_buffer(){
    int c;
    while((c=getchar())!='\n'&&c!=EOF){};
}
//
int main(){
    size_t n,m,k;
    std::scanf("%zu %zu %zu",&n,&m,&k);

    char*password=(char*)malloc(sizeof(char)*(n+1)),
        *path=(char*)malloc(sizeof(char)*(m+1)),
        **regex=(char**)malloc(sizeof(char*)*m);
    std::scanf("%s",password);

    for(size_t i=0;i<m;++i){
        regex[i]=(char*)malloc(sizeof(char)*(k+1));
        std::scanf("%s",regex[i]);
        std::qsort(regex[i],k,sizeof(regex[i][0]),comp);
    }
    double depth_level_max,
           depth_level_curr=0;
    std::scanf("%lf",&depth_level_max);
    for(size_t i=0;i<m;++i){
        double depth_level=std::pow(k,(m-i-1));
        for(size_t j=0;j<k;++j){
            if(depth_level+depth_level_curr>=depth_level_max){
                path[i]=regex[i][j];
                break;
            }
            depth_level_curr+=depth_level;
        }
    }

    size_t path_index=0;
    for(size_t i=0;i<n;++i){
        if(password[i]==BLUR_CHAR){
            std::printf("%c",path[path_index]);
            ++path_index;
            continue;
        }
        std::printf("%c",password[i]);
    }
    std::printf("\n");

    return 0;
}
