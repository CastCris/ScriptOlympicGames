#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sort_word(char*word){
    for(size_t i=0;i<strlen(word);++i){
        for(size_t j=i;j<strlen(word);++j){
            if(word[i]>word[j]){
                word[i]+=word[j];
                word[j]=word[i]-word[j];
                word[i]-=word[j];
            }
        }
    }
}

//
int main(){
    size_t n,m,k;
    scanf("%zu %zu %zu",&n,&m,&k);

    char*password=malloc(sizeof(char)*(n+1)),
        *path=malloc(sizeof(char)*(m+1)),
       **regex=malloc(sizeof(char*)*m);

    scanf("%s",password);
    for(size_t i=0;i<m;++i){
        regex[i]=malloc(sizeof(char)*k);
        scanf("%s",regex[i]);
        sort_word(regex[i]);
        //printf("%s\n",regex[i]);
    }

    int depth_level_max;
    double depth_level_curr=0;
    scanf("%i",&depth_level_max);

    for(size_t i=0;i<m;++i){
        for(size_t j=0;j<k;++j){
            double depth_level=pow(k,(m-i-1));
            //printf("%lf %lf\n",depth_level,depth_level_curr);
            if(depth_level+depth_level_curr>=(double)depth_level_max){
                path[i]=regex[i][j];
                break;
            }
            depth_level_curr+=depth_level;
        }
        //printf("\n");
    }

    //printf("%i\n",depth_level_curr);
    //printf("%s\n",path);
    size_t path_index=0;
    for(size_t i=0;i<(size_t)n;++i){
        if(password[i]=='#'){
            printf("%c",path[path_index]);
            ++path_index;
            continue;
        }
        printf("%c",password[i]);
    }

    return 0;
}
