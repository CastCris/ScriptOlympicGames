def num_decompose(x:int)->list:
    num_decom=[];
    while(x):
        num_decom.append(x%10);
        x//=10;
    num_decom.reverse()
    return num_decom
def get_digits_sum_equal(num:list,trigget:int,level:int,sum_:int,equal:int)->int:
    if(sum_==equal):
        return 1
    if(level>=len(num) or sum_>equal):
        return 0

    range_max=num[level] if trigget else 9
    num_level=num[level]
    instances=0
    #print('(',end='')
    for i in range(range_max+1):
        #print(' {}'.format(i),end='')
        new_trigget=1 if i==num_level and trigget else 0
        new_sum=sum_+i
        instances+=get_digits_sum_equal(num,new_trigget,level+1,new_sum,equal)
    #print(')',end='')
    return instances

def main():
    s=int(input())
    a=int(input())
    b=int(input())

    a_decompose=num_decompose(a-1)
    b_decompose=num_decompose(b)

    a_digits=get_digits_sum_equal(a_decompose,1,0,0,s)
    b_digits=get_digits_sum_equal(b_decompose,1,0,0,s)

    print(b_digits-a_digits)

if __name__=="__main__":
    main()
