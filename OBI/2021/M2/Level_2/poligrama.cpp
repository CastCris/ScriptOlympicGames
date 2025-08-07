#include<iostream>
#include<cstring>

#define ALPHABET_SIZE 26

int anagram(const char*str1,const char*str2,size_t str2_size){
    //printf("%s %s\n",str1,str2);
    int letters_signature[ALPHABET_SIZE]={0};
    for(size_t i=0;i<str2_size;++i){
        ++letters_signature[str1[i]-'a'];
        --letters_signature[str2[i]-'a'];
    }
    for(size_t i=0;i<ALPHABET_SIZE;++i)
        if(letters_signature[i])
            return 0;
    return 1;
}
//
int main(){
    size_t str_size;
    std::scanf("%zu",&str_size);
    char*str=(char*)malloc(sizeof(char)*(str_size+5));
    std::scanf("%s",str);

    for(size_t root_length=1;root_length<=str_size/2;++root_length){
        if(str_size%root_length)
            continue;
        int valid=1;
        for(size_t i=root_length;i<str_size;i+=root_length){
            if(!anagram(str,str+i,root_length)){
                valid=0;
                break;
            }
        }
        if(valid){
            printf("%s\n",strndup(str,root_length));
            return 0;
        }
    }

    printf("*\n");
    return 0;
}
