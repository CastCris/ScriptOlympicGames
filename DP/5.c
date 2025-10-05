char*longestPalindrome(char*s){
	int**array=malloc(sizeof(int*)*strlen(s));
	size_t n=strlen(s),start=0,len=1;

	for(size_t i=0;i<n;++i){
		array[i]=calloc(strlen(s),sizeof(int));
		array[i][i]=1;
	}
	for(size_t i=0;i<n-1;++i){
		if(s[i]==s[i+1]){
			start=i;
			len=2;
			array[i][i+1]=1;
		}
	}

	for(size_t k=2;k<n;++k){
		for(size_t i=0;i<n-k;++i){
			size_t j=i+k;
			if(array[i+1][j-1]&&s[i]==s[j]){
				array[i][j]=1;
				if(k+1>len){
					start=i;
					len=k+1;
				}
			}
		}
	}

	char*result=malloc(len+1);
    for(int i=0;i<len;++i)result[i]=s[start+i];
    result[len]='\0';
    return result;
}
