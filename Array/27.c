#include<stdio.h>
//
int removeElement(int*nums,size_t numsSize,int val){
	if(!numsSize)
		return 0;
	int temp[numsSize],
		temp_size=0;
	for(size_t i=0;i<numsSize;++i)
		if(nums[i]!=val){
			temp[temp_size]=nums[i];
			++temp_size;
		}
	for(int i=0;i<temp_size;++i)
		nums[i]=temp[i];

	return temp_size;
}
