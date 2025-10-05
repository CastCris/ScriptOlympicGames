#include<stdio.h>
//
size_t binary_search(int*array,size_t init,size_t end,int target){
	size_t index=0;
	while(init<end+1){
		index=init+(end-init)/2;
		if(array[index]<target)
			init=index+1;
		else if(array[index]>target)
			end=index-1;
		else
			break;
	}
	if(array[index]<target)
		return index+1;
	return index;
}

int searchInsert(int*nums,size_t numsSize,int target){
	return (int)binary_search(nums,0,numsSize-1,target);
}
