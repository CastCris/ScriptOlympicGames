import math

def main()->None:
    x=int(input())
    y=int(input())

    x_range=math.ceil(x**(1/6))
    y_range=math.floor(y**(1/6))


    count=y_range-x_range+1

    print(count)

if __name__=="__main__":
    main()
