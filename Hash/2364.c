#include<stdio.h>
#include<stdlib.h>
//
struct node{
	int data,
		amount;
};
struct node*create_node(int data){
	struct node*new_node=malloc(sizeof(struct node));
	new_node->data=data;
	new_node->amount=1;

	return new_node;
}
int adin(struct node*res){
	return res->data;
}
int aain(struct node*res){
	return res->amount;
}

struct vector{
	struct node**array;
	size_t index,
		   length;
};
struct vector*create_vector(size_t size){
	struct vector*new_vct=malloc(sizeof(struct vector));
	new_vct->array=malloc(sizeof(struct node*)*size);
	new_vct->index=0;
	new_vct->length=size;

	return new_vct;
}
void app_vct(struct vector*ref,int data){
	if(ref->index>ref->length-1){
		ref->array=realloc(ref->array,sizeof(struct node*)*ref->length*2);
		ref->length*=2;
	}
	ref->array[ref->index]=create_node(data);
	++ref->index;
}
int queries_vct(struct vector*ref,int querie){
	for(size_t i=0;i<ref->index;++i){
		if(adin(ref->array[i])==querie)return i;
	}
	return -1;
}
void display_vct(struct vector*ref_vct){
	for(size_t i=0;i<ref_vct->index;++i){
		printf("%i %i|",adin(ref_vct->array[i]),aain(ref_vct->array[i]));
	}
}
struct hash{
	struct vector**array_hash;
	size_t index;
};
struct hash*create_hash(size_t length){
	struct hash*new_hash=malloc(sizeof(struct hash));
	new_hash->array_hash=malloc(sizeof(struct vector*)*length);
	for(size_t i=0;i<length;++i)new_hash->array_hash[i]=create_vector(1);
	new_hash->index=length;

	return new_hash;
}
int search_in_hash(struct hash*ref,int data){
	return queries_vct(ref->array_hash[data%ref->index],data);
}
void insert_in_hash(struct hash*ref,int data){
	int index_node;
	if((index_node=search_in_hash(ref,data))==-1)app_vct(ref->array_hash[data%ref->index],data);
	else ++ref->array_hash[data%ref->index]->array[index_node]->amount;
}

void display_hash(struct hash*ref){
	for(size_t i=0;i<ref->index;++i){
		printf("%i->",i);
		display_vct(ref->array_hash[i]);
		printf("\n");
	}
}

long long countBadPairs(int*nums,int numSize){
	struct hash*tag=create_hash(numSize);
	int tot=((numSize-1)*numSize)/2;
	for(size_t i=0;i<numSize;++i){
		insert_in_hash(tag,i-nums[i]);
	}
	//display_hash(tag);
	for(size_t i=0;i<numSize;++i){
		for(size_t j=0;j<tag->array_hash[i]->index;++j){
			int amount=aain(tag->array_hash[i]->array[j]);
			if(amount>1)tot-=((amount-1)*amount)/2;
		}
	}

	printf("%i\n",tot);
}

int main(){
	int array[]={5,6,3,4};
	countBadPairs(array,sizeof(array)/sizeof(int));
	return 0;
}
