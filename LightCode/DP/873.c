#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
int lenLongestFibSubseq(int*arr,int arrSize){
	int max_len=0,
		dp[arrSize][arrSize];
	for(int i=0;i<arrSize;++i)
		memset(dp[i],0,sizeof(dp[i]));

	for(int i=0;i<arrSize-2;++i){
		int current=arr[i+2];
		size_t left=0,right=i+1;
		//printf("%i|",current);
		while(left<right){
			if(arr[left]+arr[right]<current){
				++left;
			}else if(arr[left]+arr[right]>current){
				--right;
			}else{
				//printf("%li %li/",left,right);
				dp[right][i+2]=dp[left][right]+1;
				if(dp[right][i+2]>max_len)
					max_len=dp[right][i+2];
				++left;
				--right;
			}
		}
		//printf("\n");
	}
	if(max_len)
		return max_len+2;
	return 0;
}

int main(){
	// 1,2,3,4,5,6,7,8
	// 1,3,7,11,12,14,18
	// 1,1,2,3
	// 2,4,7,8,9,10,14,15,18,23,32,50
	int array[]={};
	printf("%i\n",lenLongestFibSubseq(array,sizeof(array)/sizeof(*array)));

	return 0;
}
