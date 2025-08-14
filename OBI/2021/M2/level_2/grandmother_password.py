BLUR_CHAR='#'

def main():
    [n,m,k]=list(map(int,input().split()))
    password=input()
    regex=[]
    for i in range(m):
        regex.append(input())
        regex[i]=''.join(sorted(regex[i]))
    path=''

    depth_level_max=int(input())
    depth_level_curr=0

    for i in range(m):
        depth_level=k**(m-i-1)
        for j in range(k):
            if depth_level_curr+depth_level>=depth_level_max:
                path+=regex[i][j]
                break
            depth_level_curr+=depth_level

    path_index=0
    for i in range(n):
        if password[i]==BLUR_CHAR:
            print(path[path_index],end='')
            path_index+=1
            continue
        print(password[i],end='')
    print()

if __name__=='__main__':
    main()
