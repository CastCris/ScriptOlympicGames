ALPHABET_SIZE=26

def anagram(str1:str,str2:str,length:int)->int:
    #print(str1,str2)
    letters_signature=[0 for i in range(ALPHABET_SIZE)]
    for i in range(length):
        letters_signature[ord(str1[i])-ord('a')]+=1
        letters_signature[ord(str2[i])-ord('a')]-=1
    #print(letters_signature)
    for i in range(ALPHABET_SIZE):
        if letters_signature[i]:
            return 0
    return 1
        
def main()->None:
    x=int(input())
    string=input()

    for i in range(1,x):
        if x%i:
            continue
        valid=1
        for j in range(i,x,i):
            sub_str=string[j:x]
            if not anagram(string,sub_str,i):
                valid=0
                break
        if valid:
            print(string[:i])
            return
    print('*')
    return

if __name__=='__main__':
    main()
