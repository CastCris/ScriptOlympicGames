#include<stdio.h>
#include<stdlib.h>
//
struct Vector{
    int*    array;
    size_t  index;
    size_t  length;
};
struct Vector*vct_create(size_t vct_size){
    struct Vector*vct_new=malloc(sizeof(struct Vector));
    vct_new->array=malloc(sizeof(int)*vct_size);
    vct_new->index=0;
    vct_new->length=vct_size;

    return vct_new;
}
static inline size_t vct_index(struct Vector*vct_ref){
    return vct_ref->index;
}
static inline size_t vct_length(struct Vector*vct_ref){
    return vct_ref->length;
}
static inline int  vct_item(struct Vector*vct_ref,size_t index){
    return vct_ref->array[index];
}

void vct_append(struct Vector*vct_ref,int item){
    if(vct_index(vct_ref)>=vct_length(vct_ref)){
        vct_ref->length*=2;
        vct_ref->array=realloc(vct_ref->array,sizeof(int)*vct_length(vct_ref));
    }
    vct_ref->array[vct_index(vct_ref)]=item;
    ++vct_ref->index;
}

static inline void vct_display(struct Vector*vct_ref){
    for(size_t i=0;i<vct_index(vct_ref);++i)
        printf("%i ",vct_ref->array[i]);
    printf("\n");
}
//
struct Vector*number_decompose(int x){
    struct Vector*num=vct_create(1);
    for(size_t i=0;x;++i){
        vct_append(num,x%10);
        x/=10;
    }
    for(size_t i=0;i<vct_index(num)/2;++i){
        size_t j=vct_index(num)-i-1;

        num->array[i]+=num->array[j];
        num->array[j]=num->array[i]-num->array[j];
        num->array[i]-=num->array[j];
    }

    return num;
}

int digits_equal(struct Vector*num,size_t level,int trigger,int sum,int equal){
    if(sum==equal)
        return 1;
    if(level>=vct_index(num)||sum>equal)
        return 0;
    
    int range_max=(trigger)?vct_item(num,level):9;
    int num_level=vct_item(num,level);
    int instances=0;

    //printf("(");
    for(int i=0;i<=range_max;++i){
        //printf(" %i",i);
        int trigger_new=(i==num_level&&trigger)?1:0;
        int new_sum=sum+i;
        instances+=digits_equal(num,level+1,trigger_new,new_sum,equal);
    }
    //printf(") ");

    return instances;
}

int main(){
    int s,a,b;
    scanf("%i",&s);
    scanf("%i",&a);
    scanf("%i",&b);
    //
    struct Vector*a_decom=number_decompose(a-1);
    struct Vector*b_decom=number_decompose(b);

    int digits_a=digits_equal(a_decom,0,1,0,s);
    //printf("\n");
    int digits_b=digits_equal(b_decom,0,1,0,s);
    //printf("\n");

    printf("%i\n",digits_b-digits_a);

    return 0;
}
