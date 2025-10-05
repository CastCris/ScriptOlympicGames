#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
struct node_vector{
	int key,value;
	size_t index;
};
struct node_vector*create_node(int key,int value,size_t index){
	struct node_vector*new_node=malloc(sizeof(struct node_vector));
	new_node->key=key;
	new_node->value=value;
	new_node->index=index;

	return new_node;
}

struct vector{
	struct node_vector**array;
	size_t index,maxlen;
};
struct vector*create_vector(size_t length){
	struct vector*new_vector=malloc(sizeof(struct vector));
	new_vector->array=malloc(sizeof(struct node_vector*)*length);
	new_vector->index=0;
	new_vector->maxlen=length;

	return new_vector;
}
void swap_int(int*n1,int*n2){
	*n1+=*n2;
	*n2=*n1-*n2;
	*n1-=*n2;
}
void swap_nodes(struct node_vector**array,size_t id1,size_t id2){
	swap_int(&array[id1]->key,&array[id2]->key);
	swap_int(&array[id1]->value,&array[id2]->value);

	array[id1]->index+=array[id2]->index;
	array[id2]->index=array[id1]->index-array[id2]->index;
	array[id1]->index-=array[id1]->index;
}
void shift_up(struct vector*ref,size_t index){
	if(!index)return;
	if(ref->array[index]->key<ref->array[(index-1)/2]->key)return;
	swap_nodes(ref->array,index,(index-1)/2);
	shift_up(ref,(index-1)/2);
}
void append_vector(struct vector*ref,int key,int value,size_t index){
	if(ref->index>ref->maxlen-1){
		ref->maxlen*=2;
		ref->array=realloc(ref->array,sizeof(struct node*)*ref->maxlen);
	}
	ref->array[ref->index]=create_node(key,value,index);
	shift_up(ref,ref->index);
	++ref->index;
}
void shift_down(struct vector*ref,size_t index){
	size_t temp=index;

	if(index*2+1<ref->index&&ref->array[index*2+1]->key>ref->array[temp]->key)
		temp=index*2+1;
	if(index*2+2<ref->index&&ref->array[index*2+2]->key>ref->array[temp]->key)
		temp=index*2+2;

	if(temp!=index){
		swap_nodes(ref->array,index,temp);
		shift_down(ref,temp);
	}
}
struct node_vector*extract(struct vector*ref){
	struct node_vector*result=ref->array[0];
	ref->array[0]=ref->array[ref->index-1];
	--ref->index;
	shift_down(ref,0);

	return result;
}
int empty(struct vector*ref){
	if(ref->index<1)return 1;
	return 0;
}
void display_vector(struct vector*ref){
	for(size_t i=0;i<ref->index;++i)
		printf("%i ",ref->array[i]->key);
}
int sum_digits(int n){
	int result=0;
	while(n){
		result+=n%10;
		n/=10;
	}
	return result;
}

int maximumSum(int*nums,int numsSize){
	int max_sum=0,array_sum[numsSize],result=-1;
	for(size_t i=0;i<numsSize;++i){
		array_sum[i]=sum_digits(nums[i]);
		if(array_sum[i]>max_sum)
			max_sum=array_sum[i];
	}
	struct vector**array_array=malloc(sizeof(struct vector*)*(max_sum+1));
	for(size_t i=0;i<max_sum+1;++i)
		array_array[i]=create_vector(1);

	for(size_t i=0;i<numsSize;++i)
		append_vector(array_array[array_sum[i]],nums[i],array_sum[i],i);

	for(size_t i=0;i<numsSize;++i){
		int number=nums[i],max=-1;
		struct vector temp_vector=*(array_array[array_sum[i]]);
		while(!empty(&temp_vector)){
			struct node_vector*ext=extract(&temp_vector);
			if(array_sum[i]==ext->value&&i!=ext->index){
				max=number+ext->key;
				break;
			}
		}
		if(max>result)result=max;
	}
	return result;
}


int main(){
	int array[]={18,43,36,13,7};
	printf("%i\n",maximumSum(array,sizeof(array)/sizeof(*array)));

	return 0;
}
