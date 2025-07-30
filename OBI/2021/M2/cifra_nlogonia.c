#include<stdio.h>
#include<string.h>
//
int vowels[]={'a','e','i','o','u'};

int check_vowel(char letter){
    for(size_t i=0;i<sizeof(vowels)/sizeof(vowels[0]);++i){
        if(letter==vowels[i])
            return 1;
    }
    return 0;
}

void decode_letter(char letter){
    if(check_vowel(letter)){
        printf("%c",letter);
        return;
    }

    char origin_letter=letter;
    int min_distance=27,
        vowel=0;
    for(size_t i=0;i<sizeof(vowels)/sizeof(vowels[0]);++i){
        int distance=origin_letter-vowels[i];
        if(distance<0)
            distance*=-1;
        if(distance<min_distance){
            min_distance=distance;
            vowel=vowels[i];
        }
    }
    char next_letter=origin_letter+1;
    if(check_vowel(next_letter))
        ++next_letter;


    printf("%c%c%c",origin_letter,vowel,next_letter);
}
//
int main(){
    char cifra[31];
    scanf("%s",cifra);

    for(size_t i=0;i<strlen(cifra);++i)
        decode_letter(cifra[i]);
    printf("\n");

    return 0;
}
