#include<stdio.h>
#include<stdlib.h>
//
int main(){
    size_t str_size;
    scanf("%li",&str_size);

    char*str=malloc(sizeof(char)*(str_size+5));
    scanf("%s",str);

    int*letters=calloc(26,sizeof(int));
    for(size_t i=0;i<str_size;++i){
        ++letters[str[i]-97];
    }
    /*
    for(size_t i=0;i<26;++i)
        printf("( %c %i ) ",(char)i+97,letters[i]);
    printf("\n");
    */
    //
    int*root_signature=calloc(26,sizeof(int)),
        root_letter=str[0]-97;
    char*root=malloc(sizeof(char)*(str_size+5));
    
    for(size_t i=0;i<str_size/2;++i){
        ++root_signature[str[i]-97];
        root[i]=str[i];
        int is_root=1;
        for(size_t j=0;j<26;++j){
            if(j==(size_t)root_letter)
                continue;
            //printf("(%c %i %i) ",(char)j+97,root_signature[root_letter],root_signature[j]);
            double proportion_root=(double)root_signature[j]/(double)root_signature[root_letter];
            double proportion_letters=(double)letters[j]/(double)letters[root_letter];
            //printf("%lf %lf\n",proportion_root,proportion_letters);
            if(proportion_root==proportion_letters)
                continue;
            is_root=0;
            break;
        }
        if(is_root){
            root[i+1]='\0';
            printf("%s\n",root);
            return 0;
        }
    }
    printf("*\n");


    return 0;
}
