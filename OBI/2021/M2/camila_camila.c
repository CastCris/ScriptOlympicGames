#include<stdio.h>
//
int main(){
    int ages[3];
    size_t ages_size=sizeof(ages)/sizeof(ages[0]);
    for(int i=0;i<ages_size;++i)
        scanf("%i",&ages[i]);

    for(int i=0;i<ages_size;++i){
        for(int j=i;j<ages_size;++j){
            if(ages[i]>ages[j]){
                ages[i]+=ages[j];
                ages[j]=ages[i]-ages[j];
                ages[i]-=ages[j];
            }
        }
    }
    printf("%i\n",ages[1]);

    return 0;
}
