import sys
sys.set_int_max_str_digits(0)

a = int(input()) 
b = int(input())

if a > b: 
    print(-1)
else: 
    s_a = str(a) 
    s_b = str(b)

    if s_a in s_b:  
        print(0) 
    else: 
        d = (b - a) // 9
        if d < a: 
            print(-1) 
        else: 
            print(d - a)