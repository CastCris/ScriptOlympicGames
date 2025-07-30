#include<stdio.h>
#include<stdlib.h>

#define MAX_FRIEND_ID 101

//
int main(){
    int time_start[MAX_FRIEND_ID],
        time_ended[MAX_FRIEND_ID],
        last_operation[MAX_FRIEND_ID];

    for(size_t i=0;i<MAX_FRIEND_ID;++i){
        time_start[i]=-1;
        time_ended[i]=-1;
        last_operation[i]=-1;
    }
    //
    int n,time=0;
    scanf("%i",&n);
    for(int i=0;i<n;++i){
        char gate[3],number[5];
        scanf("%s %s",gate,number);
        int n=atoi(number);
        //printf("%s %s %i\n",gate,number,time);

        if(gate[0]=='T'){
            time+=n-1;
            continue;
        }
        last_operation[n]=gate[0];

        if(gate[0]=='R'&&time_start[n]==-1){
            time_start[n]=time;
        }else if(gate[0]=='E'&&time_ended[n]==-1){
            time_ended[n]=time;
        }else if(gate[0]=='E'){
            time_ended[n]=time;
            ++time_start[n];
        }

        time++;
    }

    for(size_t i=0;i<MAX_FRIEND_ID;++i){
        if(time_start[i]==-1)
            continue;
        if(last_operation[i]=='R')
            printf("%li %i\n",i,-1);
        else
            printf("%li %i\n",i,time_ended[i]-time_start[i]);
    }

    return 0;
}
