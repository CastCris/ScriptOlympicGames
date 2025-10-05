#include<stdio.h>
#include<stdlib.h>
//
size_t two_ptr(int*nums,int*new_nums,size_t nums_size){
	size_t left=0,new_size=1;
	new_nums[0]=nums[0];
	for(size_t i=1;i<nums_size;++i){
		if(nums[left]-nums[i]){
			new_nums[new_size]=nums[i];
			++new_size;
			left=i;
		}
	}
	return new_size;
}

int removeDuplicates(int*nums,size_t numsSize){
	int new_nums[numsSize],
		new_size=(int)two_ptr(nums,new_nums,numsSize);
	for(int i=0;i<new_size;++i)
		nums[i]=new_nums[i];
	return new_size;
}
