#include<stdio.h>
#include<stdlib.h>

#define QUEUE_SIZE_MAX 100001

struct Queue{
    int array[QUEUE_SIZE_MAX];
    size_t index;
    size_t length;
};

struct Queue*queue_create(){
    struct Queue*queue_new=malloc(sizeof(struct Queue));
    queue_new->index=0;
    queue_new->length=QUEUE_SIZE_MAX;

    return queue_new;
}
inline size_t queue_index(struct Queue*queue_ref){
    return queue_ref->index;
}

inline void queue_pop(struct Queue*queue_ref){
    --queue_ref->index;
}

inline void queue_push(struct Queue*queue_ref,int n){
    queue_ref->array[queue_index(queue_ref)]=n;
    ++queue_ref->index;
}

int main(){
    int n;
    struct Queue*queue=queue_create();
    for(scanf("%i",&n);n;--n){
        int sales;
        scanf("%i",&sales);
        if(sales)
            queue_push(queue,sales);
        else
            queue_pop(queue);
    }

    int tot=0;
    for(size_t i=0;i<queue_index(queue);++i)
        tot+=queue->array[i];
    printf("%i\n",tot);

    return 0;
}
