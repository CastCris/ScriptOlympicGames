#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define NUM_MAX 100000001

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
    for(size_t i=0;i<vct_index(vct_ref);++i){
        printf("%i ",vct_item(vct_ref,i));
    }
    printf("\n");
}


struct Hash_table{
    struct Vector**table;
    size_t length;
};
struct Hash_table*hsh_create(const size_t hsh_length){
    struct Hash_table*hsh_new=malloc(sizeof(struct Hash_table));
    hsh_new->table=malloc(sizeof(struct Vector*)*hsh_length);
    for(size_t i=0;i<hsh_length;++i)
        hsh_new->table[i]=vct_create(1);
    hsh_new->length=hsh_length;

    return hsh_new;
}

static inline size_t hsh_length(const struct Hash_table*hsh_ref){
    return hsh_ref->length;
}

static inline size_t hsh_key(const struct Hash_table*hsh_ref,const int item){
    return item%hsh_length(hsh_ref);
}


int hsh_search(const struct Hash_table*hsh_ref,const int value){
    size_t index=hsh_key(hsh_ref,value);
    for(size_t i=0;i<vct_index(hsh_ref->table[index]);++i)
        if(vct_item(hsh_ref->table[index],i)==value)
            return 1;

    return 0;
}

void hsh_add(struct Hash_table*hsh_ref,const int value){
    if(hsh_search(hsh_ref,value))
        return;

    size_t index=hsh_key(hsh_ref,value);
    vct_append(hsh_ref->table[index],value);
}

struct Vector*hsh_get_values(const struct Hash_table*hsh_ref){
    struct Vector*items=vct_create(1);
    for(size_t i=0;i<hsh_length(hsh_ref);++i){
        for(size_t j=0;j<vct_index(hsh_ref->table[i]);++j){
            vct_append(items,vct_item(hsh_ref->table[i],j));
        }
    }

    return items;
}

void hsh_display(const struct Hash_table*hsh_ref){
    for(size_t i=0;i<hsh_length(hsh_ref);++i){
        if(!vct_index(hsh_ref->table[i]))
            continue;
        printf("%li - ",i);
        vct_display(hsh_ref->table[i]);
    }
    printf("\n");
}
//
struct Vector*nums_able(){
    struct Vector*nums=vct_create(1);
    for(int i=2;i<pow((double)NUM_MAX,1.0/3.0);++i)
        vct_append(nums,i);

    return nums;
}

struct Hash_table*nums_square_and_cube(){
    struct Hash_table*nums_squabe=hsh_create(1000);
    const struct Vector*nums=nums_able();
    // vct_display(nums);

    for(size_t i=0;i<vct_index(nums);++i){
        double item=vct_item(nums,i);
        int expo=6;
        while(pow(item,expo)<=(double)NUM_MAX){
            // printf("%lf ",item);
            hsh_add(nums_squabe,pow(item,expo));
            expo*=2;
        }
        // printf("\n");

        if(expo==6)
            break;
    }
    hsh_add(nums_squabe,1);

    return nums_squabe;
}

int nums_square_and_cube_range(const int num){
    struct Hash_table*nums_valid=nums_square_and_cube();
    struct Vector*nums=hsh_get_values(nums_valid);
    int count=0;
    //vct_display(nums);

    for(size_t i=0;i<vct_index(nums);++i){
        int item=vct_item(nums,i);
        if(item>num)
            continue;
        //printf("%i\n",item);
        ++count;
    }

    return count;
}
//
int main(){
    int x,y;
    scanf("%i %i",&x,&y);
    
    int range_x=nums_square_and_cube_range(x-1);
    int range_y=nums_square_and_cube_range(y);

    printf("%i\n",range_y-range_x);

    return 0;
}
