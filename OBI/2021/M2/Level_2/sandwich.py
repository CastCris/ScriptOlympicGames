def main():
    [n,m]=input().split()
    n=int(n)
    m=int(m)
    set_invalids=[]
    for i in range(m):
        [x,y]=input().split()
        set_invalids.append([int(x)-1,int(y)-1])

    answer=0
    for mask in range(1,(1<<n)):
        valid=1
        for item in set_invalids:
            if (mask & (1<<item[0])) and (mask & (1<<item[1])):
                valid=0
                break
        if valid:
            answer+=1
    print(answer)

if __name__=='__main__':
    main()
