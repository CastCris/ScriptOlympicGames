#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define NUM_MAX_LEN 9

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

static inline int vct_item(const struct Vector*vct_ref,const size_t index){
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

void vct_display(const struct Vector*vct_ref){
    for(size_t i=0;i<vct_index(vct_ref);++i)
        printf("%i ",vct_item(vct_ref,i));
    printf("\n");
}


struct Vector*num_decompose(int x){
    struct Vector*num=vct_create(1);
    while(x){
        vct_append(num,x%10);
        x/=10;
    }

    return num;
}

int num_by_vector(const struct Vector*vct_ref){
    if(!vct_index(vct_ref)){
        return -1;
    }

    int num=0;
    for(size_t i=0;i<vct_index(vct_ref);++i){
        int digit=vct_item(vct_ref,i)*pow(10,i);
        num+=digit;
    }

    return num;
}

int main(){
    int n,m;
    scanf("%i",&n);
    scanf("%i",&m);

    struct Vector*x=num_decompose(n);
    struct Vector*y=num_decompose(m);

    while(vct_index(x)<vct_index(y))
        vct_append(x,0);
    while(vct_index(x)>vct_index(y))
        vct_append(y,0);

    struct Vector*x_new=vct_create(vct_index(x));
    struct Vector*y_new=vct_create(vct_index(y));

    for(size_t i=0;i<vct_index(x);++i){
        int x_item=vct_item(x,i),
            y_item=vct_item(y,i);
        if(x_item>y_item){
            vct_append(x_new,x_item);
            continue;
        }
        if(x_item<y_item){
            vct_append(y_new,y_item);
            continue;
        }

        vct_append(x_new,x_item);
        vct_append(y_new,y_item);
    }

    int x_num=num_by_vector(x_new),
        y_num=num_by_vector(y_new);

    if(x_num>y_num){
        x_num+=y_num;
        y_num=x_num-y_num;
        x_num-=y_num;
    }

    printf("%i %i\n",x_num,y_num);

    return 0;
}
