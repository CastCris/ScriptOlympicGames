#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
void reverse_array(int*array,size_t size_array){
	for(size_t i=0;i<size_array/2;++i){
		array[i]+=array[size_array-i-1];
		array[size_array-i-1]=array[i]-array[size_array-i-1];
		array[i]-=array[size_array-i-1];
	}
}
int jump(int*array,size_t size_array){
	reverse_array(array,size_array);

	int pre_processed[size_array];
	memset(pre_processed,-1,sizeof(pre_processed));
	pre_processed[0]=0;

	for(int i=0;i<size_array;++i){
		int min=-1;
		for(int j=0;j<array[i];++j){
			if(i-j-1<0)continue;
			if((pre_processed[i-j-1]<min|min==-1)&&pre_processed[i-j-1]!=-1)
				min=pre_processed[i-j-1]+1;
		}
		if(min==-1)continue;
		pre_processed[i]=min;
	}

	return pre_processed[size_array-1];
}

int main(){
	int array[]={8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5};
	printf("%i\n",jump(array,sizeof(array)/sizeof(int)));

	return 0;
}
