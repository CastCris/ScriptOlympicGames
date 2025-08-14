def rectangle_in_circle(array:list)->int:
    circo=sum(array)
    if circo%2:
        return 0
    half_circo=circo/2

    prefix_sum=[0 for i in range(len(array))]
    for i in range(0,len(array)-1):
        prefix_sum[i+1]=prefix_sum[i]+array[i]
    prefix_set=set(prefix_sum)

    sides=0
    for i in prefix_sum:
        oppose_side=(i+half_circo)%circo
        if oppose_side in prefix_set:
            sides+=1
    
    if sides//2>=2:
        return 1

    return 0

            
def main()->None:
    n=input()
    array=list(map(int,input().split()))

    if rectangle_in_circle(array):
        print('S')
        return
    print('N')

if __name__=="__main__":
    main()
