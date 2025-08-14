def num_decompose(x:int)->list:
    num=[]
    while x>0:
        num.append(x%10)
        x//=10

    return num

def num_from_list(x:list)->int:
    if not len(x):
        return -1
    num=0
    for i in range(len(x)):
        digit=x[i]*(10**i)
        num+=digit

    return num

def main()->None:
    x=int(input())
    y=int(input())

    x_list=num_decompose(x)
    y_list=num_decompose(y)

    while(len(x_list)<len(y_list)):
        x_list.append(0)

    while(len(x_list)>len(y_list)):
        y_list.append(0)

    x_new=[]
    y_new=[]
    for i in range(len(x_list)):
        x_item=x_list[i]
        y_item=y_list[i]

        if x_item>y_item:
            x_new.append(x_item)
            continue
        if x_item<y_item:
            y_new.append(y_item)
            continue

        x_new.append(x_item)
        y_new.append(y_item)


    x=min(num_from_list(x_new),num_from_list(y_new))
    y=max(num_from_list(y_new),num_from_list(x_new))

    print("{} {}".format(x,y))

if __name__=="__main__":
    main()
