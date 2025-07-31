def main()->None:
    x=input()
    array=list(map(int,input().split()))

    left,right=0,len(array)-1
    left_value,right_value=array[left],array[right]
    moves=0
    while(1):
        if left==right:
            break
        if right-left==1 and right_value==left_value:
            break
        if right_value==left_value:
            left+=1
            right-=1
            left_value=array[left]
            right_value=array[right]
            continue

        if left_value<right_value:
            left+=1
            moves+=1
            left_value+=array[left]
            continue
        if left_value>right_value:
            right-=1
            moves+=1
            right_value+=array[right]
            continue

    print(moves)

print(__name__)
if __name__=='__main__':
    main()
