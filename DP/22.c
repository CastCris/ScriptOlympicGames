#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
#define PATH_SIZE 20

char**result;
size_t size_result;

void parenthesis(int n,int nmax,int to_close,int open,char*str){
	if(n>nmax-1){
		for(int i=0;i<to_close-1;++i)str[strlen(str)]=')';
		strcpy(result[size_result],str);
		++size_result;

		printf("%s\n",str);

		return;
	}

	if(open)str[strlen(str)]='(';
	else str[strlen(str)]=')';

	char path1[PATH_SIZE],path2[PATH_SIZE];
	memset(path1,0,sizeof(path1));
	memset(path2,0,sizeof(path2));
	strcpy(path1,str);
	strcpy(path2,str);

	parenthesis(n+1,nmax,to_close+1,1,path1);
	if(to_close>0&&n<nmax-1)parenthesis(n,nmax,to_close-1,0,path2);
}

#define RES_SIZE 2000
char**genereateParenthesis(int n){
	result=malloc(sizeof(char*)*RES_SIZE);
	for(size_t i=0;i<RES_SIZE;++i)result[i]=malloc(sizeof(char*)*n*2);
	size_result=0;

	char tst[100];
	memset(tst,0,sizeof(tst));
	parenthesis(0,n,1,1,tst);

	return result;
}

int main(){
	for(int i=0;i<100;++i)genereateParenthesis(i+1);
	printf("ok\n");
	return 0;
}
