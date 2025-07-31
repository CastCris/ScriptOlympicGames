#include<stdio.h>
#include<stdlib.h>
//
struct Vector{
    int*array;
    size_t index;
    size_t length;
};
struct Vector*vct_create(size_t vct_size){
    struct Vector*vct_new=(struct Vector*)malloc(sizeof(struct Vector));
    vct_new->array=(int*)malloc(sizeof(int)*vct_size);
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

static inline int    vct_item(struct Vector*vct_ref,size_t index){
    return vct_ref->array[index];
}


void vct_append(struct Vector*vct_ref,int item){
    if(vct_index(vct_ref)>=vct_length(vct_ref)){
        vct_ref->length*=2;
        vct_ref->array=(int*)realloc(vct_ref->array,sizeof(int)*vct_ref->length);
    }
    vct_ref->array[vct_index(vct_ref)]=item;
    ++vct_ref->index;
}

void vct_pop(struct Vector*vct_ref){
    --vct_ref->index;
}

void vct_display(struct Vector*vct_ref){
    for(size_t i=0;i<vct_index(vct_ref);++i)
        printf("%i ",vct_item(vct_ref,i));
    printf("\n");
}
//
struct Vector_over{
    struct Vector**vct;
    size_t index;
    size_t length;
};
struct Vector_over*vctOver_create(size_t vctOver_size){
    struct Vector_over*vctOver_new=(struct Vector_over*)malloc(sizeof(struct Vector_over));
    vctOver_new->vct=(struct Vector**)malloc(sizeof(struct Vector*)*vctOver_size);
    vctOver_new->index=0;
    vctOver_new->length=vctOver_size;

    return vctOver_new;
}
static inline size_t vctOver_index(struct Vector_over*vctOver_ref){
    return vctOver_ref->index;
}
static inline size_t vctOver_length(struct Vector_over*vctOver_ref){
    return vctOver_ref->length;
}
static inline struct Vector*vctOver_item(struct Vector_over*vctOver_ref,size_t index){
    return vctOver_ref->vct[index];
}

void vctOver_grow(struct Vector_over*vctOver_ref){
    if(vctOver_index(vctOver_ref)>=vctOver_length(vctOver_ref)){
        vctOver_ref->length*=2;
        vctOver_ref->vct=(struct Vector**)realloc(vctOver_ref->vct,sizeof(struct Vector*)*vctOver_ref->length);
    }
    vctOver_ref->vct[vctOver_index(vctOver_ref)]=vct_create(1);
    ++vctOver_ref->index;
}

void vctOver_append(struct Vector_over*vctOver_ref,size_t index,int item){
    vct_append(vctOver_ref->vct[index],item);
}

void vctOver_display(struct Vector_over*vctOver_ref){
    for(size_t i=0;i<vctOver_index(vctOver_ref);++i)
        vct_display(vctOver_ref->vct[i]);
}
//
int check_intersection_sets(struct Vector*set1,struct Vector*set2){
    int intersections=0;
    for(size_t i=0;i<vct_index(set1);++i){
        for(size_t j=0;j<vct_index(set2);++j){
            if(vct_item(set1,i)==vct_item(set2,j)){
                ++intersections;
                break;
            }
        }
    }
    if((size_t)intersections==vct_index(set2))
        return 1;
    return 0;
}
int backtracking(struct Vector*array,size_t index,struct Vector*subset,struct Vector_over*subsets_invalid){
    for(size_t i=0;i<vctOver_index(subsets_invalid);++i){
        if(check_intersection_sets(subset,vctOver_item(subsets_invalid,i))){
            //vct_display(subset);
            return 0;
        }
    }

    if(index>=vct_index(array))
        return 1;

    int instances=0;

    vct_append(subset,vct_item(array,index));
    //vct_display(subset);
    instances+=backtracking(array,index+1,subset,subsets_invalid);

    vct_pop(subset);
    instances+=backtracking(array,index+1,subset,subsets_invalid);

    return instances;
}
//
int main(){
    /*
    struct Vector_over*tst=vctOver_create(11);
    for(int i=0;i<10;++i){
        vctOver_grow(tst);
        printf("A\n");
        for(int j=i;j<20;++j)
            vctOver_append(tst,i,j);
    }
    vctOver_display(tst);
    */
    /*
    struct Vector*tst=vct_create(1);
    for(int i=0;i<20;++i)
        vct_append(tst,i);
    vct_display(tst);

    struct Vector*array=vct_create(1);
    printf("%i\n",backtracking(tst,0,array)-1);
    */
    int n,m;
    scanf("%i %i",&n,&m);
    struct Vector_over*subsets_invalid=vctOver_create(m);
    for(int i=0;i<m;++i){
        int x,y;
        scanf("%i %i",&x,&y);
        vctOver_grow(subsets_invalid);
        vctOver_append(subsets_invalid,i,x);
        vctOver_append(subsets_invalid,i,y);
    }

    struct Vector*array=vct_create(n);
    for(int i=0;i<n;++i)
        vct_append(array,i+1);

    struct Vector*temp=vct_create(n);
    printf("%i\n",backtracking(array,0,temp,subsets_invalid)-1);

    return 0;
}
