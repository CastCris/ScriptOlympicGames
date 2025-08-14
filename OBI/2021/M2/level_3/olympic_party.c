#include<stdio.h>
#include<stdlib.h>

#define MIN(x,y) (((x)<(y))?(x):(y))

#define INTERVAL_LEN_MAX 10000

//
struct Vector{
    int*array;
    size_t index;
    size_t length;
};
struct Vector*vct_create(const size_t vct_size){
    struct Vector*vct_new=malloc(sizeof(struct Vector));
    vct_new->array=malloc(sizeof(int)*vct_size);
    vct_new->index=0;
    vct_new->length=vct_size;

    return vct_new;
}


static inline size_t vct_index(const struct Vector*vct_ref){
    return vct_ref->index;
}

static inline size_t vct_length(const struct Vector*vct_ref){
    return vct_ref->length;
}

static inline int vct_item(const struct Vector*vct_ref,size_t index){
    return vct_ref->array[index];
}


void vct_append(struct Vector*vct_ref,const int item){
    if(vct_index(vct_ref)>=vct_length(vct_ref)){
        vct_ref->length*=2;
        vct_ref->array=realloc(vct_ref->array,sizeof(int)*vct_length(vct_ref));
    }
    vct_ref->array[vct_index(vct_ref)]=item;
    ++vct_ref->index;
}

void vct_pop(struct Vector*vct_ref){
    --vct_ref->index;
}

void vct_display(const struct Vector*vct_ref){
    for(size_t i=0;i<vct_index(vct_ref);++i)
        printf("%i ",vct_item(vct_ref,i));
    printf("\n");
}

//
int main(){
    int n;
    scanf("%i",&n);

    int m;
    scanf("%i",&m);
    struct Vector*storage_t=vct_create(m);
    for(int i=0;i<m;++i){
        int t;
        scanf("%i",&t);
        vct_append(storage_t,t);
    }

    struct Vector*interval=vct_create(MIN(n,INTERVAL_LEN_MAX));
    for(size_t i=0;i<vct_length(interval);++i)
        vct_append(interval,i+1);

    for(int i=0;i<m;++i){
        for(size_t j=1;j<vct_index(interval);++j)
            interval->array[j]+=(interval->array[j]-1)/(vct_item(storage_t,m-i-1)-1);

        while(vct_item(interval,vct_index(interval)-1)>n)
            vct_pop(interval);
    }

    for(size_t i=0;i<vct_index(interval);++i)
        printf("%i\n",vct_item(interval,i));

    return 0;
}
