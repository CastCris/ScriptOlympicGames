#include<stdio.h>
#include<stdlib.h>

struct Vector{
    int*array;
    size_t index;
    size_t length;
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
static inline int vct_item(struct Vector*vct_ref,size_t index){
    return vct_ref->array[index];
}

void vct_append(struct Vector*vct_ref,int item){
    if(vct_index(vct_ref)>=vct_length(vct_ref)){
        vct_ref->length*=2;
        vct_ref->array=realloc(vct_ref->array,sizeof(int)*vct_ref->length);
    }
    vct_ref->array[vct_index(vct_ref)]=item;
    ++vct_ref->index;
}
void vct_display(struct Vector*vct_ref){
    for(size_t i=0;i<vct_index(vct_ref);++i)
        printf("%i ",vct_item(vct_ref,i));
    printf("\n");
}

struct Hash_table{
    struct Vector**array;
    size_t length;
};
struct Hash_table*hsh_create(size_t hsh_size){
    struct Hash_table*hsh_new=malloc(sizeof(struct Hash_table));
    hsh_new->array=malloc(sizeof(struct Vector*)*hsh_size);
    for(size_t i=0;i<hsh_size;++i)
        hsh_new->array[i]=vct_create(1);
    hsh_new->length=hsh_size;

    return hsh_new;
}
static inline size_t hsh_length(struct Hash_table*hsh_ref){
    return hsh_ref->length;
}
static inline size_t hsh_generate_key(struct Hash_table*hsh_ref,int value){
    return value%hsh_length(hsh_ref);
}

void hsh_add(struct Hash_table*hsh_ref,int item){
    size_t index=hsh_generate_key(hsh_ref,item);
    vct_append(hsh_ref->array[index],item);
}
int hsh_search(struct Hash_table*hsh_ref,int item){
    size_t index=hsh_generate_key(hsh_ref,item);
    for(size_t i=0;i<vct_index(hsh_ref->array[index]);++i){
        if(vct_item(hsh_ref->array[index],i)==item)
            return 1;
    }
    return 0;
}

void hsh_display(struct Hash_table*hsh_ref){
    for(size_t i=0;i<hsh_length(hsh_ref);++i)
        vct_display(hsh_ref->array[i]);
}

//
int rectangle_in_circle(int*l,size_t n){
    int circo=0,half_c;
    for(size_t i=0;i<n;++i){
        circo+=l[i];
    }
    half_c=circo/2;
    if(circo%2)
        return 0;

    struct Hash_table*prefix_set=hsh_create(n);
    int*prefix=calloc(n,sizeof(int));

    hsh_add(prefix_set,prefix[0]);
    for(size_t i=1;i<n;++i){
        prefix[i]=prefix[i-1]+l[i-1];
        hsh_add(prefix_set,prefix[i]);
    }

    int sides=0;
    for(size_t i=0;i<n;++i){
        int oposite_side=(half_c+prefix[i])%circo;
        if(hsh_search(prefix_set,oposite_side))
            ++sides;
    }
    if(sides/2>=2)
        return 1;

    return 0;
}

int main(){
    size_t n;
    scanf("%li",&n);

    int*l=malloc(sizeof(int)*n);
    for(size_t i=0;i<n;++i)
        scanf("%i",&l[i]);

    if(rectangle_in_circle(l,n))
        printf("S\n");
    else
        printf("N\n");

    return 0;
}

